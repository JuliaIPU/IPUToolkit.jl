module Poplar
using CxxWrap
using Scratch

const libpoplar_dir = joinpath(@get_scratch!("libpoplar"), "v$(Base.thispatch(VERSION))")
const libpoplar = joinpath(libpoplar_dir, "libpoplar_julia.so")

@wrapmodule(libpoplar)

function __init__()
    if !isfile(libpoplar)
        error("""
              `$(basename(libpoplar))` expected to exist at path `$(libpoplar)`, but could not be found.
              Run `using Pkg; Pkg.build()` to trigger recompilation of `$(basename(libpoplar))`.
              """)
    end
    @initcxx()
end

# More user-friendly methods.  NOTE: from Poplar SDK v2.3.0 (I think?) `EngineReadTensor`
# takes two arguments, like the other function below.  TODO: have a way to check the version
# of the SDK, serialising or accessing `poplar::versionString()` is complicated.
for fun in (:EngineReadTensor,) # Methods which take 1 pointer as last argument
    @eval begin
        $(fun)(arg1, arg2, ptr::Ptr{<:Number}) = $(fun)(arg1, arg2, Ptr{Cvoid}(ptr))
        $(fun)(arg1, arg2, array::AbstractArray{<:Number}) = $(fun)(arg1, arg2, Ptr{Cvoid}(pointer(array)))
    end
end
for fun in (:EngineWriteTensor, :EngineConnectStream) # Methods which take 2 pointers as last arguments
    @eval begin
        $(fun)(arg1, arg2, ptr1::Ptr{<:Number}, ptr2::Ptr{<:Number}) = $(fun)(arg1, arg2, Ptr{Cvoid}(ptr1), Ptr{Cvoid}(ptr2))
        $(fun)(arg1, arg2, array::AbstractArray{<:Number}) =
            # NOTE: we need to get the pointer to the _end_ of the array, hence `lastindex+1`.
            $(fun)(arg1, arg2, Ptr{Cvoid}(pointer(array, firstindex(array))), Ptr{Cvoid}(pointer(array, lastindex(array)+1)))
    end
end

# Be sure to quit all julia sessions which hold devices!!!
"""
    get_ipu_devices(n::Int, hint::Union{AbstractVector{<:Integer},Integer}=0)

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
"""
function get_ipu_devices(n::Int, hint::Union{AbstractVector{<:Integer},Integer}=0)
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
    if length(attached_devices) < n
        @warn "Requested $(n) devices, but could attach only to $(length(attached_devices))"
    end
    @info "Attached to devices with IDs $(Int.(Poplar.DeviceGetId.(attached_devices)))"
    return attached_devices
end

"""
    get_ipu_device(hint::Union{AbstractVector{<:Integer},Integer}=0)

Similar to [`get_ipu_devices`](@ref), but request exactly one IPU device.  If it can attach
to a device, return that pointer only (not in a vector, like `get_ipu_devices`), otherwise
return `nothing`.  You can release the device with `Poplar.DeviceDetach`.

The optional argument `hint` suggests to which device IDs to try and
attach.  It can have different types:

* if of type `Integer`, try to attach to `n` devices, starting from the one
  with index `hint`.  The default is `hint=0`;
* if of type `AbstractVector`, try to attach to `n` devices from that list of
  IDs.
"""
function get_ipu_device(hint::Union{AbstractVector{<:Integer},Integer}=0)
    device = get_ipu_devices(1, hint)
    if isone(length(device))
        return only(device)
    end
    return nothing
end

end # module Poplar
