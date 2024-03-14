module Poplar
using CxxWrap
using Scratch

const libpoplar_dir = joinpath(@get_scratch!("libpoplar"), "v$(Base.thispatch(VERSION))")
get_libpoplar_path() = joinpath(libpoplar_dir, "libpoplar_julia.so")

export @graph

function _graph(g, expr::Expr)
    out = copy(expr)
    insert!(out.args, 2, g)
    return out
end

"""
    @graph [graph] expr

This is a convenient macro to automatically inject `graph` as first argument of all function calls in the expression passed as last argument to the macro.

The `graph` argument should be the graph object you want to pass as first argument to the function calls.
If it is a local variable called exactly `graph`, this argument can be omitted and this name will be used automatically.

!!! note

    This macro is not very sophisticated and will fail with complex expressions involving, for example, control flows like `if` or `for`.
    See the examples below.

## Examples

```julia
julia> @macroexpand @graph begin
           c1 = Poplar.GraphAddConstant(Float32[1.0, 1.5, 2.0, 2.5])
           v1 = similar(c1, "v1")

           Poplar.GraphSetTileMapping(c1, 0)
           Poplar.GraphSetTileMapping(v1, 0)
       end
quote
    c1 = Poplar.GraphAddConstant(graph, Float32[1.0, 1.5, 2.0, 2.5])
    v1 = similar(graph, c1, "v1")
    Poplar.GraphSetTileMapping(graph, c1, 0)
    Poplar.GraphSetTileMapping(graph, v1, 0)
end
```
"""
macro graph(g, x::Expr)
    x.head === :block || error("The last argument to the `@graph` macro must be a begin-end block")
    out = Expr(:block)
    for expr in x.args
        if expr isa LineNumberNode
            continue
        elseif expr.head === :call
            push!(out.args, _graph(g, expr))
        elseif expr.head === :(=) && expr.args[2].head === :call
            tmp = copy(expr)
            tmp.args[2] = _graph(g, expr.args[2])
            push!(out.args, tmp)
        end
    end
    return esc(out)
end

macro graph(x::Expr)
    esc( :( $(@__MODULE__).@graph graph $(x) ) )
end

# Note: this is really only needed for Poplar SDK ≥ v2.0.0, but at this point we don't know
# the version number yet.  It doesn't really hurt defining this struct unconditionally.
struct VertexPerfEstimate
    cycles::UInt64
    flops::UInt64
    VertexPerfEstimate(cycles::Integer=0, flops::Integer=0) =
        new(UInt64(cycles), UInt64(flops))
end

@wrapmodule(get_libpoplar_path)

const SDK_VERSION = VersionNumber(match(r"[\d.]+", String(Poplar.getVersionString())).match)

function __init__()
    libpoplar = get_libpoplar_path()
    if !isfile(libpoplar)
        error("""
              `$(basename(libpoplar))` expected to exist at path `$(libpoplar)`, but could not be found.
              Run `using Pkg; Pkg.build()` to trigger recompilation of `$(basename(libpoplar))`.
              """)
    end
    @initcxx()
end

# More user-friendly methods.
let
    # Methods which take 1 pointer as last argument.  NOTE: `readTensor` changed API in
    # v2.1.0, from taking one pointer to two, like `writeTensor`.
    one_ptr = SDK_VERSION < v"2.1.0" ? (:EngineReadTensor,) : ()
    # Methods which take 2 pointers as last arguments
    two_ptr = SDK_VERSION < v"2.1.0" ? (:EngineWriteTensor, :EngineConnectStream,)  : (:EngineWriteTensor, :EngineConnectStream, :EngineReadTensor)
    for fun in one_ptr
        @eval begin
            $(fun)(arg1, arg2, ptr::Ptr{<:Number}) = $(fun)(arg1, arg2, Ptr{Cvoid}(ptr))
            $(fun)(arg1, arg2, array::AbstractArray{<:Number}) = $(fun)(arg1, arg2, Ptr{Cvoid}(pointer(array)))
        end
    end
    for fun in two_ptr
        @eval begin
            $(fun)(arg1, arg2, ptr1::Ptr{<:Number}, ptr2::Ptr{<:Number}) = $(fun)(arg1, arg2, Ptr{Cvoid}(ptr1), Ptr{Cvoid}(ptr2))
            $(fun)(arg1, arg2, array::AbstractArray{<:Number}) =
                # NOTE: we need to get the pointer to the _end_ of the array, hence `lastindex+1`.
                $(fun)(arg1, arg2, Ptr{Cvoid}(pointer(array, firstindex(array))), Ptr{Cvoid}(pointer(array, lastindex(array)+1)))
        end
    end
