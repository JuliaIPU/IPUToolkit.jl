module IPURuntime

using ..IPUCompiler: @device_override

# dummy methods
signal_exception() = nothing

# Todo: box/unbox for allowing proper type conversion
# https://github.com/JuliaGPU/CUDAnative.jl/blob/a15d2db96274948d8090457a001e62e14be0d883/src/device/runtime.jl
malloc(sz) = C_NULL

report_oom(sz) = nothing
report_exception(ex) = nothing
report_exception_name(ex) = nothing
report_exception_frame(idx, func, file, line) = nothing

# Define symbol for throwing errors
@device_override @noinline Base.throw_boundserror(A, I) = throw(nothing)

# Math functions
@device_override Base.sin(x::Float32) = ccall("llvm.sin.f32", llvmcall, Float32, (Float32,), x)
@device_override Base.cos(x::Float32) = ccall("llvm.cos.f32", llvmcall, Float32, (Float32,), x)

end # module IPURuntime
