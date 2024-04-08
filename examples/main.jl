using IPUToolkit.IPUCompiler
using IPUToolkit.Poplar

device = Poplar.get_ipu_device()

target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)

tile_clock_frequency = Poplar.TargetGetTileClockFrequency(target)

# Multiply input vector `in` by 2, and store result in vector `out`.
@codelet graph function TimesTwo(in::VertexVector{Float16, In}, out::VertexVector{Float16, Out})
    out .= in .* 2
end

# Copy elements of `in` into `out` and sort it in-place.  Get cycles counter before and
# after sorting, show the time to sort the vector by divinding the cycles count by the tile
# clock frequency, which has been interpolated inside the kernel with `@eval` (the
# alternative would be to pass it as an extra scalar input argument).
@eval @codelet graph function Sort(in::VertexVector{Float16, In}, out::VertexVector{Float16, Out})
    copyto!(out, in)
    # We can use the intrinsic `get_scount_l` to get the cycle counter right
    # before and after some operations, so that we can benchmark it.
    cycles_start = get_scount_l()
    sort!(out)
    cycles_end = get_scount_l()
    # Divide the difference between the two cycle counts by the tile frequency
    # clock to get the time.
    sort_time = (cycles_end - cycles_start) / $(tile_clock_frequency)
    @ipushow sort_time
end

inconst = Poplar.GraphAddConstant(graph, Float16[5, 2, 10, 102, -10, 2, 256, 15, 32, 100])
outvec1 = similar(graph, inconst, "outvec1");
outvec2 = similar(graph, inconst, "outvec2");

prog = Poplar.ProgramSequence()

add_vertex(graph, prog, TimesTwo, inconst, outvec1)
add_vertex(graph, prog, Sort, outvec1, outvec2)

Poplar.ProgramSequenceAdd(prog, Poplar.ProgramPrintTensor("Input", inconst))
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramPrintTensor("Output Times2", outvec1))
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramPrintTensor("Output Sorted", outvec2))

flags = Poplar.OptionFlags()
Poplar.OptionFlagsSet(flags, "debug.instrument", "true")

engine = Poplar.Engine(graph, prog, flags)
Poplar.EngineLoadAndRun(engine, device)
Poplar.detach_devices()