end

_get_type(::Type{Bool}) = BOOL()
_get_type(::Type{Cchar}) = CHAR()
_get_type(::Type{Cuchar}) = UNSIGNED_CHAR()
# _get_type(::Type{Cchar}) = SIGNED_CHAR()
_get_type(::Type{Cushort}) = UNSIGNED_SHORT()
_get_type(::Type{Cshort}) = SHORT()
_get_type(::Type{Cuint}) = UNSIGNED_INT()
_get_type(::Type{Cint}) = INT()
_get_type(::Type{Culong}) = UNSIGNED_LONG()
_get_type(::Type{Clong}) = LONG()
# _get_type(::Type{Culonglong}) = UNSIGNED_LONGLONG()
# _get_type(::Type{Clonglong}) = LONGLONG()
_get_type(::Type{Float16}) = HALF()
_get_type(::Type{Cfloat}) = FLOAT()
_get_type(t::Symbol) = _get_type(getfield(@__MODULE__, t))
_get_type(t::TensorAllocated) = Poplar.TensorElementType(t)
_get_type(t::Array) = _get_type(eltype(t))

_size(t::Union{TensorAllocated,Array}) = collect(UInt64.(size(t)))

GraphAddConstant(graph::Graph, tensor::Array{T}) where {T} =
    Poplar.GraphAddConstant(graph, _get_type(T), collect(UInt64.(size(tensor))), tensor)
# For `Float16` we need to use the function `graph.addConstantHalf` which takes
# a vector of `uint16_t` in input.
GraphAddConstant(graph::Poplar.Graph, tensor::Array{Float16}) =
    GraphAddConstantHalf(graph, Poplar._get_type(Float16), collect(UInt64.(size(tensor))), collect(reinterpret(UInt16, tensor)))
Base.getindex(t::TensorAllocated, r::AbstractUnitRange{<:Integer}) =
    TensorSlice(t, first(r), last(r) + step(r))
Base.size(t::TensorAllocated) = Int.((Poplar.TensorShape(t)...,))
Base.length(t::TensorAllocated) = prod(size(t))
Base.eachindex(t::TensorAllocated) = 0:(length(t) - 1)
function Base.eachindex(t1::TensorAllocated, t2::TensorAllocated)
    t1_len = length(t1)
    t2_len = length(t2)
    if t1_len != t2_len
        throw(DimensionMismatch("all input tensors to eachindex must have the same lengths, got $(t1) and $(t2)"))
    end
    return 0:(t1_len - 1)
end
"""
    similar(
        graph::Poplar.Graph,
        tensor::Union{Poplar.TensorAllocated,Array},
        [type::DataType],
        [debug::String]
    ) -> Poplar.TensorAllocated

Adds to `graph` a variable tensor with the same shape as `tensor`, which can be either an IPU tensor or a plain Julia `Array`.
If a `type` (this is a Julia type, like `Float32` or `Int32`) argument is not passed, the same element type as `tensor` will be automatically used.
An optional `debug` context can also be passed, as a `String`.
"""
Base.similar(graph::Graph, t::Union{TensorAllocated,Array}) =
    Poplar.GraphAddVariable(graph, _get_type(t), _size(t))
Base.similar(graph::Graph, t::Union{TensorAllocated,Array}, debug::String) =
    Poplar.GraphAddVariable(graph, _get_type(t), _size(t), debug)
Base.similar(graph::Graph, t::Union{TensorAllocated,Array}, type::DataType) =
    Poplar.GraphAddVariable(graph, _get_type(type), _size(t))
