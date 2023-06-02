using IPUToolkit.IPUCompiler, IPUToolkit.Poplar
using Enzyme

IPUCompiler.KEEP_LLVM_FILES[] = true

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

IPUCompiler.@codelet graph function RosenAdam(in::VertexVector{Float32, In}, out::VertexVector{Float32, Out})
    for idx in eachindex(out)
        out[idx] = adam(rosenbrock′, in[idx])
    end
end

input = Poplar.GraphAddConstant(graph, initial_points)
output = Poplar.GraphAddVariable(graph, Poplar.FLOAT(), collect(UInt64.(size(input))), "output");

prog = Poplar.ProgramSequence()
computeSetAdam = Poplar.GraphAddComputeSet(graph, "Adam")

# Create `num_tiles` vertices and spread the arrays over all tiles.
for tile in 0:(num_tiles - 1)
    s = cld(length(input) - 1, num_tiles)
    slice = (s * tile):(s * tile + s - 1)
    AdamVertex = Poplar.GraphAddVertex(graph, computeSetAdam, "RosenAdam")
    Poplar.GraphSetTileMapping(graph, input[slice], tile)
    Poplar.GraphSetTileMapping(graph, output[slice], tile)
    Poplar.GraphConnect(graph, AdamVertex["in"], input[slice])
    Poplar.GraphConnect(graph, AdamVertex["out"], output[slice])
    Poplar.GraphSetTileMapping(graph, AdamVertex, tile)
end

Poplar.ProgramSequenceAdd(prog, Poplar.ProgramExecute(computeSetAdam))

Poplar.GraphCreateHostRead(graph, "minima-read", output)

flags = Poplar.OptionFlags()
Poplar.OptionFlagsSet(flags, "debug.instrument", "true")

engine = Poplar.Engine(graph, prog, flags)
Poplar.EngineLoadAndRun(engine, device)
Poplar.EngineReadTensor(engine, "minima-read", minima)

Poplar.DeviceDetach(device)
