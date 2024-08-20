##
using Clang
using Clang.LibClang
using Clang.Generators
using JSON
##

const allowed_namespaces = ("poplar", "popops")

# TODO: I really shouldn't be using strings everywhere for these
const supported_nodes = ("EnumDecl", "ClassDecl", "StructDecl", "CXXMethod", "FunctionTemplate", "FunctionDecl", "CXXConstructor", "EnumConstantDecl")
const cxx = get(ENV, "CXX", "g++")

abstract type BindgenContext end

mutable struct DefaultBindgenContext <: BindgenContext
    searched_headers::Vector{String}
    blacklisted_headers::Vector{String}
    handled_symbols::Set{String}
    seen_symbols::Set{String}
    outputDecls::String
    outputMembers::String
    outputSupertypes::String
end
DefaultBindgenContext() = DefaultBindgenContext([], [], Set([]), Set([]), "", "", "")


function get_system_includes()::Vector{String}
    io = IOBuffer()
    readchomp(pipeline(`$(cxx) -x c++ -E -Wp,-v - -fsyntax-only`; stdin=IOBuffer(""), stderr=io))
    m = match(r"#include <\.\.\.> search starts here:(.*)End of search list\."s, String(take!(io)))[1]
    return abspath.(strip.(split(m[2:end - 1], "\n")))
end

# Find the header file in one of the include paths
function resolve_header(header::String, include_paths::Vector{String})::String
    for include in include_paths
        path = joinpath(include, header)
        if isfile(path)
            return path
        end
    end
    error("Couldn't find $(header) in $(join(repr.(include_paths), ", "))")
end
# Find header files in the include paths
resolve_headers(headers::Vector{String}, include_paths::Vector{String})::Vector{String} =
    resolve_header.(headers, Ref(include_paths))

function get_full_name(cursor, funcargs::Bool=true, buf="")
    parent = Clang.getCursorSemanticParent(cursor)
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

    while spelling(kind(tmpcursor)) != "Namespace" && Clang.getCursorSemanticParent(tmpcursor) != tmpcursor
        tmpcursor = Clang.getCursorSemanticParent(tmpcursor)
    end

    if get_full_name(tmpcursor) == ""
        tmpcursor = Clang.clang_getCursorDefinition(cursor)
        while spelling(kind(tmpcursor)) != "Namespace" && Clang.getCursorSemanticParent(tmpcursor) != tmpcursor
            tmpcursor = Clang.getCursorSemanticParent(tmpcursor)
        end
        return get_full_name(tmpcursor)
    end

    return get_full_name(tmpcursor)
end

function get_class_name(cursor::CLCursor)
    tmpcursor = cursor
    while spelling(kind(tmpcursor)) != "StructDecl" && spelling(kind(tmpcursor)) != "ClassDecl" && Clang.getCursorSemanticParent(tmpcursor) != tmpcursor
        tmpcursor = Clang.getCursorSemanticParent(tmpcursor)
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

nns(x::Clang.CLInvalidFile) = ""
nns(x::Clang.CLTranslationUnit) = ""
function nns(x::CLCursor)
    pn = nns(Clang.getCursorSemanticParent(x))
    if isempty(pn)
        return spelling(x)
    else
        return pn * "::" * spelling(x)
    end
end
get_qualified_name(x::CLCursor) = isempty(spelling(x)) ? "" : nns(x)

get_qualified_basename(x::CLCursor) = ""
function get_qualified_basename(x::CLTypeRef)
    n = spelling(x)
    startswith(n, "class ") && return split(n, "class ")[2]
    startswith(n, "struct ") && return split(n, "struct ")[2]
    startswith(n, "Union ") && return split(n, "Union ")[2]
    return ""
end
get_qualified_basename(x::CLCXXBaseSpecifier) = get_qualified_basename(children(x)[1])
function get_qualified_basename(x::Union{CLClassDecl,CLStructDecl,CLUnionDecl})
    bn = get_qualified_basename(children(x)[1])
    if isempty(bn)
        return spelling(x)
    else
        return bn * "::" * spelling(x)
    end
end

