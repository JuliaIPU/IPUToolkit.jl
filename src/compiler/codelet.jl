using ProgressMeter

export @codelet

"""
    $(@__MODULE__).PROGRESS_SPINNER::$(typeof(PROGRESS_SPINNER))

Option to control whether to display a spinner to show progress during compilation of IPU codelets.

## Example

```julia
$(@__MODULE__).PROGRESS_SPINNER[] = true  # enable spinner, default
$(@__MODULE__).PROGRESS_SPINNER[] = false # disable spinner
```
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

"""
    @codelet graph <function definition>

Define a codelet and add it to the `graph`.
The `@codelet` macro takes two argument:

* the graph to which to add the codelet with the [`Poplar.GraphAddCodelets`](https://docs.graphcore.ai/projects/poplar-api/en/3.2.0/poplar/graph/Graph.html#_CPPv4N6poplar5Graph11addCodeletsE9StringRef15CodeletFileType9StringRef9StringRef) function;
* the function definition of the codelet that you want to compile for the IPU device.

All the arguments of the function must be [`VertexVector`](@ref)s, which represent the [`Vector`](https://docs.graphcore.ai/projects/poplar-user-guide/en/3.2.0/vertex_vectors.html) vertex type in the Poplar SDK.

`@codelet` defines the function passed as argument, generates its LLVM Intermediate Representation (IR) using `GPUCompiler.jl` and then compiles it down to native code using the Poplar compiler `popc`, which must be in [`PATH`](https://en.wikipedia.org/wiki/PATH_(variable)).
By default the LLVM IR of the function is written to a temporary file, but you can choose to keep it in the current directory by customising [`IPUCompiler.KEEP_LLVM_FILES`](@ref).
You can control flags passed to the `popc` compiler like debug and optimisation levels or target types by customising [`IPUCompiler.POPC_FLAGS`](@ref).
During compilation of codelets a spinner is displayed to show the progress, as this step can take a few seconds for each codelet to be generated.
This can be disabled by setting [`IPUCompiler.PROGRESS_SPINNER`](@ref).
All the options mentioned in this section have to be set before the `@codelet` invocation where you want them to have effect.

The codelet is automatically added to the graph but you will have to separately use it in a vertex, by using either the [`add_vertex`](@ref) function, or Poplar's [`Poplar.GraphAddVertex`](https://docs.graphcore.ai/projects/poplar-api/en/3.2.0/poplar/graph/Graph.html#_CPPv4N6poplar5Graph9addVertexE10ComputeSet9StringRef).

## Example

```julia
using IPUToolkit.IPUCompiler, IPUToolkit.Poplar
device = Poplar.get_ipu_device()
target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)
@codelet graph function test(in::VertexVector{Int32,In}, out::VertexVector{Float32,Out})
    for idx in eachindex(out)
        out[idx] = sin(in[idx])
    end
end
```

This snippet of code defines a codelet called `test`, which takes in input the vector `in`, whose elements are `Int32`s, and modifies the vector `out`, of type `Float32`, by computing the sine of the elements of `in`.
"""
macro codelet(graph, usr_kern::Expr)
    return _codelet(graph, usr_kern)
end

# We have experienced some miscompilations of LLVM IR when using optimisation levels `-O1`
# or higher with old `popc`, especially v1.3-2.0.  So, we default to `-O0` with older
# versions, and `-O3` for newer versions.
"""
    $(@__MODULE__).POPC_FLAGS::$(typeof(POPC_FLAGS))

Options to pass to the `popc` compiler to compile the code.

## Example

```julia
$(@__MODULE__).POPC_FLAGS = `-O3 -g0 -target ipu2`
$(@__MODULE__).POPC_FLAGS = `-O2 -g`
```
"""
const POPC_FLAGS = Ref(Poplar.SDK_VERSION ≥ v"2.2.0" ? `-g -O3` : `-g -O0`)

"""
    $(@__MODULE__).KEEP_LLVM_FILES::$(typeof(KEEP_LLVM_FILES))

Option to control whether to keep in the current directory the files with the LLVM Intermediate Representation (IR) generated for the codelets.

## Example

```julia
$(@__MODULE__).KEEP_LLVM_FILES[] = false # Generated LLVM IR files are automatically deleted after compilation, default
$(@__MODULE__).KEEP_LLVM_FILES[] = true  # Generated LLVM IR files are kept in the current directory
```
"""
const KEEP_LLVM_FILES = Ref(false)

_print_s(::Type{In}) = "Input"
_print_s(::Type{Out}) = "Output"
_print_s(::Type{InOut}) = "InOut"
_print_t(::Type{Int32}) = "int"
_print_t(::Type{UInt32}) = "unsigned int"
_print_t(::Type{Float16}) = "half"
_print_t(::Type{Float32}) = "float"
_print_vec(io::IO, ::Type{VertexVector{T, S}}, name::String) where {T,S} = println(io, "poplar::", _print_s(S), "<poplar::Vector<", _print_t(T), ">> ", name, ";")

function __build_codelet(graph::Poplar.GraphAllocated, kernel, name::String, origKernel::Function)
    target = NativeCompilerTarget()
    source = methodinstance(typeof(kernel), Tuple{})
    params = IPUCompilerParams(name)
    config = CompilerConfig(target, params)
    job = CompilerJob(source, config)
    llvm_ir = JuliaContext() do ctx
        string(GPUCompiler.compile(:llvm, job; ctx)[1])
    end
    # For some reasons the Colossus intrinsics names get dots converted into underscores:
    # <https://github.com/JuliaGPU/GPUCompiler.jl/issues/464>.  Let's convert them back to
    # dots before writing the file to disk.
    llvm_ir = replace(llvm_ir,
                      "_llvm_colossus_get_scount_l" => "llvm.colossus.get.scount.l",
                      "_llvm_colossus_get_tile_id" => "llvm.colossus.get.tile.id",
                      "_llvm_colossus_urand_f16" => "llvm.colossus.urand.f16",
                      "_llvm_colossus_urand_f32" => "llvm.colossus.urand.f32",
                      "_llvm_colossus_urand32" => "llvm.colossus.urand32",
                      "_llvm_colossus_urand64" => "llvm.colossus.urand64",
                      )
    # Do not allow references to literal pointers, which are likely to be invalid on the IPU
    if contains(llvm_ir, r"inttoptr +\(i64 +\d+")
        error("LLVM IR generated for codelet $(name) contains a reference to a literal pointer")
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

        input_file = joinpath(KEEP_LLVM_FILES[] ? "" : dir, "$(name).ll")
        write(input_file, llvm_ir)

        # Unless `POPC_FLAGS[]` already sets `-target`, if we have calls to Colossus
        # intrinsics we can't target the IPU model on CPU (the `cpu` target), so in that
        # case we compile only for `ipu1,ipu2`.
        target = if !any(contains("-target"), POPC_FLAGS[].exec) && contains(llvm_ir, "@llvm.colossus.")
            `-target ipu1,ipu2`
        else
            ``
        end

        run(```
            popc
            $(POPC_FLAGS[])
            $(target)
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

function _build_codelet(graph::Poplar.GraphAllocated, kernel, name::String, origKernel::Function)
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
