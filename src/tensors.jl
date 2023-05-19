# Scope of the vectors in codelets.  These singletons are used only for dispatch.
struct In end
struct Out end
struct InOut end

struct PoplarTensor{T, N, S} <: AbstractArray{T, N}
    base::Ptr{T}
    size::NTuple{N,Int}
    length::UInt32
end
const PoplarVector{T,S} = PoplarTensor{T,1,S}
const PoplarMatrix{T,S} = PoplarTensor{T,2,S}

PoplarTensor{T,N,S}(::UndefInitializer, size::Vararg{Int,N}) where {T,N,S} =
    PoplarTensor{T,N,S}(C_NULL, size, prod(size))
PoplarTensor{T,N,S}(::UndefInitializer, size::NTuple{N,Int}) where {T,N,S} =
    PoplarTensor{T,N,S}(C_NULL, size, prod(size))

function Base.setindex!(vec::PoplarVector, f, i::Int)
    unsafe_store!(vec.base, f, i)
end

function Base.getindex(vec::PoplarVector, i::Int)
    return unsafe_load(vec.base, i)
end

Base.size(t::PoplarTensor) = t.size
Base.size(t::PoplarTensor, d::Int) = t.size[d]

function Base.copyto!(dest::PoplarTensor, src::PoplarTensor)
    for i in 1:src.length
        dest[i] = src[i]
    end
end

# TODO: significantly decreases codesize if set to false but might be actually needed sometimes
@inline function Base.mightalias(A::PoplarTensor, B::PoplarTensor)
    return false
end

# In Julia v1.9 the default algorithm for sorting arrays requires a scratch area, but we
# can't use it on an IPU because it'd need to allocate an extra array, so let's default to
# the simple fully in-place `QuickSort`.
if VERSION ≥ v"1.9.0-"
    Base.Sort.defalg(::PoplarTensor) = QuickSort
end

# Simple methods, don't access the elements
Base.show(io::IO, x::PoplarTensor) = Base.show_default(io, x)
Base.show(io::IO, ::MIME"text/plain", x::PoplarTensor) = Base.show_default(io, x)

_similar(v::PoplarTensor{T}) where {T} = Array{T}(undef, v.size)
