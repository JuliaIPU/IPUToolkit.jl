module IPUCompilerTest

using Test
using IPUToolkit.IPUCompiler
using IPUToolkit.Poplar

include("common.jl")

function test_compiler_program(device)
    # Define a local function to make sure macro hygiene is right
    double(x) = x * 2
    timestwo_gp = IPUCompiler.@codelet function TimesTwo(inconst::IPUCompiler.PoplarVec{Float32, IPUCompiler.In}, outvec::IPUCompiler.PoplarVec{Float32, IPUCompiler.Out})
        outvec .= double.(inconst)
    end

    sort_gp = IPUCompiler.@codelet function Sort(invec::IPUCompiler.PoplarVec{Float32, IPUCompiler.In}, outvec::IPUCompiler.PoplarVec{Float32, IPUCompiler.Out})
        outvec .= invec
        sort!(outvec)
    end

    sin_gp = IPUCompiler.@codelet function Sin(invec::IPUCompiler.PoplarVec{Float32, IPUCompiler.In}, outvec::IPUCompiler.PoplarVec{Float32, IPUCompiler.Out})
        for idx in eachindex(outvec)
            @inbounds outvec[idx] = sin(invec[idx])
        end
    end

    target = @cxxtest Poplar.DeviceGetTarget(device)
    graph = @cxxtest Poplar.Graph(target)

    Poplar.GraphAddCodelets(graph, timestwo_gp)
    Poplar.GraphAddCodelets(graph, sort_gp)
    Poplar.GraphAddCodelets(graph, sin_gp)

    input = Float32[5, 2, 10, 102, -10, 2, 256, 15, 32, 100]

    inconst = @cxxtest Poplar.GraphAddConstant(graph, Poplar.FLOAT(), UInt64[10], input)
    outvec1 = @cxxtest Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[10], "outvec1");
    outvec2 = @cxxtest Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[10], "outvec2");
    outvec3 = @cxxtest Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[10], "outvec3");

    Poplar.GraphSetTileMapping(graph, inconst, 0)
    Poplar.GraphSetTileMapping(graph, outvec1, 0)
    Poplar.GraphSetTileMapping(graph, outvec2, 0)
    Poplar.GraphSetTileMapping(graph, outvec3, 0)

    prog = @cxxtest Poplar.ProgramSequence()

    computeSetMul = @cxxtest Poplar.GraphAddComputeSet(graph, "computeSetMul")
    TimesTwoVtx = @cxxtest Poplar.GraphAddVertex(graph, computeSetMul, "TimesTwo")
    Poplar.GraphConnect(graph, TimesTwoVtx["inconst"], inconst)
    Poplar.GraphConnect(graph, TimesTwoVtx["outvec"], outvec1)
    Poplar.GraphSetTileMapping(graph, TimesTwoVtx, 0)
    if Poplar.SDK_VERSION < v"2.0"
        Poplar.GraphSetCycleEstimate(graph, TimesTwoVtx, 1)
    else
        # Poplar.GraphSetPerfEstimate(graph, TimesTwoVtx, 1)
    end

    computeSetSort = @cxxtest Poplar.GraphAddComputeSet(graph, "computeSetSort")
    SortVtx = @cxxtest Poplar.GraphAddVertex(graph, computeSetSort, "Sort")
    Poplar.GraphConnect(graph, SortVtx["invec"], outvec1)
    Poplar.GraphConnect(graph, SortVtx["outvec"], outvec2)
    Poplar.GraphSetTileMapping(graph, SortVtx, 0)
    if Poplar.SDK_VERSION < v"2.0"
        Poplar.GraphSetCycleEstimate(graph, SortVtx, 1)
    else
        # Poplar.GraphSetPerfEstimate(graph, SortVtx, 1)
    end

    computeSetSin = @cxxtest Poplar.GraphAddComputeSet(graph, "computeSetSin")
    SinVtx = @cxxtest Poplar.GraphAddVertex(graph, computeSetSin, "Sin")
    Poplar.GraphConnect(graph, SinVtx["invec"], outvec2)
    Poplar.GraphConnect(graph, SinVtx["outvec"], outvec3)
    Poplar.GraphSetTileMapping(graph, SinVtx, 0)
    if Poplar.SDK_VERSION < v"2.0"
        Poplar.GraphSetCycleEstimate(graph, SinVtx, 1)
    else
        # Poplar.GraphSetPerfEstimate(graph, SinVtx, 1)
    end

    Poplar.ProgramSequenceAdd(prog, Poplar.ProgramExecute(computeSetMul))
    Poplar.ProgramSequenceAdd(prog, Poplar.ProgramExecute(computeSetSort))
    # The `@device_override` business works well only on Julia v1.7+
    if VERSION ≥ v"1.7"
        Poplar.ProgramSequenceAdd(prog, Poplar.ProgramExecute(computeSetSin))
    end

    # Init some variables which will be used to read back from the IPU
    # the results of some basic operations.
    output_timestwo = similar(input)
    Poplar.GraphCreateHostRead(graph, "timestwo-read", outvec1)
    output_sort = similar(input)
    Poplar.GraphCreateHostRead(graph, "sort-read", outvec2)
    if VERSION ≥ v"1.7"
        output_sin = similar(input)
        Poplar.GraphCreateHostRead(graph, "sin-read", outvec3)
    end

    flags = @cxxtest Poplar.OptionFlags()
    Poplar.OptionFlagsSet(flags, "debug.instrument", "true")

    engine = @cxxtest Poplar.Engine(graph, prog, flags)
    Poplar.EngineLoadAndRun(engine, device)

    # Read back some tensors and check the expected values.
    Poplar.EngineReadTensor(engine, "timestwo-read", output_timestwo)
    @test output_timestwo == 2 .* input
    Poplar.EngineReadTensor(engine, "sort-read", output_sort)
    @test output_sort == sort(output_timestwo)
    if VERSION ≥ v"1.7"
        Poplar.EngineReadTensor(engine, "sin-read", output_sin)
        @test output_sin == sin.(output_sort)
    end

    Poplar.DeviceDetach(device)
end

@testset "IPUCompiler" begin
    if Poplar.SDK_VERSION ≥ v"2.2.0" || Base.JLOptions().check_bounds != 1 # --check-bounds != yes
        # Get a device
        device = @cxxtest @test_logs((:info, r"^Trying to attach to device"),
                                     (:info, r"^Successfully attached to device"),
                                     (:info, r"^Attached to devices with IDs"),
                                     match_mode=:any,
                                     Poplar.get_ipu_device())
        # Run a test program
        test_compiler_program(device)
    else
        # With --check-bounds=yes GPUCompiler generates a function mentioning an undefined
        # symbol `gpu_malloc`.  Mark the test as broken until we sort this out.  However
        # this function is optimised away when compiling with `-O1` or higher, and for
        # Poplar.SDK_VERSION ≥ v"2.2.0" we use `-O3`.
        @warn """
              Skipping IPUCompiler tests because bound checks are forced.  To run this testset use
                  using Pkg
                  Pkg.test("IPUToolkit"; julia_args=`--check-bounds=auto`)
              """
        @test_broken false
    end
end

end # module IPUCompilerTest
