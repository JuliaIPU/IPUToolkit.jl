using IPUToolkit.Poplar

# device = Poplar.get_ipu_model()
device = Poplar.get_ipu_device()

target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)

h3 = zeros(Float32, 4, 4)

@graph begin
    c1 = Poplar.GraphAddConstant(Float32[1.0, 1.5, 2.0, 2.5])
    v1 = similar(c1, "v1")
    v2 = similar(c1, "v2")
    v3 = similar(h3, "v3")
    v4 = Poplar.GraphAddVariable(Poplar.INT(), UInt64[10], "v4")

    Poplar.GraphSetTileMapping(v1, 0)
    Poplar.GraphSetTileMapping(v3, 0)
    Poplar.GraphSetTileMapping(v4, 0)
    Poplar.GraphSetTileMapping(c1, 0)
end

for i in UInt64(0):UInt64(3)
    Poplar.GraphSetTileMapping(graph, v2[i], i)
end

prog = Poplar.ProgramSequence()

Poplar.ProgramSequenceAdd(prog, Poplar.ProgramCopy(c1, v1))
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramPrintTensor("v1-debug", v1))

Poplar.ProgramSequenceAdd(prog, Poplar.ProgramCopy(v1, v2))
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramPrintTensor("v2-debug", v2))

Poplar.GraphCreateHostWrite(graph, "v3-write", v3)
Poplar.GraphCreateHostRead(graph, "v3-read", v3)

v1slice = Poplar.TensorSlice(v1, 0, 3)
v3slice = Poplar.TensorSlice(v3, UInt64[1, 1], UInt64[2, 4])
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramCopy(v1slice, v3slice))

inStream = Poplar.GraphAddHostToDeviceFIFO(graph, "v4-input-stream", Poplar.INT(), 10)

Poplar.ProgramSequenceAdd(prog, Poplar.ProgramCopy(inStream, v4))
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramPrintTensor("v4-0", v4))
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramCopy(inStream, v4))
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramPrintTensor("v4-1", v4))

flags = Poplar.OptionFlags()
Poplar.OptionFlagsSet(flags, "debug.instrument", "true")

engine = Poplar.Engine(graph, prog, flags)
Poplar.EngineLoad(engine, device)

Poplar.EngineWriteTensor(engine, "v3-write", h3)

inData = Int32.(0:29)

Poplar.EngineConnectStream(engine, "v4-input-stream", inData)

Poplar.EngineRun(engine, 0)

Poplar.EngineReadTensor(engine, "v3-read", h3)

print("h3 data: ")
display(h3')

Poplar.detach_devices()
