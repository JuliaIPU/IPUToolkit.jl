using ProgressMeter

"""
    $(@__MODULE__).PROGRESS_SPINNER::$(typeof(PROGRESS_SPINNER))

Option to control whether to display a spinner to show progress during compilation of IPU codelets.
"""
const PROGRESS_SPINNER = Ref(true)

function _codelet(graph, usr_kern::Expr)
    if usr_kern.head ∉ (:function, :(=)) || usr_kern.args[1].head !== :call
        throw(ArgumentError("@codelet takes a named function definition in input"))
    end

    name = usr_kern.args[1].args[1]
    args = usr_kern.args[1].args[2:end]
    codelet_fun = gensym(name)
    func_ptr = "extern get_vec_ptr_" * String(name)
    func_size = "extern get_vec_size_" * String(name)
    i = Int32(-1)
    kernargs = [
        # TODO: I'd really like to avoid that `getfield`.
        esc(:(
            $(arg.args[2])( # VertexVector{T,S}
                $(Expr(:call, :ccall, func_ptr,  :llvmcall, Ptr{getfield(@__MODULE__, arg.args[2].args[2])}, :((Int32,)), i += one(i))), # base::Ptr{T}
                $(Expr(:call, :ccall, func_size, :llvmcall, UInt32,                                          :((Int32,)), i,          )) # length::UInt32
                            )
        ))
        for arg in args]
    kern_call = Expr(:call, :($(esc(name))), kernargs...)

    return quote
        $(esc(usr_kern))
        function $(codelet_fun)()
            $(kern_call)
            return $(esc(nothing))
        end
        _build_codelet($(esc(graph)), $(codelet_fun), $(String(name)), $(esc(name)))
    end
end

macro codelet(graph, usr_kern::Expr)
    return _codelet(graph, usr_kern)
end

# We have experienced some miscompilations of LLVM IR when using optimisation levels `-O1`
# or higher with old `popc`, especially v1.3-2.0.  So, we default to `-O0` with older
# versions, and `-O3` for newer versions.
const POPC_FLAGS = Poplar.SDK_VERSION ≥ v"2.2.0" ? `-g -O3` : `-g -O0`

_print_s(::Type{In}) = "Input"
_print_s(::Type{Out}) = "Output"
_print_s(::Type{InOut}) = "InOut"
_print_t(::Type{Int32}) = "int"
_print_t(::Type{Float16}) = "half"
_print_t(::Type{Float32}) = "float"
_print_vec(io::IO, ::Type{VertexVector{T, S}}, name::String) where {T,S} = println(io, "poplar::", _print_s(S), "<poplar::Vector<", _print_t(T), ">> ", name, ";")

function __build_codelet(graph, kernel, name, origKernel)
    target = NativeCompilerTarget()
    source = methodinstance(typeof(kernel), Tuple{})
    params = IPUCompilerParams(name)
    config = CompilerConfig(target, params)
    job = CompilerJob(source, config)
    llvm_ir = JuliaContext() do ctx
        string(GPUCompiler.compile(:llvm, job; ctx)[1])
    end

    method = methods(origKernel)[end]
    args = method.sig.parameters[2:end]
    argnames = string.(Base.method_argnames(method)[2:end])

    kernel_name = match(Regex("(_Z[\\d_]+$(name)[\\d_]+)"), llvm_ir)[1]

    # Create codelet file in temporary directory, so taht we don't pollute the
    # file system with codelet files everywhere.
    output_path = joinpath(mktempdir(), name * ".gp")

    mktempdir() do dir
        open(joinpath(dir, "gen_codelet.cpp"), "w") do io
            for i in 1:length(args)
                _print_vec(io, args[i], argnames[i])
            end
        end

        input_file = joinpath(dir, "$(name).ll")
        write(input_file, llvm_ir)

        run(```
            popc
            $(POPC_FLAGS)
            -X -Wno-override-module
            -X -Qunused-arguments
            -DGET_VEC_PTR_NAME=get_vec_ptr_$(name)
            -DGET_VEC_SIZE_NAME=get_vec_size_$(name)
            -DCLASS_NAME=$(name)
            -DFIRST_NAME=$(argnames[1])
            -DKERNEL_NAME=$(kernel_name)
            -I$(dir)
            $(input_file)
            $(joinpath(@__DIR__, "codelet_gen.cpp"))
            -o $(output_path)
            ```)
    end

    Poplar.GraphAddCodelets(graph, output_path)
    return nothing
end

function _build_codelet(graph, kernel, name, origKernel)
    if PROGRESS_SPINNER[]
        prog = ProgressUnknown("Compiling codelet $(name):"; spinner=true)
        task = Threads.@spawn __build_codelet(graph, kernel, name, origKernel)
        while !istaskdone(task)
            ProgressMeter.next!(prog; spinner="⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏")
            sleep(0.1)
        end
        ProgressMeter.finish!(prog)
        fetch(task)
    else
        __build_codelet(graph, kernel, name, origKernel)
    end
end
