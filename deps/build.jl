##
using Clang
using Match
using JSON
using libcxxwrap_julia_jll
using Scratch
##

const libpoc_dir = @get_scratch!("libpoc")
const allowed_namespaces = ("poplar", "popops")

# TODO: I really shouldn't be using strings everywhere for these
const supported_nodes = ("EnumDecl", "ClassDecl", "StructDecl", "CXXMethod", "FunctionTemplate", "FunctionDecl", "CXXConstructor", "EnumConstantDecl")

abstract type BindgenContext end

mutable struct DefaultBindgenContext <: BindgenContext
    searched_headers::Array{String}
    blacklisted_headers::Array{String}
    handled_symbols::Set{String}
    seen_symbols::Set{String}
    outputDecls::String
    outputMembers::String
    outputSupertypes::String
end
DefaultBindgenContext() = DefaultBindgenContext([], [], Set([]), Set([]), "", "", "")


function get_system_includes()::Vector{String}
    cxx = get(ENV, "CXX", "g++-10")
    io = IOBuffer()
    readchomp(pipeline(`$(cxx) -x c++ -E -Wp,-v - -fsyntax-only`; stdin=IOBuffer(""), stderr=io))
    m = match(r"#include <\.\.\.> search starts here:(.*)End of search list\."s, String(take!(io)))[1]
    return strip.(split(m[2:end - 1], "\n"))
end


function resolve_headers(headers::Array{String}, includepaths::Array{String})::Vector{String}
    fullheaders = String[]
    for header in headers
        for include in includepaths
            path = joinpath(include, header)
            isfile(path) && push!(fullheaders, path)
        end
    end
    return fullheaders
end


function get_full_name(cursor, funcargs::Bool=true, buf="")
    parent = get_lexical_parent(cursor)
    parent_kind = spelling(kind(parent))
    cursor_name = name(cursor)
    if !funcargs
        cursor_name = split(cursor_name, "(")[1]
    end

    if parent_kind != "TranslationUnit" && parent_kind != "InvalidFile"
        buf = get_full_name(parent, funcargs, buf)
    end
    if buf == ""
        return cursor_name
    else
        return buf * "::" * cursor_name
    end
end

function get_namespace(cursor::CLCursor)
    tmpcursor = cursor

    while spelling(kind(tmpcursor)) != "Namespace" && get_lexical_parent(tmpcursor) != tmpcursor
        tmpcursor = get_lexical_parent(tmpcursor)
    end

    if get_full_name(tmpcursor) == ""
        tmpcursor = Clang.clang_getCursorDefinition(cursor)
        while spelling(kind(tmpcursor)) != "Namespace" && get_lexical_parent(tmpcursor) != tmpcursor
            tmpcursor = get_lexical_parent(tmpcursor)
        end
        return get_full_name(tmpcursor)
    end

    return get_full_name(tmpcursor)
end

function get_class_name(cursor::CLCursor)
    tmpcursor = cursor
    while spelling(kind(tmpcursor)) != "StructDecl" && spelling(kind(tmpcursor)) != "ClassDecl" && get_lexical_parent(tmpcursor) != tmpcursor
        tmpcursor = get_lexical_parent(tmpcursor)
    end
    return get_full_name(tmpcursor)
end

function get_inline_varname(cursor::CLCursor)
    vname = get_class_name(cursor)
    if !startswith(vname, get_namespace(cursor))
        vname = get_namespace(cursor) * vname
    end

    vname = replace(vname, "poplar::" => "")

    vname = uppercasefirst(vname)

    replace(vname, "::" => "")

end

function get_julia_name(cursor::CLCursor)
    method_name = split(name(cursor), "(")[1]
    vname = get_inline_varname(cursor) *  titlecase(method_name, strict=false)

    vname = replace(vname, "poplar::" => "")
    replace(vname, "::" => "")
end

function object_decl_handler(ctx::BindgenContext, classdecl::CLCursor)::Tuple{Union{Nothing, String}, Union{Nothing, String}}
    full_name = get_full_name(classdecl)
    length(children(classdecl)) == 0 && return nothing, "skip_empty_classdecl"
    wrapper_var_name = get_inline_varname(classdecl)

    # handle simple inheritance
    if length(children(classdecl)) > 1 && kind(children(classdecl)[1]) == Clang.CXCursor_CXXBaseSpecifier

        if startswith(get_full_name(children(classdecl)[1]), "class ")
            base_class = split(get_full_name(children(classdecl)[1]), "class ")[2]

            ctx.outputSupertypes *= "template<> struct SuperType<$full_name> { typedef $base_class type; };\n"

            return "auto JL$wrapper_var_name = mod.add_type<$full_name>(\"$wrapper_var_name\", jlcxx::julia_base_type<$base_class>());", nothing
        end
    end

    return "auto JL$wrapper_var_name = mod.add_type<$full_name>(\"$wrapper_var_name\");", nothing
