# Timing inside a codelet is complicated, because in a codelet you can use
# `__builtin_ipu_get_scount_l` to get the current cycle count, but the clock speed is only
# available from the `target` object (`target.getTileClockFrequency()`).  What you can do is
# to get the counters before and after the region you want to benchmark and then divide by
# the clock frequency, interpolated in the codelet code with `@eval`:
#
#     device = Poplar.get_ipu_device()
#     target = Poplar.DeviceGetTarget(device)
#     graph = Poplar.Graph(target)
#     tile_clock_frequency = Poplar.TargetGetTileClockFrequency(target)
#     @eval IPUCompiler.@codelet graph function Foo(...)
#         cycles_start = get_scount_l()
#         # Do something here...
#         cycles_end = get_scount_l()
#         time = (cycles_end - cycles_start) / $(tile_clock_frequency)
#         @ipushow time
#     end
#
# Here we only provide some macros for easily getting the cycle counts, not the times
# directly.  For reference, typical clock counts are either 1.330 GHz on a classic machine
# or 1.850 GHz on a Bow machine.
#
# *NOTE*: cycle counters are `UInt32`, so timing expressions longer than `typemax(UInt32) /
# tile_clock_frequency` (~2 or 3 seconds depending on the model) is unreliable.

export @ipucycles, @ipushowcycles, @ipuelapsed

macro ipucycles(msg, ex)
    # `@ipuprintln` is already disabled by `DISABLE_PRINT`, but we want to remove also the
    # `get_scount_l` instructions since we aren't going to print anything anyway.
    if DISABLE_PRINT[]
        return :()
    end

    return quote
        !isnothing($(esc(msg))) && $(@__MODULE__).@ipuprint $(msg) ":"
        local cycles_start = get_scount_l()
        local value = $(esc(ex))
        local cycles_end = get_scount_l()
        local Δ = cycles_end - cycles_start
        $(@__MODULE__).@ipuprintln Δ " cycles"
        value
    end
end

macro ipucycles(ex)
    return quote
        $(@__MODULE__).@ipucycles nothing $(esc(ex))
    end
end

"""
    @ipucycles ex
    @ipucycles "description" ex

Print from inside a codelet the number of cycles spent to compute the expression `ex`.
The corresponding time can be obtained by dividing the number of cycles by the clock frequency of the the tile, which you can get with `Poplar.TargetGetTileClockFrequency(target)` outside of the codelet.
The optional argument `description`, a literal `String`, can be used to print also a label to identify the timed expression.
A label is added automatically by [`@ipushowcycles`](@ref).

See also [`@ipuelapsed`](@ref).

This macro can be made no-op completely by setting
```julia
$(@__MODULE__).DISABLE_PRINT[] = true
```
"""
var"@ipucycles"

"""
    @ipushowcycles ex

Print from inside a codelet the expression `ex` and the number of cycles spent to compute it.
This is useful when benchmarking multiple expression, to identify their contributions more easily.
The corresponding time can be obtained by dividing the number of cycles by the clock frequency of the the tile, which you can get with `Poplar.TargetGetTileClockFrequency(target)` outside of the codelet.

See also [`@ipucycles`](@ref), [`@ipuelapsed`](@ref).

This macro can be made no-op completely by setting
```julia
$(@__MODULE__).DISABLE_PRINT[] = true
```
"""
macro ipushowcycles(ex)
    return quote
        $(@__MODULE__).@ipucycles $(sprint(Base.show_unquoted, ex)) $(esc(ex))
    end
end

"""
    @ipuelapsed ex

Return number of cycles spent to compute the expression `ex`.
The corresponding time can be obtained by dividing the number of cycles by the clock frequency of the the tile, which you can get with `Poplar.TargetGetTileClockFrequency(target)` outside of the codelet.

See also [`@ipucycles`](@ref), [`@ipushowcycles`](@ref).
"""
macro ipuelapsed(ex)
    return quote
        local cycles_start = get_scount_l()
        $(esc(ex))
        local cycles_end = get_scount_l()
        cycles_end - cycles_start
    end
end
