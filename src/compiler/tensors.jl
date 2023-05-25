# `PoplarArray` is a placeholder type to represent variables to be added to a
#  graph.  NOTE: these are distincts from `VertexVector`s which represent the
#  input/output arguments of codelets (vertices).

export PoplarArray, PoplarVector, PoplarMatrix

struct PoplarArray{T,N} <: AbstractArray{T,N}
    size::NTuple{N,Int}
end
const PoplarVector{T} = PoplarArray{T,1}
const PoplarMatrix{T} = PoplarArray{T,2}
PoplarArray{T,N}(::UndefInitializer, size::Vararg{Int,N}) where {T,N} =
    PoplarArray{T,N}(size)

Base.size(t::PoplarArray) = t.size
Base.size(t::PoplarArray, d::Int) = size(t)[d]

# Simple methods, don't access the elements
Base.show(io::IO, x::PoplarArray) = Base.show_default(io, x)
Base.show(io::IO, ::MIME"text/plain", x::PoplarArray) = Base.show_default(io, x)

_similar(t::PoplarArray{T,N}) where {T,N} = Array{T,N}(undef, size(t))