end


function optionals(method::CLCursor)
    args = function_args(method)
    num = 0
    for arg in args
        for token in tokenize(arg)
            if token.text == "="
                num += 1
            end
        end
    end
    return num
end


function should_wrap(item::AbstractString)
    return startswith(item, "ArrayRef") && !contains(item, "poplar") && !contains(item, "std::string") && !contains(item, "program::")
end

function arg_list(method::CLCursor, types=true::Bool, cutoff=Inf, varnames=true::Bool)
    length(function_args(method)) == 0 && return ""
    cutoff == 0 && return ""
    args = function_args(method)
    arglist = get_full_name(method)
    arglist = split(arglist, "(")[2]
    arglist = split(arglist, ")")[1]
    # TODO: this is **really** not a good way to do this


    argssplit = []
    cur = ""
    count = 0
    for chr in arglist
        if chr == '<'
            count += 1
        end

        if chr == '>'
            count -= 1
        end

        if count == 0 && chr == ','
            push!(argssplit, cur)
            cur = ""
            continue
        end

        cur *= chr
    end
    if cur != ""
        push!(argssplit, cur)
    end

    total = ""
    varname = 'a'

    i = 1
    for item in argssplit
        i > cutoff && break
        item = lstrip(item)

        item = replace(item, "const poplar::DebugContext &" => "std::string")
        item = replace(item, "poplar::DebugContext" => "std::string")
        item = replace(item, "poplar::StringRef" => "std::string")

        if types
            pre = ""
            if should_wrap(item)
                pre = "jlcxx::"
            end

            if varnames
                total *= "$pre$item $varname, "
            else
                total *= "$pre$item, "
            end
        else
            if should_wrap(item)
                total *= "jlcxxToPoplar($varname), "
            else
                total *= "$varname, "
            end
        end
        varname += 1
        i += 1
    end
    return total[1:end - 2]
end

function constructor_handler(ctx::BindgenContext, method::CLCursor)::Tuple{Union{Nothing, String}, Union{Nothing, String}}
    Clang.clang_getCXXAccessSpecifier(method) != Clang.CX_CXXPublic && return nothing, "insufficient_access"


    m_header = filename(method)
    m_name = name(method)
    name_small = split(m_name, "(")[1]
    m_kind = kind(method)
    base_var = get_inline_varname(method)

    get_class_name(method) == "" && return nothing, "constructor_missing_class"

    # workaround: ostreams really don't like being copied
    contains(arg_list(method), "ostream") && return nothing, "ostream_blacklist"
    contains(arg_list(method), "istream") && return nothing, "istream_blacklist"
    contains(arg_list(method), "&&") && return nothing, "rvalue_unsupported"

    contains(m_name, "unique_ptr") && return nothing, "unique_ptr_blacklist"


    arg_list(method) == "" && return nothing, "default_constructor" # default constructor gets autogenerated

    tokenize(method)[end].text == "delete" && return nothing, "deleted_method"


    out = "{ using namespace $(get_namespace(method)); \n"

    num_args = length(function_args(method))
    num_required = num_args - optionals(method)
    if num_required == 0
        num_required = 1
    end

    for cutoff in num_required:num_args
        out *= "JL$base_var.constructor<$(arg_list(method, true, cutoff, false))>();\n"
    end

    out *= "}"

    return out, nothing
end


function method_handler(ctx::BindgenContext, method::CLCursor)::Tuple{Union{Nothing, String}, Union{Nothing, String}}
    Clang.clang_getCXXAccessSpecifier(method) != Clang.CX_CXXPublic && return nothing, "insufficient_access"

    m_header = filename(method)
    m_name = name(method)
    name_small = split(m_name, "(")[1]
    m_kind = kind(method)
    base_var = get_inline_varname(method)
    julia_name = get_julia_name(method)
    func_name = get_full_name(method, false)

    get_class_name(method) == "" && return nothing, "constructor_missing_class"

    contains(func_name, "::operator") && return  nothing, "operator_unsupported"
    contains(arg_list(method), "&&") && return nothing, "rvalue_unsupported"

    # workaround: ostreams really don't like being copied
    contains(arg_list(method), "ostream") && return nothing, "ostream_blacklist"
    contains(arg_list(method), "istream") && return nothing, "istream_blacklist"

    # Workaround: getImpl (on various poplar types) returns an incomplete class which messes with cxxwrap
    (m_name == "getImpl()" || m_name == "getPImpl()") && return nothing, "getimpl_blacklist"

    contains(m_name, "connectStreamToCallback") && return nothing, "calls_deleted_function"
    contains(m_name, "registerCycleEstimator") && return nothing, "calls_deleted_function"



    # contains(arg_list(method), "TypeTraits") && return

    out = "{ using namespace $(get_namespace(method)); \n"

    num_args = length(function_args(method))
    num_required = num_args - optionals(method)
    if num_required == 0
        out = out * "JL$base_var.method(\"$julia_name\", []($(get_class_name(method))& cl) {return cl.$name_small();} ); \n"
        num_required += 1
    end

    for cutoff in num_required:num_args
        out = out * "JL$base_var.method(\"$julia_name\", []($(get_class_name(method))& cl, $(arg_list(method, true, cutoff))) {return cl.$name_small($(arg_list(method, false, cutoff)));} ); \n"
    end


    out = out * "}"


    if spelling(kind(method)) == "FunctionTemplate"
        if occursin("ArrayRef<T>", out)
            full = ""
            types = ["ArrayRef<int>", "ArrayRef<long>", "ArrayRef<float>", "ArrayRef<double>"]
            for type in types
                full *= replace(out, "ArrayRef<T>" => type)
            end
            return full, nothing
        end
        return nothing, "unsupported_template"
    end

    return out, nothing
