# NOTE: `VertexVector`s are distincts from `PoplarArrays` because they represent
# the variables you can add to a graph.

# Scope of the vectors in codelets.  These singletons are used only for dispatch.
struct In end
struct Out end
struct InOut end

"""
    VertexVector{T, S} <: AbstractVector{T}

This datatype formally represents vectors to be used in codelets (vertices) in IPU programs.
They are the counterpart of the [vertex vector types](https://docs.graphcore.ai/projects/poplar-user-guide/en/3.2.0/vertex_vectors.html) in the Poplar SDK.

The parameters of `VertexVector{T,S}` are

* `T`: the type of the elements of the vector, e.g. `Int32`, `Float32`, etc.;
* `S`: the scope of the vector in the codelet, `In`, `Out`, or `InOut`.

`VertexVector` is only meant to be used by end-user to define the arguments of codelets with the [`@codelet`](@ref) macro.
You should not try to manually instantiate or access the fields of a `VertexVector`.

## Example

```
VertexVector{Float32, In}    # input-only vector of `Float32` elements
VertexVector{Int32, Out}     # output-only vector of `Int32` elements
VertexVector{UInt32, InOut}  # input/output vector of `UInt32` elements
```
"""
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
