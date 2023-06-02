using IPUToolkit.IPUCompiler, IPUToolkit.Poplar
using Enzyme

IPUCompiler.KEEP_LLVM_FILES[] = true

device = Poplar.get_ipu_device()
target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)

tiles_per_iput = Int(Poplar.TargetGetNumTiles(target))

jl_input = collect(Float32.(range(-10; stop=10, length=10 * tiles_per_iput)))

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

IPUCompiler.@codelet graph function RosenAdam(in::VertexVector{Float32, In}, out::VertexVector{Float32, Out})
    for idx in eachindex(out)
        out[idx] = adam(rosenbrock′, in[idx])
    end
end

input = Poplar.GraphAddConstant(graph, jl_input)
output = Poplar.GraphAddVariable(graph, Poplar.FLOAT(), collect(UInt64.(size(jl_input))), "output");

prog = Poplar.ProgramSequence()
computeSetAdam = Poplar.GraphAddComputeSet(graph, "Adam")

# Spread the vertex across all tiles
for idx in 0:(length(jl_input) - 1)
    tile = mod(idx, tiles_per_iput - 1)
    AdamVertex = Poplar.GraphAddVertex(graph, computeSetAdam, "RosenAdam")
    Poplar.GraphSetTileMapping(graph, input[idx], tile)
    Poplar.GraphSetTileMapping(graph, output[idx], tile)
    Poplar.GraphConnect(graph, AdamVertex["in"], input[idx:idx])
    Poplar.GraphConnect(graph, AdamVertex["out"], output[idx:idx])
    Poplar.GraphSetTileMapping(graph, AdamVertex, tile)
end

Poplar.ProgramSequenceAdd(prog, Poplar.ProgramExecute(computeSetAdam))

flags = Poplar.OptionFlags()
Poplar.OptionFlagsSet(flags, "debug.instrument", "true")

engine = Poplar.Engine(graph, prog, flags)
Poplar.EngineLoadAndRun(engine, device)

Poplar.DeviceDetach(device)
