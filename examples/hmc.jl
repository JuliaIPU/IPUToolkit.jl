using IPUToolkit.IPUCompiler, IPUToolkit.Poplar
using Enzyme

IPUCompiler.KEEP_LLVM_FILES[] = true
ENV["POPLAR_RUNTIME_OPTIONS"] = """{"target.hostSyncTimeout":"30"}"""

device = Poplar.get_ipu_device()
target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)

num_tiles = Int(Poplar.TargetGetNumTiles(target))

∂!(f, x, f′) = autodiff_deferred(Reverse, f, Duplicated(x, f′))

neg_log_density(q::AbstractVector{T}) where {T} = (q[1]^2  - q[2])^2 + (q[1]- one(T))^2 / T(100)

# Note: both input and output must have exactly same type (including *all* parameters).
function grad_neg_log_density!(f′::V, x::V) where {T,V<:AbstractVector{T}}
    # The derivative is added to duplicated arguments, so we need to zero f′
    # before going on.
    f′ .= zero(T)
    ∂!(neg_log_density, x, f′)
    return f′
end

function leapfrog!(q::AbstractVector{T}, p::AbstractVector{T}, f′::AbstractVector{T}, dt::T) where {T}
    grad_neg_log_density!(f′, q)
    p .-= (dt ./ 2) .* f′
    q .+= dt .* p
    grad_neg_log_density!(f′, q)
    p .-= (dt / 2) .* f′
end

function sample_transition!(q_proposed::AbstractVector{T}, p::AbstractVector{T}, f′::AbstractVector{T}, q::AbstractVector{T}, dt::T, n_step) where {T}
    randn2!(p)
    h_init = sum(abs2, p) / 2 + neg_log_density(q)
    q_proposed .= q
    for step in UInt32(1):n_step
        leapfrog!(q_proposed, p, f′, dt)
    end
    h_diff = h_init - (sum(abs2, p) / 2 + neg_log_density(q_proposed))
    accept_prob = isnan(h_diff) ? zero(T) : exp(min(0, h_diff))
    if rand(T) >= accept_prob
        q_proposed .= q
    end
    return accept_prob
end

function sample_chain!(q_chain::AbstractVector{T}, buffer_q::AbstractVector{T}, p::AbstractVector{T}, f′::AbstractVector{T}, orig_q::AbstractVector{T}, n_sample, n_step, dt::T) where {T}
    sum_accept_prob = zero(T)
    buffer_q .= orig_q
    for sample in UInt32(1):n_sample
        accept_prob = sample_transition!(buffer_q, p, f′, orig_q, dt, n_step)
        for idx in eachindex(buffer_q)
            @inbounds q_chain[length(buffer_q) * (sample - 1) + idx] = buffer_q[idx]
        end
        sum_accept_prob += accept_prob
    end
    return sum_accept_prob / n_sample
end

n_sample = UInt32(10)
n_step = UInt32(10)
dt = Float32(0.1)

@eval @codelet graph function HamiltonianMonteCarlo(
    q_chain::VertexVector{Float32, InOut},
    buffer_q::VertexVector{Float32, InOut},
    p::VertexVector{Float32, InOut},
    gradient::VertexVector{Float32, InOut},
    orig_q::VertexVector{Float32, InOut},
    )
    sample_chain!(q_chain, buffer_q, p, gradient, orig_q, $(n_sample), $(n_step), $(dt))
end

orig_q = randn(Float32, 2 * num_tiles)

orig_q_ipu = Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[length(orig_q)], "orig_q")
copyto!(graph, orig_q_ipu, orig_q)
buffer_q_ipu = similar(graph, orig_q, "buffer_q")
p_ipu = similar(graph, orig_q, "p")
gradient_ipu = similar(graph, orig_q, "gradient")
q_chain_ipu = Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[length(orig_q) * n_sample], "q_chain")
q_chain = Matrix{Float32}(undef, length(orig_q), n_sample)

prog = Poplar.ProgramSequence()

add_vertex(graph, prog, 0:(num_tiles - 1), HamiltonianMonteCarlo,
           q_chain_ipu, buffer_q_ipu, p_ipu, gradient_ipu, orig_q_ipu)

Poplar.GraphCreateHostRead(graph, "q-chain-read", q_chain_ipu)

flags = Poplar.OptionFlags()
Poplar.OptionFlagsSet(flags, "debug.instrument", "false")

engine = Poplar.Engine(graph, prog, flags)
Poplar.EngineLoadAndRun(engine, device)
Poplar.EngineReadTensor(engine, "q-chain-read", q_chain)

Poplar.detach_devices()

#=

using Plots

sample = 10
scatter(q_chain[1:2:end, sample], q_chain[2:2:end, sample]; xlims=(-3, 3), ylims=(-3, 6))

=#
