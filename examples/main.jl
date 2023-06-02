using IPUToolkit.IPUCompiler
using IPUToolkit.Poplar

device = if Poplar.SDK_VERSION < v"2.0"
    Poplar.IPUModelCreateDevice(Poplar.IPUModel())
else
    Poplar.get_ipu_device()
end

target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)

tile_clock_frequency = Poplar.TargetGetTileClockFrequency(target)

IPUCompiler.@codelet graph function TimesTwo(inconst::IPUCompiler.VertexVector{Float32, IPUCompiler.In}, outvec::IPUCompiler.VertexVector{Float32, IPUCompiler.Out})
    outvec .= inconst .* 2
end

@eval IPUCompiler.@codelet graph function Sort(invec::IPUCompiler.VertexVector{Float32, IPUCompiler.In}, outvec::IPUCompiler.VertexVector{Float32, IPUCompiler.Out})
    outvec .= invec
    # We can use the intrinsic `get_scount_l` to get the cycle counter right
    # before and after some operations, so that we can benchmark it.
    cycles_start = get_scount_l()
    sort!(outvec)
    cycles_end = get_scount_l()
    # Divide the difference between the two cycle counts by the tile frequency
    # clock to get the time.
    sort_time = (cycles_end - cycles_start) / $(tile_clock_frequency)
    @ipushow sort_time
end

inconst = Poplar.GraphAddConstant(graph, Poplar.FLOAT(), UInt64[10], Float32[5, 2, 10, 102, -10, 2, 256, 15, 32, 100])
outvec1 = Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[10], "outvec1");
outvec2 = Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[10], "outvec2");

Poplar.GraphSetTileMapping(graph, inconst, 0)
Poplar.GraphSetTileMapping(graph, outvec1, 0)
Poplar.GraphSetTileMapping(graph, outvec2, 0)

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
Poplar.DeviceDetach(device)