function object_decl_handler(ctx::BindgenContext, classdecl::CLCursor)::Tuple{Union{Nothing, String}, Union{Nothing, String}}
    full_name = get_full_name(classdecl)
    length(children(classdecl)) == 0 && return nothing, "skip_empty_classdecl"
    wrapper_var_name = get_inline_varname(classdecl)

    # `VertexPerfEstimate` is a simple struct, we need to map it to a manually
    # defined struct on the Julia side.
    if wrapper_var_name == "VertexPerfEstimate"
        return """mod.map_type<poplar::VertexPerfEstimate>("VertexPerfEstimate");""", nothing
    end

    # handle simple inheritance
    subnodes = children(classdecl)
    if length(subnodes) > 1 && kind(subnodes[1]) == Clang.CXCursor_CXXBaseSpecifier
        base_class = get_qualified_basename(subnodes[1])
        if !isempty(base_class)

            ctx.outputSupertypes *= "template<> struct SuperType<$full_name> { typedef $base_class type; };\n"

            return "auto JL$wrapper_var_name = mod.add_type<$full_name>(\"$wrapper_var_name\", jlcxx::julia_base_type<$base_class>());", nothing
        end
    end

    return "auto JL$wrapper_var_name = mod.add_type<$full_name>(\"$wrapper_var_name\");", nothing
end


function optionals(args::Vector)
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
optionals(method::CLCursor) = optionals(get_function_args(method))

function should_wrap(item::AbstractString)
    return startswith(item, "ArrayRef") && !contains(item, "poplar") && !contains(item, "std::string") && !contains(item, "program::")
end

function arg_list(method::CLCursor, types=true::Bool, cutoff=Inf, varnames=true::Bool)
    Clang.getNumArguments(Clang.getCursorType(method)) == 0 && return ""
    cutoff == 0 && return ""
    arglist = get_full_name(method) # -> spelling(method)
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

        # item = replace(item, "const DebugContext &" => "std::string")
        # item = replace(item, "DebugContext" => "std::string")
        # item = replace(item, "StringRef" => "std::string")

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


    m_header = spelling(method)
    m_name = name(method)
    name_small = split(m_name, "(")[1]
    m_kind = kind(method)
    base_var = get_inline_varname(method)

    get_class_name(method) == "" && return nothing, "constructor_missing_class"

    # workaround: ostreams really don't like being copied
    arglist = arg_list(method)
    contains(arglist, "ostream") && return nothing, "ostream_blacklist"
    contains(arglist, "istream") && return nothing, "istream_blacklist"
    contains(arglist, "&&") && return nothing, "rvalue_unsupported"

    contains(m_name, "unique_ptr") && return nothing, "unique_ptr_blacklist"


    arglist == "" && return nothing, "default_constructor" # default constructor gets autogenerated

    tokenize(method)[end].text == "delete" && return nothing, "deleted_method"


    out = "{ using namespace $(get_namespace(method));\n"

    args = get_function_args(method)
    num_args = length(args)
    num_required = num_args - optionals(args)
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

    m_header = spelling(method)
    m_name = name(method)
    name_small = split(m_name, "(")[1]
    m_kind = kind(method)
    base_var = get_inline_varname(method)
    julia_name = get_julia_name(method)
    func_name = get_full_name(method, false)

    get_class_name(method) == "" && return nothing, "constructor_missing_class"

    contains(func_name, "::operator") && return  nothing, "operator_unsupported"
    arglist = arg_list(method)
    contains(arglist, "&&") && return nothing, "rvalue_unsupported"

    # workaround: ostreams really don't like being copied
    contains(arglist, "ostream") && return nothing, "ostream_blacklist"
    contains(arglist, "istream") && return nothing, "istream_blacklist"

    # Workaround: getImpl (on various poplar types) returns an incomplete class which messes with cxxwrap
    (m_name == "getImpl()" || m_name == "getPImpl()") && return nothing, "getimpl_blacklist"

    contains(m_name, "connectStreamToCallback") && return nothing, "calls_deleted_function"
    contains(m_name, "registerCycleEstimator") && return nothing, "calls_deleted_function"
    contains(m_name, "connectHostFunction") && return nothing, "calls_deleted_function"

    out = "{ using namespace $(get_namespace(method));\n"

    args = get_function_args(method)
    num_args = length(args)
    num_required = num_args - optionals(args)
    if num_required == 0
        out = out * """JL$(base_var).method("$(julia_name)", []($(get_class_name(method))& cl) {return cl.$(name_small)();});\n"""
        num_required += 1
    end

    for cutoff in num_required:num_args
        # Do not add methods which contains arguments with `TypeTraits::isSimpleType`
        if !contains(arg_list(method, true, cutoff), "TypeTraits::isSimpleType")
            out = out * """JL$(base_var).method("$(julia_name)", []($(get_class_name(method))& cl, $(arg_list(method, true, cutoff))) {return cl.$(name_small)($(arg_list(method, false, cutoff)));});\n"""
        end
    end


    out = out * "}"


    if spelling(kind(method)) == "FunctionTemplate"
        if contains(out, "ArrayRef<T>")
            # Expand all references to ArrayRef<T> to containers of common types
            full = ""
            # Not all methods support the same types in `ArrayRef<T>`, so we need to do some
            # specialisation.
            _types = if julia_name in ("EngineReadTensor", "EngineWriteTensor", "EngineConnectStream", "EngineCopyFromRemoteBuffer")
                ("unsigned int", "int", "long", "float")
            else
                ("unsigned int", "int", "long", "float", "double")
            end
            arrayref_types = string.("ArrayRef<", _types, ">")
            for type in arrayref_types
                full *= replace(out, "ArrayRef<T>" => type)
            end
            return full, nothing
        elseif contains(out, r"GraphConnect\b")
            # Manually expand template in poplar::Graph::connect.  Ideally this
            # would be more automatic.
            full = ""
            for type in ("unsigned int", "int", "long", "float", "double")
                # Note: we have to prevent automatic argument conversion:
                # <https://github.com/JuliaInterop/CxxWrap.jl/blob/aec9d9975aec28e9046ad81e7038bbc5319963ea/README.md#automatic-argument-conversion>.
                full *= replace(out,
                                r"\bT\b" => "jlcxx::StrictlyTypedNumber<" * type * ">",
                                "a, b" => "a, b.value",
                                )
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

    out = "{ using namespace $(get_namespace(func));\n"
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
    parent_name = get_julia_name(Clang.getCursorSemanticParent(decl))
    return "mod.set_const(\"$parent_name$julia_name\", $full_name);", nothing
