using IPUToolkit.IPUCompiler, IPUToolkit.Poplar

ENV["POPLAR_RUNTIME_OPTIONS"] = """{"target.hostSyncTimeout":"60"}"""

IPUCompiler.KEEP_LLVM_FILES[] = true

device = Poplar.get_ipu_device()
target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)

num_tiles = Int(Poplar.TargetGetNumTiles(target))
n::UInt32 = typemax(UInt32) ÷ num_tiles
num_steps::UInt32 = num_tiles * n
slice::Float32 = 1 / num_steps

tile_clock_frequency = Poplar.TargetGetTileClockFrequency(target)

ids = collect(UInt32.(0:(num_tiles - 1)))
sums = similar(ids, Float32)
cycles = similar(ids)

# Why are we using `@eval`?  Because inside a codelet we cannot access non-constant globals,
# so we can either make them constant, or interpolate them via `@eval` and let people play
# with the values without having to restart the session.  I think the latter is more
# user-friendly :)  And a top-level `@eval` is not _too_ bad.
@eval function pi_kernel(i::T) where {T<:Integer}
    sum = 0f0
    for j in (i * $(n)):((i + one(T)) * $(n) - one(T))
        x = (j - 5f-1) * $(slice)
        sum += 4 / (1 + x ^ 2)
    end
    return sum
end

@codelet graph function Pi(in::VertexVector{UInt32, In},
                           out::VertexVector{Float32, Out},
                           cycles::VertexVector{UInt32, Out})
    # Each tile deals with one-element vectors only.  In `out` we store the result of the
    # kernel, in `cycles` we store the cycles count on this tile.
    cycles[begin] = @ipuelapsed(out[begin] = pi_kernel(in[begin]))
end

ids_ipu = Poplar.GraphAddConstant(graph, ids)
sums_ipu = similar(graph, sums, "sums");
cycles_ipu = similar(graph, cycles, "cycles");

prog = Poplar.ProgramSequence()

add_vertex(graph, prog, 0:(num_tiles - 1), Pi, ids_ipu, sums_ipu, cycles_ipu)

Poplar.GraphCreateHostRead(graph, "sums-read", sums_ipu)
Poplar.GraphCreateHostRead(graph, "cycles-read", cycles_ipu)

flags = Poplar.OptionFlags()
Poplar.OptionFlagsSet(flags, "debug.instrument", "true")

engine = Poplar.Engine(graph, prog, flags)
Poplar.EngineLoadAndRun(engine, device)
Poplar.EngineReadTensor(engine, "sums-read", sums)
Poplar.EngineReadTensor(engine, "cycles-read", cycles)

Poplar.detach_devices()

pi = sum(sums) * slice
time = round(maximum(cycles) / tile_clock_frequency; sigdigits=4)

print("""
      Calculating PI using:
        $(num_steps) slices
        $(num_tiles) IPU tiles
      Obtained value of PI: $(pi)
      Time taken: $(time) seconds ($(maximum(cycles)) cycles at $(round(tile_clock_frequency / 1e9; sigdigits=3)) GHz)
      """)
