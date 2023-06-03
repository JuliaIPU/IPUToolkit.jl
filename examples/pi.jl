using IPUToolkit.IPUCompiler, IPUToolkit.Poplar
using Enzyme

ENV["POPLAR_RUNTIME_OPTIONS"] = """{"target.hostSyncTimeout":"60"}"""

IPUCompiler.KEEP_LLVM_FILES[] = true

device = Poplar.get_ipu_device()
target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)

num_tiles = Int(Poplar.TargetGetNumTiles(target))
n = 2_000_000
num_steps = num_tiles * n
slice::Float32 = 1 / num_steps

tile_clock_frequency = Poplar.TargetGetTileClockFrequency(target)

ids = collect(Int32.(0:(num_tiles - 1)))
sums = Vector{Float32}(undef, num_tiles)
cycles = Vector{UInt32}(undef, num_tiles)

# Why are we using `@eval`?  Because inside a codelet we cannot access non-constant globals,
# so we can either make them constant, or interpolate them via `@eval` and let people play
# with the values without having to restart the session.  I think the latter is more
# user-friendly :)  And a top-level `@eval` is not _too_ bad.
@eval function pi_kernel(i)
    sum = 0f0
    for j in (Int32(1) + i * $(n)):min($(num_steps), (i + 1) * $(n))
        x = (j - 5f-1) * $(slice)
        sum += Float32(Int32(4) / (Int32(1) + x ^ 2))
    end
    return sum
end

IPUCompiler.@codelet graph function Pi(in::VertexVector{Int32, In},
                                       out::VertexVector{Float32, Out},
                                       cycles::VertexVector{UInt32, Out})
    # Each tile deals with one-element vectors only.  In `out` we store the result of the
    # kernel, in `cycles` we store the cycles count on this tile.
    cycles[begin] = @ipuelapsed(out[begin] = pi_kernel(in[begin]))
end

input = Poplar.GraphAddConstant(graph, ids)
output = similar(graph, input, Float32, "sums");
cs = similar(graph, input, UInt32, "cycles");

prog = Poplar.ProgramSequence()

add_vertex(graph, prog, 0:(num_tiles - 1), Pi, input, output, cs)

Poplar.GraphCreateHostRead(graph, "sums-read", output)
Poplar.GraphCreateHostRead(graph, "cycles-read", cs)

flags = Poplar.OptionFlags()
Poplar.OptionFlagsSet(flags, "debug.instrument", "true")

engine = Poplar.Engine(graph, prog, flags)
Poplar.EngineLoadAndRun(engine, device)
Poplar.EngineReadTensor(engine, "sums-read", sums)
Poplar.EngineReadTensor(engine, "cycles-read", cycles)

Poplar.DeviceDetach(device)

pi = sum(sums) * slice

print("""
      Calculating PI using:
        $(num_steps) slices
        $(num_tiles) IPU tiles
      Obtained value of PI: $(pi)
      Time taken: $(maximum(cycles) / tile_clock_frequency) seconds
      """)
