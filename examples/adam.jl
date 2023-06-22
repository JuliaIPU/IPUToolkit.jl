using IPUToolkit.IPUCompiler, IPUToolkit.Poplar
using Enzyme

IPUCompiler.KEEP_LLVM_FILES[] = true
ENV["POPLAR_RUNTIME_OPTIONS"] = """{"target.hostSyncTimeout":"60"}"""

device = Poplar.get_ipu_device()
target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)

num_tiles = Int(Poplar.TargetGetNumTiles(target))

initial_points = collect(Float32.(range(-4; stop=4, length=10 * num_tiles)))
minima = similar(initial_points)

∂(f, x) = first(first(autodiff_deferred(Reverse, f, Active(x))))
rosenbrock(x, y=4) = (1 - x) ^ 2 + 100 * (y - x ^ 2) ^ 2
rosenbrock′(x) = ∂(rosenbrock, x)
function adam(∂f, x₀::T) where {T}
    x = x₀
    # Some constants
    α = T(0.001) # learning rate
    β₁ = T(0.9)
    β₂ = T(0.999)
    ϵ = T(1e-8)
    # Momenta
    m = zero(T)
    v = zero(T)
    # Stopping criteria
    ε = 10 * eps(T)
    δ = one(T)
    max_t = Int32(1_000_000)
    t = one(max_t)
    while abs(δ) > ε && t ≤ max_t
        g = ∂f(x)
        m = β₁ * m + (1 - β₂) * g
        v = β₂ * v + (1 - β₂) * g ^ 2
        m̂ = m / (1 - β₁ ^ t)
        v̂ = v / (1 - β₂ ^ t)
        δ = α * m̂ / (√(v̂) + ϵ)
        x -= δ
        t += one(t)
    end
    return x
end

@codelet graph function RosenAdam(in::VertexVector{Float32, In}, out::VertexVector{Float32, Out})
    for idx in eachindex(out)
        out[idx] = adam(rosenbrock′, in[idx])
    end
end

initial_points_ipu = Poplar.GraphAddConstant(graph, initial_points)
minima_ipu = similar(graph, minima, "minima");

prog = Poplar.ProgramSequence()

add_vertex(graph, prog, 0:(num_tiles - 1), RosenAdam, initial_points_ipu, minima_ipu)

Poplar.GraphCreateHostRead(graph, "minima-read", minima_ipu)

flags = Poplar.OptionFlags()
Poplar.OptionFlagsSet(flags, "debug.instrument", "true")

engine = Poplar.Engine(graph, prog, flags)
Poplar.EngineLoadAndRun(engine, device)
Poplar.EngineReadTensor(engine, "minima-read", minima)

Poplar.DeviceDetach(device)
