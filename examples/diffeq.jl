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

p = [7f0, 28f0, 8f0 / 3f0]

n = 10000
t = Vector{Float32}(undef, n)
u1 = Vector{Float32}(undef, n)
u2 = Vector{Float32}(undef, n)
u3 = Vector{Float32}(undef, n)

### Start IPU program

ENV["POPLAR_RUNTIME_OPTIONS"] = """{"target.hostSyncTimeout":"60"}"""

IPUCompiler.PROGRESS_SPINNER[] = false

device = Poplar.get_ipu_device()
target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)

@codelet graph function solve_lorenz(t::VertexVector{Float32, Out},
                                     u1::VertexVector{Float32, Out},
                                     u2::VertexVector{Float32, Out},
                                     u3::VertexVector{Float32, Out},
                                     p::VertexVector{Float32, In})
    u0 = @SVector [1f0; 0f0; 0f0]
    svp = @inbounds SVector{3, Float32}(p)
    integ = DiffEqGPU.init(GPUTsit5(), lorenz, false, u0, 0f0, 0.005f0, svp, nothing, CallbackSet(nothing), true, false)
    for idx in eachindex(t, u1, u2, u3)
        DiffEqGPU.step!(integ, integ.t + integ.dt, integ.u)
        t[idx] = integ.t
        u1[idx] = integ.u[1]
        u2[idx] = integ.u[2]
        u3[idx] = integ.u[3]
    end
    return nothing
end

p_ipu = Poplar.GraphAddConstant(graph, p)
t_ipu = Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[n], "times")
u1_ipu = similar(graph, t_ipu, "u1")
u2_ipu = similar(graph, t_ipu, "u2")
u3_ipu = similar(graph, t_ipu, "u3")

prog = Poplar.ProgramSequence()
add_vertex(graph, prog, solve_lorenz, t_ipu, u1_ipu, u2_ipu, u3_ipu, p_ipu)

Poplar.GraphCreateHostRead(graph, "times-read", t_ipu)
Poplar.GraphCreateHostRead(graph, "u1-read", u1_ipu)
Poplar.GraphCreateHostRead(graph, "u2-read", u2_ipu)
Poplar.GraphCreateHostRead(graph, "u3-read", u3_ipu)

engine = Poplar.Engine(graph, prog)
Poplar.EngineLoadAndRun(engine, device)

Poplar.EngineReadTensor(engine, "times-read", t)
Poplar.EngineReadTensor(engine, "u1-read", u1)
Poplar.EngineReadTensor(engine, "u2-read", u2)
Poplar.EngineReadTensor(engine, "u3-read", u3)

Poplar.DeviceDetach(device)
