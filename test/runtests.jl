using Test
using Poplar
using CxxWrap

# We often want to check that some CxxWrap objects are not NULL.
macro cxxtest(ex)
    return :( Test.@test $(esc(ex)).cpp_object != C_NULL )
end

# https://giordano.github.io/blog/2019-05-03-julia-get-pointer-value/
dereference(T::DataType, ptr::Ptr) = unsafe_load(Ptr{T}(ptr))
dereference(T::DataType, ptr::CxxRef) = dereference(T, ptr.cpp_object)

@testset "Poplar.jl" begin
    @cxxtest Poplar.Tensor()
    dm = Poplar.DeviceManager()
    @test Poplar.DeviceManagerGetNumDevices(dm) > 0

    @testset "Types" begin
        # TODO: make sure these tests makes sense, but my understanding is that these types
        # should be non-zero enum-like values.
        for type in (:BOOL, :CHAR, :UNSIGNED_CHAR, :SIGNED_CHAR, :UNSIGNED_SHORT, :SHORT,
                     :UNSIGNED_INT, :INT, :UNSIGNED_LONG, :LONG, :UNSIGNED_LONGLONG,
                     :LONGLONG, :HALF, :FLOAT)
            @test dereference(Cint, getfield(Poplar, type)) != 0
        end
    end

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

    v1 = Poplar.GraphAddVariable(graph, Poplar.FLOAT, UInt64[2, 2], "v1")
    v2 = Poplar.GraphAddVariable(graph, Poplar.FLOAT, UInt64[2, 2], "v2")
end