end


function gen_json(ctx::BindgenContext, decl, id, handled=false, not_handled_reason="")
    if not_handled_reason === nothing
        not_handled_reason = ""
    end

    decl_kind = kind(decl)
    spelling(decl_kind) ∈ ["EnumDecl", "ClassDecl", "StructDecl", "CXXMethod", "FunctionTemplate", "FunctionDecl", "CXXConstructor", "EnumConstantDecl"] || return
    fname = spelling(decl)

    tokenstr = ""
    for token in tokenize(decl)
        tokenstr *= token.text * " "
    end
    tokenstr = tokenstr[1:end-1]

    #if length(tokenstr) > 150
    #    tokenstr = tokenstr[1:150]
    #end

    d = Dict("Implemented" => handled, "Text" => tokenstr, "Namespace" => get_namespace(decl), "Token type" => spelling(decl_kind), "Name" => get_full_name(decl), "Filename" => fname, "FailureReason" => not_handled_reason)

    open("out.json", "a") do file
        write(file, JSON.json(d) * "\n")
    end
end


function iterate_children(ctx::BindgenContext, childvec::Vector{CLCursor})
    for (i, child) in enumerate(childvec)
        valid = true
        reason = nothing

        child_header = spelling(child)
        child_name = name(child)
        child_kind = kind(child)
        startswith(child_name, "__") && (valid = false; reason = "skip_compiler_definitions")  # skip compiler definitions
        child_header ∈ ctx.blacklisted_headers && (valid = false; reason = "header_blacklisted")

        !any(x -> startswith(get_namespace(child), x), allowed_namespaces) && (valid = false; reason = "not_allowed_namespace")

        child_id = get_full_name(child) * "__" * spelling(child_kind)
        child_id = replace(child_id, "poplar::StringRef" => "std::string")
        # child_id = replace(child_id, "StringRef" => "std::string")

        # prevents duplicate codegen(+error), TODO: check if still necessary
        child_id == "poplar::FieldData::SizeT::size()__CXXMethod" && (valid = false; reason = "filedata_size_blacklist")

        # Popops expressions are causing all kinds of problems
        contains(child_id, "expr::") && (valid = false; reason = "expr_blacklisted")
        contains(child_id, "popops::expr") && (valid = false; reason = "expr_blacklisted")

        # TODO: Find and document reason
        contains(child_id, "equivalent_device_type") && (valid = false; reason = "equivalent_device_type_blacklist")

        # workaround (returning vector of Device causes issues)
        contains(child_id, "getDevices") && (valid = false; reason = "getdevices_blacklist")

        # Skip everything related to poplar::core (like Target.getTargetOptions)
        contains(child_id, "core::") && (valid = false; reason = "core_blacklisted")
        contains(child_id, "getTargetOptions") && (valid = false; reason = "core_blacklisted")

        # These cause error
        #    error: static assertion failed: Mirrored types (marked with IsMirroredType) can't be added using add_type, map them directly to a struct instead and use map_type or explicitly disable mirroring for this type, e.g. define template<> struct IsMirroredType<Foo> : std::false_type { };
        contains(child_id, "poplar::VertexPerfEstimate::VertexPerfEstimate") && (valid = false; reason = "mirrored_type")
        contains(child_id, "poplar::ErrorLocationHash__StructDecl") && (valid = false; reason = "mirrored_type")

        # This conversion `ArrayRef<std::string>` to `ArrayRef<poplar::StringRef>` isn't handled correctly
        contains(child_id, "poplar::Graph::trace(ArrayRef<std::string>") && (valid = false; reason = "arrayrefstring_blacklisted")
        # contains(child_id, "trace(ArrayRef<std::string>") && (valid = false; reason = "arrayrefstring_blacklisted")

        # `DebugContext` constructors which cause ambiguous overload calls
        contains(child_id, r"^poplar::DebugContext::DebugContext.*__CXXConstructor$") && (valid = false; reason = "debugcontext_blacklisted")
        # contains(child_id, r"^DebugContext.*__CXXConstructor$") && (valid = false; reason = "debugcontext_blacklisted")

        # This causes the error
        #    no matching function for call to ‘poplar::program::Sequence::add_many(std::__cxx11::basic_string<char>&)’
        contains(child_id, r"poplar::program::Sequence::Sequence.*__CXXConstructor$") && (valid = false; reason = "programsequence_blacklisted")

        # Avoid duplicate definition during precompilation of the CxxWrap module
        contains(child_id, "poplar::layout::to_string(const poplar::layout::VectorList)__FunctionDecl") && (valid = false; reason = "duplicate_definition")
        # contains(child_id, "poplar::layout::to_string(const VectorList)__FunctionDecl") && (valid = false; reason = "duplicate_definition")

        # Avoid duplicate definition during precompilation of the CxxWrap module.
        # Ref: <https://github.com/JuliaIPU/IPUToolkit.jl/issues/12>.
        contains(child_id, "poplar::toString") && (valid = false; reason = "duplicate_definition")

        # error: invalid use of incomplete type ‘class pva::Report’
        contains(child_id, "poplar::Engine::getReport") && (valid = false; reason = "incomplete_type")
        # contains(child_id, "Engine::getReport") && (valid = false; reason = "incomplete_type")

        # error: invalid application of ‘sizeof’ to incomplete type ‘poplar::core::VertexIntrospector’
        contains(child_id, "poplar::VertexIntrospector") && (valid = false; reason = "incomplete_type")
        # contains(child_id, "VertexIntrospector") && (valid = false; reason = "incomplete_type")

        # error: invalid use of incomplete type ‘class poplar::Preallocations’
        contains(child_id, "poplar::Preallocations") && (valid = false; reason = "incomplete_type")
        # contains(child_id, "Preallocations") && (valid = false; reason = "incomplete_type")

        # error: no matching function for call to ‘poplar::GlobalExchangeConstraint::GlobalExchangeConstraint()’
        contains(child_id, "poplar::Target::getGlobalExchangeConstraints()__CXXMethod") && (valid = false; reason = "getGlobalExchangeConstraints_blacklisted")

        # These methods are handled incorrectly by this script and generate lines with
        # invalid syntax.  They don't seem to be super important, so let's just skip them
        # for the time being.
        contains(child_id, "poplar::Module::forEachLoadableSegment") && (valid = false; reason = "forEachLoadableSegment_blacklisted")
        contains(child_id, "poplar::Module::forEachSegment") && (valid = false; reason = "forEachSegment_blacklisted")

        # error: no match for call to ‘(poplar::Engine::copyToRemoteBuffer<unsigned int>::<lambda(unsigned int*)>) (gccs::ArrayRef<const unsigned int>::const_iterator)’
        contains(child_id, "poplar::Engine::copyToRemoteBuffer(ArrayRef<T>, std::string, uint64_t, unsigned int)__FunctionTemplate") && (valid = false; reason = "copyToRemoteBuffer_blacklisted")

        # IPUAttributes appears only in one method of Device.getAttribute, but it isn't
        # documented and it looks troublesome to support in a backward-compatible way, let's
        # just skip it.
        contains(child_id, "IPUAttributes") && (valid = false; reason = "IPUAttributes_blacklisted")

        # Sadly we aren't going to support quarter precision floating-point numbers anytime soon, so let's just skip this.
        contains(child_id, "QuarterMetadata") && (valid = false; reason = "QuarterMetadata_blacklisted")

        handled = false
        if !(child_id ∈ ctx.handled_symbols)
            if valid
                code, reason = nothing, nothing


                res = if spelling(child_kind) == "EnumDecl"
                    enum_decl_handler(ctx, child)
                elseif spelling(child_kind) == "ClassDecl"
                    object_decl_handler(ctx, child)
                elseif spelling(child_kind) == "StructDecl"
                    object_decl_handler(ctx, child)
                end

                if res !== nothing
                    code, reason = res
                    if code !== nothing
                        handled = true
                        ctx.outputDecls *= "// " * child_id * "\n" * code * "\n"
                        push!(ctx.handled_symbols, child_id)
                    end
                end


                res = if spelling(child_kind) == "CXXMethod"
                    method_handler(ctx, child)
                elseif spelling(child_kind) == "FunctionTemplate"
                    method_handler(ctx, child)
                elseif spelling(child_kind) == "FunctionDecl"
                    func_handler(ctx, child)
                elseif spelling(child_kind) == "CXXConstructor"
                    constructor_handler(ctx, child)
                elseif spelling(child_kind) == "EnumConstantDecl"
                    enum_const_handler(ctx, child)
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

