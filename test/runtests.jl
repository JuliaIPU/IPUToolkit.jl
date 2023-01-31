using Test
using Poplar

@testset "Poplar.jl" begin
    @test Poplar.Tensor().cpp_object != C_NULL
    dm = Poplar.DeviceManager()
    @test Poplar.DeviceManagerGetNumDevices(dm) > 0

    # Some simple code (NOTE: very incomplete at the moment)
    model = Poplar.IPUModel()
    @test model.cpp_object != C_NULL
    device = Poplar.IPUModelCreateDevice(model)
    @test device.cpp_object != C_NULL
    target = Poplar.DeviceGetTarget(device)
    @test target.cpp_object != C_NULL
    graph = Poplar.Graph(target)
    @test graph.cpp_object != C_NULL
    Poplar.PopopsAddCodelets(graph)
end
