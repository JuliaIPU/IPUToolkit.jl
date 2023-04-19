# Scope of the vectors in codelets.  These singletons are used only for dispatch.
struct In end
struct Out end
struct InOut end

struct PoplarVec{T, S} <: AbstractVector{T}
    base::Ptr{T}
    size::UInt32
end

PoplarVec{T, S}(::UndefInitializer, size) where {T, S} =
    PoplarVec{T, S}(C_NULL, size)

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

# Simple methods, don't access the elements
Base.show(io::IO, x::PoplarVec) = Base.show_default(io, x)
Base.show(io::IO, ::MIME"text/plain", x::PoplarVec) = Base.show_default(io, x)