end

function func_handler(ctx::BindgenContext, func::CLCursor)::Tuple{Union{Nothing, String}, Union{Nothing, String}}
    f_name = name(func)
    name_small = split(f_name, "(")[1]
    f_kind = kind(func)
    julia_name = get_julia_name(func)
    func_name = get_full_name(func, false)

    # workaround: ostreams really don't like being copied
    contains(arg_list(func), "ostream") && return nothing, "ostream_blacklist"
    contains(arg_list(func), "istream") && return nothing, "istream_blacklist"


    contains(arg_list(func), "&&") && return nothing, "rvalue_unsupported"
    contains(func_name, "::operator") && return nothing, "operator_unsupported"

    out = "{ using namespace $(get_namespace(func)); \n"
    return out * "mod.method(\"$julia_name\", []($(arg_list(func))) {return $func_name($(arg_list(func, false)));} ); }", nothing
end




function enum_decl_handler(ctx::BindgenContext, decl::CLCursor)::Tuple{Union{Nothing, String}, Union{Nothing, String}}
    !(Clang.clang_getCXXAccessSpecifier(decl) ∈ [Clang.CX_CXXPublic, Clang.CX_CXXInvalidAccessSpecifier]) && return nothing, "insufficient_access"

    full_name = get_full_name(decl)
    julia_name = get_julia_name(decl)
    return "mod.add_bits<$full_name>(\"$julia_name\", jlcxx::julia_type(\"CppEnum\"));", nothing
end

function enum_const_handler(ctx::BindgenContext, decl::CLCursor)::Tuple{Union{Nothing, String}, Union{Nothing, String}}
    !(Clang.clang_getCXXAccessSpecifier(decl) ∈ [Clang.CX_CXXPublic, Clang.CX_CXXInvalidAccessSpecifier]) && return nothing, "insufficient_access"

    full_name = get_full_name(decl)
    julia_name = get_julia_name(decl)
    parent_name = get_julia_name(get_lexical_parent(decl))
    return "mod.set_const(\"$parent_name$julia_name\", $full_name);", nothing
end


function gen_json(ctx::BindgenContext, decl, id, handled=false, not_handled_reason="")
    if not_handled_reason === nothing
        not_handled_reason = ""
    end

    decl_kind = kind(decl)
    spelling(decl_kind) ∈ ["EnumDecl", "ClassDecl", "StructDecl", "CXXMethod", "FunctionTemplate", "FunctionDecl", "CXXConstructor", "EnumConstantDecl"] || return ""
    fname = filename(decl)

    !any(x -> contains(fname, split(x, "/include/")[1]), ctx.searched_headers) && return

    fname = split(fname, "/include/")[2]

    tokenstr = ""
    for token in tokenize(decl)
        tokenstr *= token.text * " "
    end
    tokenstr = tokenstr[1:end-1]

    #if length(tokenstr) > 150
    #    tokenstr = tokenstr[1:150]
    #end


    d = Dict("Implemented" => handled, "Text" => tokenstr, "Namespace" => get_namespace(decl), "Token type" => spelling(decl_kind), "Name" => get_full_name(decl), "Filename" => fname, "FaliureReason" => not_handled_reason)

    open("out.json", "a") do file

        write(file, JSON.json(d) * "\n")
    end
end


