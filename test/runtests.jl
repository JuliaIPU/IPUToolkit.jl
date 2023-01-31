using Test
using Poplar

@testset "Poplar.jl" begin
    @test Poplar.Tensor().cpp_object != C_NULL
end
