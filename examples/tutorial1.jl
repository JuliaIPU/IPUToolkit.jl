using Poplar

model = Poplar.IPUModel()
device = Poplar.IPUModelCreateDevice(model)
# device = Poplar.getIPU()

target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)

v1 = Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[4], "v1")
v2 = Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[4], "v2")
v3 = Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[4, 4], "v3")
v4 = Poplar.GraphAddVariable(graph, Poplar.INT(), UInt64[10], "v4")

Poplar.GraphSetTileMapping(graph, v1, 0)

for i in UInt64(0):UInt64(3)
    Poplar.GraphSetTileMapping(graph, v2[i], i)
end

Poplar.GraphSetTileMapping(graph, v3, 0)
Poplar.GraphSetTileMapping(graph, v4, 0)

prog = Poplar.ProgramSequence()

c1 = Poplar.GraphAddConstant(graph, Poplar.FLOAT(), UInt64[4], Float32[1.0, 1.5, 2.0, 2.5])
Poplar.GraphSetTileMapping(graph, c1, 0)

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

h3 = Array{Float32}(zeros(4*4))
h3 .= zero(h3)

Poplar.EngineWriteTensor(engine, "v3-write", Poplar.startPtr(h3))

inData = Array{Int32}(zeros(30))
for i in 1:30
    inData[i] = (i-1)
end

Poplar.EngineConnectStream(engine, "v4-input-stream", Poplar.startPtr(inData), Poplar.endPtr(inData))

Poplar.EngineRun(engine, 0)

Poplar.EngineReadTensor(engine, "v3-read", Poplar.startPtr(h3))

println("h3 data:")
for i in 0:3
    print(" ")
    for j in 0:3
        print(h3[i*4 + j+1], " ")
    end
    println("")
end
