using Test

include("../src/CPPBindgen.jl")

const lib_path = "test.so"

function cleanup()
    @info "Cleanup, remove dangling files (test.so)"
    rm(lib_path, force=true)
end

cleanup()

@testset "Build" begin
    CPPBindgen.build_bindings(lib_path)
    @test isfile(lib_path)
    @eval module tm include("load_fixture.jl") end
    tensor_alloc = tm.Tensor()
    @test tensor_alloc !== nothing
end