function gen_bindings(headers::Vector{String}, blacklist::Vector{String})
    rm("out.json"; force=true)
    touch("out.json")

    # Automatically print out the includes of the header files we want to parse
    io = IOBuffer()
    for header in headers
        println(io, "#include <$(header)>")
    end

    includes = [joinpath(@__DIR__, "wrapper", "3.3", "include")]
    ctx = DefaultBindgenContext()
    ctx.searched_headers = resolve_headers(headers, includes)
    ctx.blacklisted_headers = resolve_headers(blacklist, includes)

    # bootstrap a Clang ASTUnit for parsing the headers
    flags = CXTranslationUnit_DetailedPreprocessingRecord |
            CXTranslationUnit_SkipFunctionBodies
    idx = Clang.Index()
    tus = []
    symbol_names = String[]
    # add compiler flags
    # clang_args = ["-I"*inc for inc in includes]
    # cross-compiling setup for DEBUG:
    args = get_default_args("x86_64-linux-gnu", is_cxx=true, version=v"9.1.0")
    append!(args, ["-I"*inc for inc in includes])
    push!(args, "-nostdinc++", "-nostdlib++")
    push!(args, "-xc++")
    # push!(args, "-v")
    clang_args = args
    for h in ctx.searched_headers
        tu = Clang.TranslationUnit(idx, h, clang_args, flags)
        push!(tus, tu)
    end

    for trans_unit in tus
        root_cursor = Clang.getTranslationUnitCursor(trans_unit)
        println(root_cursor)
        clang_children = children(root_cursor)
        iterate_children(ctx, clang_children)
    end

    return String(take!(io)), ctx.outputDecls * ctx.outputMembers, ctx.outputSupertypes
end

function generate_wrapper()
    gen_headers, gen_inline, gen_inherit = gen_bindings(
        [
            "poplar/VectorLayout.hpp",
            "poplar/DeviceManager.hpp",
            "poplar/Engine.hpp",
            "poplar/Graph.hpp",
            "poplar/CSRFunctions.hpp",
            "poplar/IPUModel.hpp",
            "popops/ElementWise.hpp",
            "popops/codelets.hpp",
        ],
        String[])
    #gen_inline = replace(gen_inline, "\n" => "\nprintf(\"Line is %d\\n\", __LINE__);\n")

    # Workaround for CxxWrap not liking any types name "Type"
    gen_inline = replace(gen_inline, "\"Type\"" => "\"Type_\"")

    dir = joinpath(@__DIR__, "wrapper")
    write(joinpath(dir, "gen_headers.hpp"), gen_headers)
    write(joinpath(dir, "gen_inline.cpp"), gen_inline)
    write(joinpath(dir, "gen_inherit.cpp"), gen_inherit)

    return nothing
end

generate_wrapper()
