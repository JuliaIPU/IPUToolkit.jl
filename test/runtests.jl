using Test
using Poplar

# We often want to check that some CxxWrap objects are not NULL.
macro cxxtest(ex)
    return :( Test.@test $(esc(ex)).cpp_object != C_NULL )
end

@testset "Poplar.jl" begin
    @cxxtest Poplar.Tensor()
    dm = Poplar.DeviceManager()
    @test Poplar.DeviceManagerGetNumDevices(dm) > 0

    # Some simple code (NOTE: very incomplete at the moment)
    model = Poplar.IPUModel()
    @cxxtest model
    device = Poplar.IPUModelCreateDevice(model)
    @cxxtest device
    target = Poplar.DeviceGetTarget(device)
    @cxxtest target
    graph = Poplar.Graph(target)
    @cxxtest graph
    Poplar.PopopsAddCodelets(graph)
end
