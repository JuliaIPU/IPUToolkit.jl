include(joinpath(@__DIR__, "llvm_builder.jl"))
using Poplar
using GPUCompiler

##

@llvmBuilder.Codelet TimesTwo function (inconst::llvmBuilder.PoplarVec{Float32, llvmBuilder.In}, outvec::llvmBuilder.PoplarVec{Float32, llvmBuilder.Out})
    (outvec .= inconst .* 2)
end

@llvmBuilder.Codelet Sort function (invec::llvmBuilder.PoplarVec{Float32, llvmBuilder.In}, outvec::llvmBuilder.PoplarVec{Float32, llvmBuilder.Out})
    outvec .= invec
    sort!(outvec)
end

model = Poplar.IPUModel()
device = Poplar.IPUModelCreateDevice(model)
# device = Poplar.getIPU()

target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)

Poplar.GraphAddCodelets(graph, "TimesTwo.gp")
Poplar.GraphAddCodelets(graph, "Sort.gp")

inconst = Poplar.GraphAddConstant(graph, Poplar.FLOAT, UInt64[10], Float32[5, 2, 10, 102, -10, 2, 256, 15, 32, 100])
outvec1 = Poplar.GraphAddVariable(graph, Poplar.FLOAT, UInt64[10], "outvec1");
outvec2 = Poplar.GraphAddVariable(graph, Poplar.FLOAT, UInt64[10], "outvec2");

Poplar.GraphSetTileMapping(graph, inconst, 0)
Poplar.GraphSetTileMapping(graph, outvec1, 0)
Poplar.GraphSetTileMapping(graph, outvec2, 0)

prog = Poplar.ProgramSequence()

computeSetMul = Poplar.GraphAddComputeSet(graph, "computeSetMul")
TimesTwoVtx = Poplar.GraphAddVertex(graph, computeSetMul, "TimesTwo")
Poplar.GraphConnect(graph, TimesTwoVtx["inconst"], inconst)
Poplar.GraphConnect(graph, TimesTwoVtx["outvec"], outvec1)
Poplar.GraphSetTileMapping(graph, TimesTwoVtx, 0)
Poplar.GraphSetCycleEstimate(graph, TimesTwoVtx, 1)

computeSetSort = Poplar.GraphAddComputeSet(graph, "computeSetSort")
SortVtx = Poplar.GraphAddVertex(graph, computeSetSort, "Sort")
Poplar.GraphConnect(graph, SortVtx["invec"], outvec1)
Poplar.GraphConnect(graph, SortVtx["outvec"], outvec2)
Poplar.GraphSetTileMapping(graph, SortVtx, 0)
Poplar.GraphSetCycleEstimate(graph, SortVtx, 1)


Poplar.ProgramSequenceAdd(prog, Poplar.ProgramExecute(computeSetMul))
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramExecute(computeSetSort))
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramPrintTensor("Input", inconst))
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramPrintTensor("Output Times2", outvec1))
Poplar.ProgramSequenceAdd(prog, Poplar.ProgramPrintTensor("Output Sorted", outvec2))

flags = Poplar.OptionFlags()
Poplar.OptionFlagsSet(flags, "debug.instrument", "true")

engine = Poplar.Engine(graph, prog, flags)
Poplar.EngineLoadAndRun(engine, device)
