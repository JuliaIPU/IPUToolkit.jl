using IPUToolkit.IPUCompiler
using IPUToolkit.Poplar
using DiffEqGPU
using StaticArrays
using OrdinaryDiffEq
using Plots

function lorenz(u, p, t)
    σ = p[1]
    ρ = p[2]
    β = p[3]
    du1 = σ * (u[2] - u[1])
    du2 = u[1] * (ρ - u[3]) - u[2]
    du3 = u[1] * u[2] - β * u[3]
    return SVector{3}(du1, du2, du3)
end

### Start IPU program

ENV["POPLAR_RUNTIME_OPTIONS"] = """{"target.hostSyncTimeout":"60"}"""

IPUCompiler.PROGRESS_SPINNER[] = false

device = Poplar.get_ipu_device()
target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)

num_tiles = Int(Poplar.TargetGetNumTiles(target))
tiles = 0:(num_tiles - 1)

p = [7f0, 28f0, 8f0 / 3f0]

n = 10000
u1 = [Vector{Float32}(undef, n) for _ in tiles]
u2 = [Vector{Float32}(undef, n) for _ in tiles]

@codelet graph function solve_lorenz(u1::VertexVector{Float32, Out},
                                     u2::VertexVector{Float32, Out},
                                     p::VertexVector{Float32, In})
    u0 = @SVector [1f0; 0f0; 0f0]
    svp = @inbounds SVector{3, Float32}(p)
    integ = DiffEqGPU.init(GPUTsit5(), lorenz, false, u0, 0f0, 0.005f0, svp, nothing, CallbackSet(nothing), true, false)
    for idx in eachindex(u1, u2)
        DiffEqGPU.step!(integ, integ.t + integ.dt, integ.u)
        u1[idx] = integ.u[1]
        u2[idx] = integ.u[2]
    end
    return nothing
end

p_ipu =  [Poplar.GraphAddConstant(graph, p .* Float32(tile + 1)) for tile in tiles]
u1_ipu = [Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[n], "u1_$(tile)") for tile in tiles]
u2_ipu = [Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[n], "u1_$(tile)") for tile in tiles]

prog = Poplar.ProgramSequence()

for tile in tiles
    add_vertex(graph, prog, tile, solve_lorenz, u1_ipu[tile+1], u2_ipu[tile+1], p_ipu[tile+1])
end

for tile in tiles
    Poplar.GraphCreateHostRead(graph, "u1-read_$(tile)", u1_ipu[tile+1])
    Poplar.GraphCreateHostRead(graph, "u2-read_$(tile)", u2_ipu[tile+1])
end

engine = Poplar.Engine(graph, prog)
Poplar.EngineLoadAndRun(engine, device)

for tile in tiles
    Poplar.EngineReadTensor(engine, "u1-read_$(tile)", u1[tile+1])
    Poplar.EngineReadTensor(engine, "u2-read_$(tile)", u2[tile+1])
end

Poplar.DeviceDetach(device)
