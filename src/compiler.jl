# based on GPUCompiler example https://github.com/JuliaGPU/GPUCompiler.jl/blob/master/examples/kernel.jl
module IPUCompiler

using GPUCompiler
using Match

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

struct IPUCompilerParams <: AbstractCompilerParams end
GPUCompiler.runtime_module(::CompilerJob{<:Any,IPUCompilerParams}) = IpuRuntime

abstract type In end
abstract type Out end
abstract type InOut end

struct getVec{T} end

struct PoplarVec{T, T2} <: AbstractArray{T, 1}
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

@inline function getVec{PoplarVec{T, T2}}(arg::String, i::Int32)::PoplarVec where {T, T2}
    return PoplarVec{T, T2}(ccall(arg, llvmcall, Ptr{T}, (Int32, Int32), i, 0), ccall(arg, llvmcall, UInt32, (Int32, Int32), i, 1))
end

macro codelet(usr_kern)
    if usr_kern.head ∉ (:function, :(=)) || usr_kern.args[1].head !== :call
        throw(ArgumentError("@codelet takes a named function definition in input"))
    end
    name = usr_kern.args[1].args[1]
    func = eval(usr_kern)
    args = methods(func).ms[end].sig.parameters[2:end]

    kernargs = Expr[]
    i = Int32(0)

    funcname = "extern getVec" * String(name)

    for arg in args
        push!(kernargs, :($getVec{$arg}($funcname, Int32($i))))
        i += Int32(1)
    end
    kern_call = Expr(:call, :($func), kernargs...)

    return quote

        function $(esc(name))()
            $kern_call
            return nothing
        end
        build_codelet($(esc(name)), String(nameof($(esc(name)))), $usr_kern)
    end
end

function build_codelet(kernel, name, origKernel)
    args = methods(origKernel).ms[end].sig.parameters[2:end]

    # There doesn't seem to be a nicer way to do this
    argnames = split(methods(origKernel).ms[end].slot_syms, "\0")[2:methods(origKernel).ms[end].nargs]

    output_path = name * ".gp"
    source = FunctionSpec(kernel)

    target = NativeCompilerTarget()
    params = IPUCompilerParams()
    job = CompilerJob(target, source, params, :func)

    llvm_ir = JuliaContext() do ctx
        string(GPUCompiler.compile(:llvm, job; ctx)[1])
    end

    kernel_name = match(Regex("(_Z[0-9]+jfptr_$(kernel)_[0-9]+)"), llvm_ir)[1]

    mktempdir() do dir
        open(joinpath(dir, "gen_codelet.txt"), "w") do io
            for i in 1:length(args)
                @match args[i] begin
                    PoplarVec{Int32, In} => println(io, "poplar::Input<poplar::Vector<int>> $(argnames[i]);")
                    PoplarVec{Float32, In} => println(io, "poplar::Input<poplar::Vector<float>> $(argnames[i]);")
                    PoplarVec{Int32, Out} => println(io, "poplar::Output<poplar::Vector<int>> $(argnames[i]);")
                    PoplarVec{Float32, Out} => println(io, "poplar::Output<poplar::Vector<float>> $(argnames[i]);")

                    PoplarVec{Int32, InOut} => println(io, "poplar::InOut<poplar::Vector<int>> $(argnames[i]);")
                    PoplarVec{Float32, InOut} => println(io, "poplar::InOut<poplar::Vector<float>> $(argnames[i]);")
                end
            end
        end

        input_file = joinpath(dir, "$(name).ll")
        write(input_file, llvm_ir)

        run(`popc -g -O0 -X -Wno-override-module -X -Qunused-arguments -DGET_VEC_NAME=getVec$(name) -DCLASS_NAME=$(name) -DFIRST_NAME=$(argnames[1]) -DKERNEL_NAME=$(kernel_name) -I$(dir) $(input_file) $(joinpath(@__DIR__, "codelet_gen.cpp")) -o $(output_path)`)
    end
end

end # module IPUCompiler
