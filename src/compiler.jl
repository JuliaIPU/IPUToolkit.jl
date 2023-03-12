# based on GPUCompiler example https://github.com/JuliaGPU/GPUCompiler.jl/blob/master/examples/kernel.jl
module IPUCompiler

using GPUCompiler
using Match
using ..Poplar

module IpuRuntime

# dummy methods
signal_exception() = nothing

# Todo: box/unbox for allowing proper type conversion
# https://github.com/JuliaGPU/CUDAnative.jl/blob/a15d2db96274948d8090457a001e62e14be0d883/src/device/runtime.jl
malloc(sz) = C_NULL

report_oom(sz) = nothing
report_exception(ex) = nothing
report_exception_name(ex) = nothing
report_exception_frame(idx, func, file, line) = nothing

end # module IpuRuntime

struct IPUCompilerParams <: AbstractCompilerParams
    kernel_name::String
end
GPUCompiler.runtime_module(::CompilerJob{<:Any,IPUCompilerParams}) = IpuRuntime
# `GPUCompiler.isintrinsic` specifies functions which are to be considered intrinsics for
# the current job, and so don't have to be validated by the compilation pipeline.  We set
# `getVec$(kernel_name)` to be considered intrinsic, as this is implemented in the
# accompanying C++ codelet, so outside of the LLVM IR generated by GPUCompiler.
GPUCompiler.isintrinsic(@nospecialize(job::CompilerJob{<:Any,IPUCompilerParams}), fn::String) =
    contains(fn, Regex("^get_vec_(ptr|size)_" * job.params.kernel_name * "\$"))

abstract type In end
abstract type Out end
abstract type InOut end

struct PoplarVec{T, T2} <: AbstractVector{T}
    base::Ptr{T}
    size::UInt32
end

function Base.setindex!(vec::PoplarVec, f, i::Int)
    unsafe_store!(vec.base, f, i)
end

function Base.getindex(vec::PoplarVec, i::Int)
    return unsafe_load(vec.base, i)
end

function Base.size(vec::PoplarVec)
    return (Int(vec.size),)
end

function Base.copyto!(dest::PoplarVec, src::PoplarVec)
    for i in 1:length(src)
        dest[i] = src[i]
    end
end

# TODO: significantly decreases codesize if set to false but might be actually needed sometimes
@inline function Base.mightalias(A::PoplarVec, B::PoplarVec)
    return false
end

# In Julia v1.9 the default algorithm for sorting arrays requires a scratch area, but we
# can't use it on an IPU because it'd need to allocate an extra array, so let's default to
# the simple fully in-place `QuickSort`.
if VERSION ≥ v"1.9.0-"
    Base.Sort.defalg(::PoplarVec) = QuickSort
end

macro codelet(usr_kern)
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
            $(arg.args[2])($(Expr(:call, :ccall, func_ptr,  :llvmcall, Ptr{getfield(@__MODULE__, arg.args[2].args[2])}, :((Int32,)), Int32((i += one(i))))),
                           $(Expr(:call, :ccall, func_size, :llvmcall, UInt32,                                          :((Int32,)), Int32((i)),         )))
        ))
        for arg in args]
    kern_call = Expr(:call, :($(esc(name))), kernargs...)

    return quote
        let
            $(esc(usr_kern))
            function $(codelet_fun)()
                $(kern_call)
                return $(esc(nothing))
            end
            build_codelet($(codelet_fun), $(String(name)), $(esc(name)))
        end
    end
end

# We have experienced some miscompilations of LLVM IR when using optimisation levels `-O1`
# or higher with old `popc`, especially v1.3-2.0.  So, we default to `-O0` with older
# versions, and `-O3` for newer versions.
const POPC_FLAGS = Poplar.SDK_VERSION ≥ v"2.2.0" ? `-g -O3` : `-g -O0`

function build_codelet(kernel, name, origKernel)
    target = NativeCompilerTarget()
    source = FunctionSpec(typeof(kernel))
    params = IPUCompilerParams(name)
    job = CompilerJob(target, source, params, :func)
    llvm_ir = JuliaContext() do ctx
        string(GPUCompiler.compile(:llvm, job; ctx)[1])
    end

    args = methods(origKernel).ms[end].sig.parameters[2:end]
    # There doesn't seem to be a nicer way to do this
    argnames = split(methods(origKernel).ms[end].slot_syms, "\0")[2:methods(origKernel).ms[end].nargs]

    kernel_name = match(Regex("(_Z[\\d]+jfptr[\\d_]+$(name)[\\d_]+)"), llvm_ir)[1]

    # Create codelet file in temporary directory, so taht we don't pollute the
    # file system with codelet files everywhere.
    output_path = joinpath(mktempdir(), name * ".gp")

    mktempdir() do dir
        open(joinpath(dir, "gen_codelet.cpp"), "w") do io
            for i in 1:length(args)
                @match args[i] begin
                    PoplarVec{Int32, In} => println(io, "poplar::Input<poplar::Vector<int>> $(argnames[i]);")
                    PoplarVec{Float16, In} => println(io, "poplar::Input<poplar::Vector<half>> $(argnames[i]);")
                    PoplarVec{Float32, In} => println(io, "poplar::Input<poplar::Vector<float>> $(argnames[i]);")

                    PoplarVec{Int32, Out} => println(io, "poplar::Output<poplar::Vector<int>> $(argnames[i]);")
                    PoplarVec{Float16, Out} => println(io, "poplar::Output<poplar::Vector<half>> $(argnames[i]);")
                    PoplarVec{Float32, Out} => println(io, "poplar::Output<poplar::Vector<float>> $(argnames[i]);")

                    PoplarVec{Int32, InOut} => println(io, "poplar::InOut<poplar::Vector<int>> $(argnames[i]);")
                    PoplarVec{Float16, InOut} => println(io, "poplar::InOut<poplar::Vector<half>> $(argnames[i]);")
                    PoplarVec{Float32, InOut} => println(io, "poplar::InOut<poplar::Vector<float>> $(argnames[i]);")
                end
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

    return output_path
end

# Mapping of the LLVM version used by each version of the Poplar SDK.  To find it, use `popc
# --version`.
const POPLAR_SDK_LLVM_MAPPING = Dict(
    v"1.3.0" => v"11.0.0",
    v"1.4.0" => v"11.0.0",
    v"2.0.0" => v"11.0.0",
    v"2.1.0" => v"13.0.0",
    v"2.2.0" => v"13.0.0",
    v"2.3.0" => v"14.0.0",
    v"2.4.0" => v"14.0.0",
    v"2.5.0" => v"14.0.0",
    v"2.6.0" => v"15.0.0",
    v"3.0.0" => v"15.0.0",
)

function __init__()
    sdk_llvm_version = POPLAR_SDK_LLVM_MAPPING[Base.thisminor(Poplar.SDK_VERSION)]
    if sdk_llvm_version != Base.thismajor(Base.libllvm_version)
        @warn """
              You are using Poplar SDK v$(Poplar.SDK_VERSION) which is coupled to LLVM v$(sdk_llvm_version), but your Julia uses LLVM v$(Base.libllvm_version).
              IPUCompiler code generation may not work correctly.
              """
    end
end

end # module IPUCompiler
