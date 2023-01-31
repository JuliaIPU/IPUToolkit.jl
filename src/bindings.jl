module Poplar
using CxxWrap
using Scratch

@wrapmodule(joinpath(@get_scratch!("libpoc"), "libpoc.so"))

function __init__()
    @initcxx
end

function startPtr(data::AbstractArray, i=1)
    Base.unsafe_convert(Ptr{Nothing}, pointer(data, i))
end

function endPtr(data::AbstractArray, i=length(data))
    Base.unsafe_convert(Ptr{Nothing}, pointer(data, i+1))
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

end
