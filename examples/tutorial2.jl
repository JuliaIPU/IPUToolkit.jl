using IPUToolkit.Poplar

# device = Poplar.get_ipu_model()
device = Poplar.get_ipu_device()

target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)

Poplar.PopopsAddCodelets(graph)

v1 = Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[2, 2], "v1")
v2 = similar(graph, v1, "v2")

for i in 0:1
    for j in 0:1
        Poplar.GraphSetTileMapping(graph, v1[i][j], i*2 + j)
        Poplar.GraphSetTileMapping(graph, v2[i][j], j*2 + i)
    end
end

prog = Poplar.ProgramSequence()

c1 = Poplar.GraphAddConstant(graph, Float32[1.0, 1.5, 2.0, 2.5])
c2 = Poplar.GraphAddConstant(graph, Float32[4.0, 3.0, 2.0, 1.0])
Poplar.GraphSetTileMapping(graph, c1, 0)
Poplar.GraphSetTileMapping(graph, c2, 0)

Poplar.ProgramSequenceAdd(prog, Poplar.ProgramCopy(c1, Poplar.TensorFlatten(v1)))
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramCopy(c2, Poplar.TensorFlatten(v2)))

flags = Poplar.OptionFlags()

v3 = Poplar.PopopsAdd(graph, v1, v2, prog, "Add", flags)
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramPrintTensor("v3", v3))

v4 = Poplar.PopopsAdd(graph, v3, v2, prog, "Add", flags)
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramPrintTensor("v4", v4))

v5 = Poplar.PopopsAdd(graph, v1, Poplar.TensorTranspose(v2), prog, "Add", flags)
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramPrintTensor("v5", v5))


engine = Poplar.Engine(graph, prog, flags)
Poplar.EngineLoadAndRun(engine, device)

Poplar.detach_devices()
