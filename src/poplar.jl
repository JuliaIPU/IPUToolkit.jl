module Poplar
using CxxWrap
using Scratch

const libpoc = joinpath(@get_scratch!("libpoc"), "libpoc.so")
@wrapmodule(libpoc)

function __init__()
    if !isfile(libpoc)
        error("""
              `libpoc.so` expected to exist at path `$(libpoc)`, but could not be found.
              Run `using Pkg; Pkg.build()` to trigger recompilation of `libpoc.so`.
              """)
    end
    @initcxx()
end

# More user-friendly methods
for fun in (:EngineReadTensor,) # Method which take at 1 pointer as last argument
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
ipu_devices = []
function getIPUs(n::Int)
    while n > length(ipu_devices)
        push!(ipu_devices, getRealIPU())
    end
    return Tuple(ipu_devices[1:n])
end

function getIPU()
    getIPUs(1)[1]
end

end # module Poplar
