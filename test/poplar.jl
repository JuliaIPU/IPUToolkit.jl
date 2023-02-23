using Test
using IPUToolkit.Poplar
using CxxWrap

# We often want to check that some CxxWrap objects are not NULL.
macro cxxtest(ex)
    return quote
        local out = $(esc(ex))
        Test.@test out.cpp_object != C_NULL
        out
    end
end

# https://giordano.github.io/blog/2019-05-03-julia-get-pointer-value/
dereference(T::DataType, ptr::Ptr) = unsafe_load(Ptr{T}(ptr))
dereference(T::DataType, ptr::CxxRef) = dereference(T, ptr.cpp_object)
dereference(T::DataType, ptr::Poplar.Type_Allocated) = dereference(T, ptr.cpp_object)

function test_program(device)
    target = @cxxtest Poplar.DeviceGetTarget(device)
    graph = @cxxtest Poplar.Graph(target)
    Poplar.PopopsAddCodelets(graph)

    v1 = @cxxtest Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[2, 2], "v1")
    v2 = @cxxtest Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[2, 2], "v2")

    for i in 0:1
        for j in 0:1
            Poplar.GraphSetTileMapping(graph, v1[i][j], i*2 + j)
            Poplar.GraphSetTileMapping(graph, v2[i][j], j*2 + i)
        end
    end

    prog = @cxxtest Poplar.ProgramSequence()

    h1 = Float32[1.0, 1.5, 2.0, 2.5]
    h2 = Float32[4.0, 3.0, 2.0, 1.0]

    c1 = @cxxtest Poplar.GraphAddConstant(graph, Poplar.FLOAT(), UInt64[4], h1)
    c2 = @cxxtest Poplar.GraphAddConstant(graph, Poplar.FLOAT(), UInt64[4], h2)
    Poplar.GraphSetTileMapping(graph, c1, 0)
    Poplar.GraphSetTileMapping(graph, c2, 0)

    Poplar.ProgramSequenceAdd(prog, Poplar.ProgramCopy(c1, Poplar.TensorFlatten(v1)))
    Poplar.ProgramSequenceAdd(prog, Poplar.ProgramCopy(c2, Poplar.TensorFlatten(v2)))

    flags = @cxxtest Poplar.OptionFlags()

    v3 = @cxxtest Poplar.PopopsAdd(graph, v1, v2, prog, "Add", flags)
    v4 = @cxxtest Poplar.PopopsAdd(graph, v3, v2, prog, "Add", flags)
    v5 = @cxxtest Poplar.PopopsAdd(graph, v1, Poplar.TensorTranspose(v2), prog, "Add", flags)

    # Init some variables which will be used to read back from the IPU
    # (model) the results of some basic operations.
    h3 = zeros(Float32, 4)
    Poplar.GraphCreateHostRead(graph, "v3-read", v3)
    h4 = zeros(Float32, 4)
    Poplar.GraphCreateHostRead(graph, "v4-read", v4)
    h5 = zeros(Float32, 4)
    Poplar.GraphCreateHostRead(graph, "v5-read", v5)

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
end


@testset "Poplar.jl" begin
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
        test_program(device)
    end

    # Same test, but with a real IPU
    @testset "Hardware IPU" begin
        device = @cxxtest Poplar.getIPU()
        test_program(device)
    end
end
