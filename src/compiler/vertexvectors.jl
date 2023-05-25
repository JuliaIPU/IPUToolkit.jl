# Vectors to be used in codelets (vertices).  They are the counterpart of the vertex vector
# types
# (<https://docs.graphcore.ai/projects/poplar-user-guide/en/3.2.0/vertex_vectors.html>).
# NOTE: these are distincts from `PoplarArrays` because they represent the variables you can
# add to a graph.

# Scope of the vectors in codelets.  These singletons are used only for dispatch.
struct In end
struct Out end
struct InOut end

struct VertexVector{T, S} <: AbstractVector{T}
    base::Ptr{T}
    length::UInt32
end

VertexVector{T,S}(::UndefInitializer, length::Int) where {T,S} =
    VertexVector{T,S}(C_NULL, length)

function Base.setindex!(vec::VertexVector, f, i::Int)
    unsafe_store!(vec.base, f, i)
end

function Base.getindex(vec::VertexVector, i::Int)
    return unsafe_load(vec.base, i)
end

Base.size(t::VertexVector) = (t.length,)
function Base.size(t::VertexVector, d::Int)
    if d <= 0
        error("Dimension $(d) out of range")
    elseif d == 1
        return t.length
    else
        return 1
    end
end

function Base.copyto!(dest::VertexVector, src::VertexVector)
    for i in 1:src.length
        dest[i] = src[i]
    end
end

# TODO: significantly decreases codesize if set to false but might be actually needed sometimes
@inline function Base.mightalias(A::VertexVector, B::VertexVector)
    return false
end

# In Julia v1.9 the default algorithm for sorting arrays requires a scratch area, but we
# can't use it on an IPU because it'd need to allocate an extra array, so let's default to
# the simple fully in-place `QuickSort`.
if VERSION ≥ v"1.9.0-"
    Base.Sort.defalg(::VertexVector) = QuickSort
end

# Simple methods, don't access the elements
Base.show(io::IO, x::VertexVector) = Base.show_default(io, x)
Base.show(io::IO, ::MIME"text/plain", x::VertexVector) = Base.show_default(io, x)
