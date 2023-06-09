include("adam_common.jl")

∂(f, x, y) = first(autodiff(Reverse, f, Active(x), Active(y)))

@time @eval let
    tasks = [Threads.@spawn adam(rosenbrock′, x₀[idx], y₀[idx]) for idx in eachindex(x₀, y₀)]
    num_iterations .= fetch.(tasks)
end
