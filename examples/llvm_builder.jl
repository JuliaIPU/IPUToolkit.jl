# based on GPUCompiler example https://github.com/JuliaGPU/GPUCompiler.jl/blob/master/examples/kernel.jl
module llvmBuilder
using GPUCompiler
using StaticArrays
using Match

module IpuRuntime


    # dummy methods
    signal_exception() = return

    # Todo: box/unbox for allowing proper type conversion
    # https://github.com/JuliaGPU/CUDAnative.jl/blob/a15d2db96274948d8090457a001e62e14be0d883/src/device/runtime.jl
    #function malloc(sz::Csize_t) 
    #    return ccall("extern fake_malloc", llvmcall, Int64, (Csize_t,), sz)
    #end


    report_oom(sz) = return
    report_exception(ex) = return
    report_exception_name(ex) = return
    report_exception_frame(idx, func, file, line) = return
end

struct TestCompilerParams <: AbstractCompilerParams end
GPUCompiler.runtime_module(::CompilerJob{<:Any,TestCompilerParams}) = IpuRuntime

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


macro Codelet(name, usr_kern)
    func = eval(usr_kern)
    args = methods(func).ms[end].sig.parameters[2:end]
    
    kernargs = []
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
        $buildCodelet($(esc(name)), String(nameof($(esc(name)))), $usr_kern)
    end
end


function buildCodelet(kernel, name, origKernel=function ()end)
    args = methods(origKernel).ms[end].sig.parameters[2:end]

    # There doesn't seem to be a nicer way to do this
    argnames = split(methods(origKernel).ms[end].slot_syms, "\0")[2:methods(origKernel).ms[end].nargs]

    open("gen_codelet.txt", "w") do io
        for i in 1:length(args)
            @match args[i] begin
            PoplarVec{Int32, In} => write(io, "poplar::Input<poplar::Vector<int>> $(argnames[i]);\n")
            PoplarVec{Float32, In} => write(io, "poplar::Input<poplar::Vector<float>> $(argnames[i]);\n")
            PoplarVec{Int32, Out} => write(io, "poplar::Output<poplar::Vector<int>> $(argnames[i]);\n")
            PoplarVec{Float32, Out} => write(io, "poplar::Output<poplar::Vector<float>> $(argnames[i]);\n")

                PoplarVec{Int32, InOut} => write(io, "poplar::InOut<poplar::Vector<int>> $(argnames[i]);\n")
                PoplarVec{Float32, InOut} => write(io, "poplar::InOut<poplar::Vector<float>> $(argnames[i]);\n")
            end
        end
    end


    outputPath = name * ".gp"
    source = FunctionSpec(kernel)

    target = NativeCompilerTarget()
    params = TestCompilerParams()
    job = CompilerJob(target, source, params)

    
    output = ""
    try
        output = string(GPUCompiler.compile(:llvm, job)[1])
    catch
        GPUCompiler.@device_code_warntype GPUCompiler.compile(:llvm, job)
    end

    kernel_name = match(Regex("(_Z[0-9]+julia_$(Symbol(kernel))_[0-9]+)"), output)[1]


    open("julia-code.ll", "w") do io
        write(io, output)
    end;

    run(`popc -g -O0 -X -Wno-override-module -X -Qunused-arguments -DGET_VEC_NAME=getVec$name -DCLASS_NAME=$name -DFIRST_NAME=$(argnames[1]) -DKERNEL_NAME=$kernel_name julia-code.ll codelet_gen.cpp -o $outputPath`)
end

end
