using Enzyme

make_grid(x::T, y::T) where {T<:AbstractVector} =
    repeat(x; inner=length(y)), repeat(y; outer=length(x))
# High resolution range
x_range = y_range = collect(Float32.(range(-6; step=2^-5, length=368)))
# # Low resolution range, with exactly 1472 points
# x_range = collect(Float32.(range(-11; step=2^-1, length=23 * 2)))
# y_range = collect(Float32.(range(-8; step=2^-1, length=32)))
# Inputs to the codelet
x₀, y₀ = make_grid(x_range, y_range)
# Output of the codelet
num_iterations = similar(x₀, Int32)

rosenbrock(x, y) = (1 - x) ^ 2 + 100 * (y - x ^ 2) ^ 2
rosenbrock′(x, y) = ∂(rosenbrock, x, y)
function adam(∂f, x₀::T, y₀::T) where {T}
    x, y = x₀, y₀
    # Some constants
    α = T(0.001) # learning rate
    β₁ = T(0.9)
    β₂ = T(0.999)
    ϵ = T(1e-8)
    # Momenta
    m = zero(T), zero(T)
    v = zero(T), zero(T)
    # Stopping criteria
    ε = 10 * eps(T)
    δ_x, δ_y = one(T), one(T)
    max_t = Int32(500_000)
    t = one(max_t)
    while abs(δ_x) > ε < abs(δ_y) && t ≤ max_t
        g = ∂f(x, y)
        m = β₁ .* m .+ (1 - β₂) .* g
        v = β₂ .* v .+ (1 - β₂) .* g .^ 2
        m̂ = m ./ (1 - β₁ ^ t)
        v̂ = v ./ (1 - β₂ ^ t)
        δ_x, δ_y = α .* m̂ ./ (.√(v̂) .+ ϵ)
        x -= δ_x
        y -= δ_y
        t += one(t)
    end
    # Return the number of iterations, subtract one because at the end of the last iteration
    # we added 1 to the counter but didn't run the following iteration.
    return t - one(t)
end
