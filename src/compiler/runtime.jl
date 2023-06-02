module IPURuntime

import ..IPUCompiler: @device_override, @ipuprintf, @ipuprintln, get_scount_l, get_tile_id
using GPUCompiler: reset_runtime
import LinearAlgebra

# reset the runtime cache from global scope, so that any change triggers recompilation
reset_runtime()

# dummy methods
signal_exception() = nothing

# Todo: box/unbox for allowing proper type conversion
# https://github.com/JuliaGPU/CUDAnative.jl/blob/a15d2db96274948d8090457a001e62e14be0d883/src/device/runtime.jl
malloc(sz) = C_NULL

function report_oom(sz)
    @ipuprintf("ERROR: Out of memory (trying to allocate %i bytes)\n", sz)
    return nothing
end

function report_exception(ex)
    @ipuprintf("ERROR: a %s was thrown during kernel execution.", ex)
    return nothing
end

function report_exception_name(ex)
    @ipuprintf("""
               ERROR: a %s was thrown during kernel execution.
               Stacktrace:
               """, ex)
    return nothing
end

function report_exception_frame(idx, func, file, line)
    @ipuprintf(" [%i] %s at %s:%i\n", idx, func, file, line)
    return nothing
end

# IPU builtins: https://docs.graphcore.ai/projects/poplar-api/en/latest/ipu_intrinsics/ipu_builtins.html
get_scount_l() = ccall("extern @llvm.colossus.get.scount.l",  llvmcall, Cuint, ())
get_tile_id() = ccall("extern @llvm.colossus.get.tile.id",  llvmcall, Cuint, ())
# Random functions, based on IPU intrinsics
Base.rand(T::Type{Float16}) = ccall("extern @llvm.colossus.urand.f16",  llvmcall, Float16, ()) + T(0.5)
Base.rand(T::Type{Float32}) = ccall("extern @llvm.colossus.urand.f32",  llvmcall, Float32, ()) + T(0.5)
Base.rand(T::Type{UInt32}) = ccall("extern @llvm.colossus.urand32",  llvmcall, UInt32, ()) + T(0.5)
Base.rand(T::Type{UInt64}) = ccall("extern @llvm.colossus.urand64",  llvmcall, UInt64, ()) + T(0.5)

# Math functions.  These methods are implemented internally by promoting arguments to double
# precisions, which is either horribly slow on the IPU (doubles are implemented in software)
# or require missing LLVM intrinsics.
@device_override Base.sin(x::Float32) = ccall("llvm.sin.f32", llvmcall, Float32, (Float32,), x)
@device_override Base.cos(x::Float32) = ccall("llvm.cos.f32", llvmcall, Float32, (Float32,), x)
@device_override Base.tan(x::Float32) = ccall("extern tanf",  llvmcall, Float32, (Float32,), x)
@device_override Base.:^(x::Float32, p::Integer) = ccall("llvm.pow.f32",  llvmcall, Float32, (Float32, Float32), x, p)

## quirks, adapted from
## https://github.com/JuliaGPU/CUDA.jl/blob/5c51766d0a9e7819ea79f314e37ed6a8a5d24369/src/device/quirks.jl
macro print_and_throw(args...)
    esc(quote
            @ipuprintln "ERROR: " $(args...) "."
            throw(nothing)
        end)
end

# math.jl
@device_override @noinline Base.Math.throw_complex_domainerror(f::Symbol, x) =
    @print_and_throw "This operation requires a complex input to return a complex result"
@device_override @noinline Base.Math.throw_exp_domainerror(x) =
    @print_and_throw "Exponentiation yielding a complex result requires a complex argument"

# intfuncs.jl
@device_override @noinline Base.throw_domerr_powbysq(::Any, p) =
    @print_and_throw "Cannot raise an integer to a negative power"
@device_override @noinline Base.throw_domerr_powbysq(::Integer, p) =
    @print_and_throw "Cannot raise an integer to a negative power"
@device_override @noinline Base.throw_domerr_powbysq(::AbstractMatrix, p) =
    @print_and_throw "Cannot raise an integer to a negative power"
@device_override @noinline Base.__throw_gcd_overflow(a, b) =
    @print_and_throw "gcd overflow"

# boot.jl
@device_override @noinline Core.throw_inexacterror(f::Symbol, ::Type{T}, val) where {T} =
    @print_and_throw "Inexact conversion"

# abstractarray.jl
@device_override @noinline Base.throw_boundserror(A, I) =
    @print_and_throw "Out-of-bounds array access"

# trig.jl
@device_override @noinline Base.Math.sincos_domain_error(x) =
    @print_and_throw "sincos(x) is only defined for finite x, x = " x
@device_override @noinline Base.Math.acos_domain_error(x) =
    @print_and_throw "acos(x) not defined for |x| > 1, x = " x
@device_override @noinline Base.Math.asin_domain_error(x) =
    @print_and_throw "asin(x) not defined for |x| > 1, x = " x

# range.jl
@static if VERSION >= v"1.7-"
    @eval begin
        @device_override function Base.StepRangeLen{T,R,S,L}(ref::R, step::S, len::Integer,
                                                             offset::Integer=1) where {T,R,S,L}
            if T <: Integer && !isinteger(ref + step)
                @print_and_throw("StepRangeLen{<:Integer} cannot have non-integer step")
            end
            len = convert(L, len)
            len >= zero(len) || @print_and_throw("StepRangeLen length cannot be negative")
            offset = convert(L, offset)
            L1 = oneunit(typeof(len))
            L1 <= offset <= max(L1, len) || @print_and_throw("StepRangeLen: offset must be in [1,...]")
            $(
                Expr(:new, :(StepRangeLen{T,R,S,L}), :ref, :step, :len, :offset)
            )
        end
    end
else
    @device_override function Base.StepRangeLen{T,R,S}(ref::R, step::S, len::Integer,
                                                       offset::Integer=1) where {T,R,S}
        if T <: Integer && !isinteger(ref + step)
            @print_and_throw("StepRangeLen{<:Integer} cannot have non-integer step")
        end
        len >= 0 || @print_and_throw("StepRangeLen length cannot be negative")
        1 <= offset <= max(1,len) || @print_and_throw("StepRangeLen: offset must be in [1,...]")
        new(ref, step, len, offset)
    end
end

# LinearAlgebra
@static if VERSION >= v"1.8-"
    @device_override function Base.setindex!(D::LinearAlgebra.Diagonal, v, i::Int, j::Int)
        @boundscheck checkbounds(D, i, j)
        if i == j
            @inbounds D.diag[i] = v
        elseif !iszero(v)
            @print_and_throw("cannot set off-diagonal entry to a nonzero value")
        end
        return v
    end
end

# fastmath.jl
@static if VERSION <= v"1.7-"
## prevent fallbacks to libm
for f in (:acosh, :asinh, :atanh, :cbrt, :cosh, :exp2, :expm1, :log1p, :sinh, :tanh)
    f_fast = Base.FastMath.fast_op[f]
    @eval begin
        @device_override Base.FastMath.$f_fast(x::Float32) = $f(x)
        @device_override Base.FastMath.$f_fast(x::Float64) = $f(x)
    end
end
end

end # module IPURuntime