Base.similar(graph::Graph, t::Union{TensorAllocated,Array}, type::DataType, debug::String) =
    Poplar.GraphAddVariable(graph, _get_type(type), _size(t), debug)

const ATTACHED_DEVICES = Poplar.DeviceAllocated[]
const ATTACHED_DEVICES_LOCK = ReentrantLock()

# Be sure to quit all julia sessions which hold devices!!!
"""
    Poplar.get_ipu_devices(n::Int, hint::Union{AbstractVector{<:Integer},Integer}=0)

Try to attach to `n` IPU devices, returns a vector of the pointers to the devices
successfully attached to.  You can release them with `Poplar.DeviceDetach` (note that this
function takes a single pointer as input, so you have to use broadcasting
`Poplar.DeviceDetach.(devices)` to release a vector of pointers).

The second optional argument `hint` suggests to which device IDs to try and
attach.  It can have different types:

* if of type `Integer`, try to attach to `n` devices, starting from the one
  with index `hint`.  The default is `hint=0`;
* if of type `AbstractVector`, try to attach to `n` devices from that list of
  IDs.

See [`get_ipu_device`](@ref) for requesting exactly one IPU device.
To release all devices previously attached with `Poplar.get_ipu_devices` or [`Poplar.get_ipu_device`](@ref) use [`Poplar.detach_devices`](@ref).
"""
function get_ipu_devices(n::Int, hint::Union{AbstractVector{<:Integer},Integer}=0)
    lock(ATTACHED_DEVICES_LOCK) do
        device_manager = Poplar.DeviceManager()
        try_ids = if hint isa AbstractVector
            hint
        else
            max_dev_id = Int(Poplar.DeviceManagerGetNumDevices(device_manager))
            hint:(max_dev_id - 1)
        end
        attached_devices = Poplar.DeviceAllocated[]
        for id in try_ids
            if length(attached_devices) >= n
                break
            end
            device = Poplar.DeviceManagerGetDevice(device_manager, id)
            @info "Trying to attach to device $(id)..."
            res = Poplar.DeviceAttach(device)
            if res
                @info "Successfully attached to device $(id)"
                push!(attached_devices, device)
            end
        end
        actual_n = length(attached_devices)
        if actual_n < n
            @warn "Requested $(n) devices, but could attach only to $(actual_n)"
        end
        if !(actual_n == n == 1)
            # Do not print the summary of the attached devices if we requested one and got one.
            @info "Attached to devices with IDs $(Int.(Poplar.DeviceGetId.(attached_devices)))"
        end
        append!(ATTACHED_DEVICES, attached_devices)
        attached_devices
    end
end

"""
    Poplar.get_ipu_device(hint::Union{AbstractVector{<:Integer},Integer}=0)

Similar to [`Poplar.get_ipu_devices`](@ref), but request exactly one IPU device.  If it can attach
to a device, return that pointer only (not in a vector, like `get_ipu_devices`), otherwise
return `nothing`.  You can release the device with `Poplar.DeviceDetach(device)`.
To release all devices previously attached with `Poplar.get_ipu_device` or [`Poplar.get_ipu_devices`](@ref) use [`Poplar.detach_devices`](@ref).

The optional argument `hint` suggests to which device IDs to try and
attach.  It can have different types:

* if of type `Integer`, try to attach to one device, starting from the one with index `hint`.
  The default is `hint=0`;
* if of type `AbstractVector`, try to attach to a device from that list of IDs.
"""
function get_ipu_device(hint::Union{AbstractVector{<:Integer},Integer}=0)
    device = get_ipu_devices(1, hint)
    if isone(length(device))
        return only(device)
    end
    return nothing
end

"""
    Poplar.detach_devices() -> Nothing

Detach all devices previously attached in the current Julia session with [`Poplar.get_ipu_devices`](@ref) or [`Poplar.get_ipu_device`](@ref).
"""
function detach_devices()
    lock(ATTACHED_DEVICES_LOCK) do
        for device in ATTACHED_DEVICES
            Poplar.DeviceDetach(device)
        end
        empty!(ATTACHED_DEVICES)
    end
    return nothing
end

end # module Poplar
