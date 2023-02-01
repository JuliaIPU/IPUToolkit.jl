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
    # TODO: keeping `wrapmodule` inside `__init__` is a hack, it should be moved back to
    # top-level once we solve <https://github.com/giordano/julia-ipu/issues/1>.
    @initcxx()
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
