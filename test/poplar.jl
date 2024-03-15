module PoplarTest

using Test
using IPUToolkit.Poplar

include("common.jl")

function test_poplar_program(device)
    target = @cxxtest Poplar.DeviceGetTarget(device)
    graph = @cxxtest Poplar.Graph(target)
    Poplar.PopopsAddCodelets(graph)

    v1 = @cxxtest Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[2, 2], "v1")
    @test_throws ArgumentError copyto!(graph, v1, [1, 2, 3, 4])
    v2 = @cxxtest similar(graph, v1, "v2")

    for i in 0:1
        for j in 0:1
            @graph begin
                Poplar.GraphSetTileMapping(v1[i][j], i*2 + j)
                Poplar.GraphSetTileMapping(v2[i][j], j*2 + i)
            end
        end
    end

    prog = @cxxtest Poplar.ProgramSequence()

    h1 = Float32[1.0, 1.5, 2.0, 2.5]
    h2 = Float32[4.0, 3.0, 2.0, 1.0]

    # We want to exercise the use of `copyto!` (-> `Graph::setInitialValue`) on
    # a tensor allocated with `Graph::addVariable`, but for some reason the test
    # below would fail with older SDKs and on an IPU model, so in that case we
    # use good ol' `Graph::AddConstant`.
    if Poplar.SDK_VERSION < v"2.6" && !USE_HARDWARE_IPU
        c1 = @cxxtest Poplar.GraphAddConstant(graph, h1)
    else
        c1 = @cxxtest Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[4], "c1")
        copyto!(graph, c1, h1)
    end
    c2 = @cxxtest Poplar.GraphAddConstant(graph, h2)
    @graph begin
        Poplar.GraphSetTileMapping(c1, 0)
        Poplar.GraphSetTileMapping(c2, 0)
    end

    Poplar.ProgramSequenceAdd(prog, Poplar.ProgramCopy(c1, Poplar.TensorFlatten(v1)))
    Poplar.ProgramSequenceAdd(prog, Poplar.ProgramCopy(c2, Poplar.TensorFlatten(v2)))

    flags = @cxxtest Poplar.OptionFlags()

    v3 = @cxxtest Poplar.PopopsAdd(graph, v1, v2, prog, "Add", flags)
    v4 = @cxxtest Poplar.PopopsAdd(graph, v3, v2, prog, "Add", flags)
    v5 = @cxxtest Poplar.PopopsAdd(graph, v1, Poplar.TensorTranspose(v2), prog, "Add", flags)

    # Init some variables which will be used to read back from the IPU
    # (model) the results of some basic operations.
    h3 = zeros(Float32, 4)
    h4 = zeros(Float32, 4)
    h5 = zeros(Float32, 4)
    @graph begin
        Poplar.GraphCreateHostRead("v3-read", v3)
        Poplar.GraphCreateHostRead("v4-read", v4)
        Poplar.GraphCreateHostRead("v5-read", v5)
    end

    engine = @cxxtest Poplar.Engine(graph, prog, flags)
    Poplar.EngineLoadAndRun(engine, device)

    # Read back some tensors and check the expected values.
    Poplar.EngineReadTensor(engine, "v3-read", h3)
    @test h3 == h1 + h2
    Poplar.EngineReadTensor(engine, "v4-read", h4)
    @test h4 == h3 + h2
    Poplar.EngineReadTensor(engine, "v5-read", h5)
    # TODO: try to write this test in terms of the other tensors.
    @test h5 == Float32[5.0, 3.5, 5.0, 3.5]

    # Release the device at the end of the program
    Poplar.DeviceDetach(device)
end

@testset "Poplar" begin
    @cxxtest Poplar.Tensor()

    @testset "Device manager" begin
        dm = Poplar.DeviceManager()
        @test Poplar.DeviceManagerGetNumDevices(dm) > 0
    end

    # Make sure that dereferencing the types pointers gives a non-totally-useless value.
    @testset "Types" begin
        @testset "$(type)" for type in (:BOOL, :CHAR, :UNSIGNED_CHAR, :SIGNED_CHAR,
                                        :UNSIGNED_SHORT, :SHORT, :UNSIGNED_INT, :INT,
                                        :UNSIGNED_LONG, :LONG, :UNSIGNED_LONGLONG,
                                        :LONGLONG, :HALF, :FLOAT)
            @test dereference(Cint, getfield(Poplar, type)()) != 0
        end
    end

    # Test a simple program using a software-emulated IPU (IPU model)
    @testset "IPU Model" begin
        model = @cxxtest Poplar.IPUModel()
        device = @cxxtest Poplar.IPUModelCreateDevice(model)
        test_poplar_program(device)
    end

    # Same test, but with a real IPU
    USE_HARDWARE_IPU && @testset "Hardware IPU" begin
        # Make sure `get_ipu_devices` works when you request 0 devices.
        device = @test_logs (:info, r"^Attached to devices with IDs [\w\d]+\[\]") Poplar.get_ipu_devices(0)
        @test isempty(device)
        # Simple test for `get_ipu_devices` with a range as second argument.
        Poplar.DeviceDetach.(@test_logs((:info, r"^Trying to attach to device 0..."),
                                        match_mode=:any,
                                        Poplar.get_ipu_devices(1, 0:0)))
        # Couldn't attach to all requested devices
        @test_logs((:warn, "Requested 2 devices, but could attach only to 0"),
                   (:info, r"^Attached to devices with IDs [\w\d]+\[\]"),
                   Poplar.get_ipu_devices(2, 0:-1))
        # Get a device
        device = @cxxtest @test_logs((:info, r"^Trying to attach to device"),
                                     (:info, r"^Successfully attached to device"),
                                     match_mode=:any,
                                     Poplar.get_ipu_device())
        # Run a test program
        test_poplar_program(device)
    end
end

end # module PoplarTest