function iterate_children(ctx::BindgenContext, childvec::Vector{CLCursor})
    for (i, child) in enumerate(childvec)
        valid = true
        reason = nothing

        child_header = filename(child)
        child_name = name(child)
        child_kind = kind(child)
        startswith(child_name, "__") && (valid = false; reason = "skip_compiler_definitions")  # skip compiler definitions
        child_header ∈ ctx.blacklisted_headers && (valid = false; reason = "header_blacklisted")

        !any(x -> startswith(get_namespace(child), x), allowed_namespaces) && (valid = false; reason = "not_allowed_namespace")


        child_id = get_full_name(child) * "__" * spelling(child_kind)
        child_id = replace(child_id, "poplar::StringRef" => "std::string")

        # prevents duplicate codegen(+error), TODO: check if still necessary
        child_id == "poplar::FieldData::SizeT::size()__CXXMethod" && (valid = false; reason = "filedata_size_blacklist")

        # Popops expressions are causing all kinds of problems
        contains(child_id, "expr::") && (valid = false; "expr_blacklisted")
        contains(child_id, "popops::expr") && (valid = false; "expr_blacklisted")

        # TODO: Find and document reason
        contains(child_id, "equivalent_device_type") && (valid = false; "equivalent_device_type_blacklist")

        # workaround (returning vector of Device causes issues)
        contains(child_id, "getDevices") && (valid = false; "getdevices_blacklist")

        handled = false


        if !(child_id ∈ ctx.handled_symbols)
            if valid
                code, reason = nothing, nothing


                res = @match spelling(child_kind) begin
                    "EnumDecl" => enum_decl_handler(ctx, child)
                    "ClassDecl" => object_decl_handler(ctx, child)
                    "StructDecl" => object_decl_handler(ctx, child)
                end

                if res !== nothing
                    code, reason = res
                    if code !== nothing
                        handled = true
                        ctx.outputDecls *= "// " * child_id * "\n" * code * "\n"
                        push!(ctx.handled_symbols, child_id)
                    end
                end


                res = @match spelling(child_kind) begin
                    "CXXMethod" => method_handler(ctx, child)
                    "FunctionTemplate" => method_handler(ctx, child)
                    "FunctionDecl" => func_handler(ctx, child)
                    "CXXConstructor" => constructor_handler(ctx, child)
                    "EnumConstantDecl" => enum_const_handler(ctx, child)
                end

                if res !== nothing
                    code, reason = res
                    if code !== nothing
                        handled = true
                        ctx.outputMembers *= "// " * child_id * "\n" * code * "\n"
                        push!(ctx.handled_symbols, child_id)
                    end

                end
            end


            if spelling(child_kind) ∈ supported_nodes
                gen_json(ctx, child, child_id, handled, reason)
            end

            push!(ctx.seen_symbols, child_id)

        end


        iterate_children(ctx, children(child))
    end
end

function gen_bindings(headers::Array{String}, blacklist::Array{String})

    rm("out.json"; force=true)

    touch("out.json")
    includes = get_system_includes()
    ctx = DefaultBindgenContext()
    ctx.searched_headers = resolve_headers(headers, includes)
    ctx.blacklisted_headers = resolve_headers(blacklist, includes)
    clangctx = DefaultContext()

    parse_headers!(clangctx, ctx.searched_headers, args=[""], includes=includes)
    for trans_unit in clangctx.trans_units
        root_cursor = getcursor(trans_unit)
        println(root_cursor)
        clang_children = children(root_cursor)
        iterate_children(ctx, clang_children)
    end
    return ctx.outputDecls * ctx.outputMembers, ctx.outputSupertypes
end

function build_bindings(; path::String=joinpath(libpoc_dir, "libpoc.so"), compile::Bool=true)
    gen_inline, gen_inherit = gen_bindings(["poplar/VectorLayout.hpp", "poplar/DeviceManager.hpp", "poplar/Engine.hpp",
                                            "poplar/Graph.hpp", "poplar/IPUModel.hpp", "popops/ElementWise.hpp", "popops/codelets.hpp"],
                                           ["poplar/StringRef.hpp", "poplar/VectorRef.hpp", "poplar/ArrayRef.hpp"])
    #gen_inline = replace(gen_inline, "\n" => "\nprintf(\"Line is %d\\n\", __LINE__);\n")

    # Workaround for CxxWrap not liking any types name "Type"
    gen_inline = replace(gen_inline, "\"Type\"" => "\"Type_\"")

    write("gen_inline.txt", gen_inline)
    write("gen_inherit.txt", gen_inherit)

    cxxwrap_include_dir = joinpath(libcxxwrap_julia_jll.artifact_dir, "include")

    if compile
        # TODO: automatically get julia path
        cxx = get(ENV, "CXX", "g++-10")
        julia_include_dir = joinpath(ENV["JULIA_INCLUDE_DIR"], "julia") # TODO: find a nice default for the include dir
        run(pipeline(`$(cxx) -O0 -std=c++20 -fPIC -shared -I$(julia_include_dir) -I$(cxxwrap_include_dir) -o $(path) $(joinpath(@__DIR__, "template.cpp")) -lpopops -lpoplar`))
    end
    return nothing
end

build_bindings()
