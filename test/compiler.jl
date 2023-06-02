module IPUCompilerTest

# Whether bounds are always checked
const check_bounds = Base.JLOptions().check_bounds == 1

using Test
using IPUToolkit.IPUCompiler
using IPUToolkit.Poplar
if Poplar.SDK_VERSION ≥ v"2.2.0" || !check_bounds
    using Enzyme
    using LinearAlgebra
    using Statistics
end
if !check_bounds
    using StaticArrays
end

# Silence progress spinners.
IPUCompiler.PROGRESS_SPINNER[] = false

include("common.jl")

∂(f, x) = first(first(autodiff_deferred(Reverse, f, Active(x))))

function test_compiler_program(device)
    target = @cxxtest Poplar.DeviceGetTarget(device)
    graph = @cxxtest Poplar.Graph(target)

    # Define a local function to make sure macro hygiene is right
    double(x) = x * 2
    @codelet graph function TimesTwo(inconst::VertexVector{Float32, In}, outvec::VertexVector{Float32, Out})
        outvec .= double.(inconst)
    end

    @codelet graph function Sort(invec::VertexVector{Float32, In}, outvec::VertexVector{Float32, Out})
        outvec .= invec
        sort!(outvec)
    end

    @codelet graph function Sin(invec::VertexVector{Float32, In}, outvec::VertexVector{Float32, Out})
        for idx in eachindex(outvec)
            @inbounds outvec[idx] = sin(invec[idx])
        end
    end

    @codelet graph function Print(outvec::VertexVector{Float32, Out})
        @ipuprint "Hello, world!"
        @ipuprint "Titire tu" " patule" " recubans sub tegmine " "fagi"
        @ipuprint "The Answer to the Ultimate Question of Life, the Universe, and Everything is " 42
        x = Int32(7)
        @ipushow x
    end

    input = Float32[5, 2, 10, 102, -10, 2, 256, 15, 32, 100]

    inconst = @cxxtest Poplar.GraphAddConstant(graph, input)
    outvec1 = @cxxtest Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[10], "outvec1");
    outvec2 = @cxxtest Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[10], "outvec2");
    outvec3 = @cxxtest Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[10], "outvec3");
    outvec4 = @cxxtest Poplar.GraphAddVariable(graph, Poplar.FLOAT(), UInt64[10], "outvec4");

    prog = @cxxtest Poplar.ProgramSequence()

    add_vertex(graph, prog, TimesTwo, inconst, outvec1)
    add_vertex(graph, prog, Sort, outvec1, outvec2)
    if VERSION ≥ v"1.7"
        # The `@device_override` business works well only on Julia v1.7+
        add_vertex(graph, prog, Sin, outvec2, outvec3)
    end
    add_vertex(graph, prog, Print, outvec4)
    @test_throws ArgumentError add_vertex(graph, prog, +, outvec4)
    @test_throws ArgumentError add_vertex(graph, prog, Print, outvec3, outvec4)

    # Init some variables which will be used to read back from the IPU
    # the results of some basic operations.
    output_timestwo = similar(input)
    Poplar.GraphCreateHostRead(graph, "timestwo-read", outvec1)
    output_sort = similar(input)
    Poplar.GraphCreateHostRead(graph, "sort-read", outvec2)
    if VERSION ≥ v"1.7"
        output_sin = similar(input)
        Poplar.GraphCreateHostRead(graph, "sin-read", outvec3)
    end

    flags = @cxxtest Poplar.OptionFlags()
    Poplar.OptionFlagsSet(flags, "debug.instrument", "true")

    engine = @cxxtest Poplar.Engine(graph, prog, flags)
    # Load and run the program, but capture the stderr, so that we can test that
    # it contains what we expect.
    pipe = Pipe()
    redirect_stderr(pipe) do
        Poplar.EngineLoadAndRun(engine, device)
    end
    output = IOBuffer()
    task = @async write(output, pipe)
    close(pipe)
    wait(task)
    lines = split(String(take!(output)), '\n')
    @test contains(lines[1], r"Hello, world!$")
    @test contains(lines[2], r"Titire tu patule recubans sub tegmine fagi$")
    @test contains(lines[3], r"The Answer to the Ultimate Question of Life, the Universe, and Everything is 42$")
    @test contains(lines[4], r"x = 7$")
    @test lines[end] == ""

    # Read back some tensors and check the expected values.
    Poplar.EngineReadTensor(engine, "timestwo-read", output_timestwo)
    @test output_timestwo == 2 .* input
    Poplar.EngineReadTensor(engine, "sort-read", output_sort)
    @test output_sort == sort(output_timestwo)
    if VERSION ≥ v"1.7"
        Poplar.EngineReadTensor(engine, "sin-read", output_sin)
        @test output_sin == sin.(output_sort)
    end

    Poplar.DeviceDetach(device)
end

function test_ipuprogram(device)
    N = 15_000
    input = randn(Float32, N)
    outvec1 = PoplarVector{Float32}(undef, N)
    outvec2 = PoplarVector{Float32}(undef, N)
    outvec3 = PoplarVector{Float32}(undef, N)
    outvec4 = PoplarVector{Float32}(undef, N)
    outvec5 = PoplarVector{Float32}(undef, N)
    outvec6 = PoplarVector{Float32}(undef, N)
    f(x) = cos(x)
    f′(x) = ∂(f, x)
    g(x) = tan(x)
    g′(x) = ∂(g, x)

    @ipuprogram device begin
        function TimesTwo(inconst::VertexVector{Float32, In}, outvec::VertexVector{Float32, Out})
            outvec .= 2 .* inconst
        end
        function Scale(invec::VertexVector{Float32, In}, outvec::VertexVector{Float32, Out})
            outvec .= invec
            # `sum(abs2, v)` is layman norm because we can't statically compile
            # `LinearAlgebra.norm!`.
            outvec .*= sqrt(length(outvec) / sum(abs2, outvec))
        end
        function Exp(invec::VertexVector{Float32, In}, outvec::VertexVector{Float32, Out})
            for idx in eachindex(outvec)
                @inbounds outvec[idx] = exp(invec[idx])
            end
        end
        function DiffCos(invec::VertexVector{Float32, In}, outvec::VertexVector{Float32, Out})
            outvec .= f′.(invec)
        end
        function DiffTan(invec::VertexVector{Float32, In}, outvec::VertexVector{Float32, Out})
            for idx in eachindex(outvec)
                @inbounds outvec[idx] = g′(invec[idx])
            end
        end
        function Random(out::VertexVector{Float32, Out})
            for idx in eachindex(out)
                out[idx] = rand(Float32)
            end
        end

        TimesTwo(input, outvec1)
        Scale(outvec1, outvec2)
        Exp(outvec2, outvec3)
        DiffCos(outvec3, outvec4)
        DiffTan(outvec4, outvec5)
        Random(outvec6)

        jl_outvec1 = outvec1
        jl_outvec2 = outvec2
        jl_outvec3 = outvec3
        jl_outvec4 = outvec4
        jl_outvec5 = outvec5
        jl_outvec6 = outvec6
    end
    Poplar.DeviceDetach(device)
    @test jl_outvec1 ≈ 2 .* input
    @test norm(jl_outvec2) ≈ sqrt(N)
    @test jl_outvec3 ≈ exp.(jl_outvec2)
    @test jl_outvec4 ≈ @. -sin(jl_outvec3)
    @test jl_outvec5 ≈ @. sec(jl_outvec4) ^ 2
    # There's a non-zero probability that this test may fail, but assuming an
    # average relative error of sqrt(N) / N, we multiply by `pi` to be somewhat
    # safe (and `pi` is cool).
    @test mean(jl_outvec6) ≈ 0.5 rtol=(pi * sqrt(N) / N)
end

rosenbrock(x, y=4) = (1 - x) ^ 2 + 100 * (y - x ^ 2) ^ 2
rosenbrock′(x) = ∂(rosenbrock, x)
# See Algorithm 1 at page 2 of https://arxiv.org/abs/1412.6980
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
    Δ = 10 * eps(T)
    δ = one(T)
    max_t = Int32(1_000_000)
    t = one(max_t)
    while abs(δ) > Δ && t ≤ max_t
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

function test_adam(device)
    input = collect(Float32.(-4:1:4))
    output = PoplarVector{Float32}(undef, length(input))
    @ipuprogram device begin
        function AdamRosenbrock(in::VertexVector{Float32, In}, out::VertexVector{Float32, Out})
            for idx in eachindex(out)
                out[idx] = adam(rosenbrock′, in[idx])
            end
        end
        AdamRosenbrock(input, output)
        jl_output = output
    end
    Poplar.DeviceDetach(device)
    @test all(isapprox.(jl_output, [repeat([-2], 4); repeat([2], 5)]; atol=2.6e-3))
end

function test_linalg(device)
    N = 16
    mat1 = randn(Float32, N)
    mat2 = randn(Float32, N)
    mul = PoplarVector{Float32}(undef, N)
    inverse = PoplarVector{Float32}(undef, N)

    @ipuprogram device begin
        function LinAlg(in1::VertexVector{Float32, In}, in2::VertexVector{Float32, In}, mul::VertexVector{Float32, Out}, inverse::VertexVector{Float32, Out})
            # Arguments can only be vectors, so we need to convert them to
            # (static) matrices to do some linear algebra stuff.  The conversion
            # to `SMatrix` has an internal check about the shape/size of the
            # to-be-converted array which would result in dynamic dispatch, we
            # need to skip the check with `@inbounds`, but we need to be extra
            # sure we're passing consistent data.
            m1 = @inbounds SMatrix{4,4,Float32,16}(in1)
            m2 = @inbounds SMatrix{4,4,Float32,16}(in2)
            m1_m2 = m1 * m2
            mul .= (m1_m2)[:]
            inverse .= inv(m1_m2)[:]
        end

        LinAlg(mat1, mat2, mul, inverse)

        jl_mul = mul
        jl_inv = inverse
    end
    Poplar.DeviceDetach(device)
    jl_mul = reshape(jl_mul, 4, 4)
    @test reshape(mat1, 4, 4) * reshape(mat2, 4, 4) ≈ jl_mul
    @test reshape(jl_inv, 4, 4) ≈ inv(jl_mul)
end

@testset "IPUCompiler" begin
    @testset "Test program: $(f)" for f in (test_compiler_program, test_ipuprogram, test_adam, test_linalg)
        function skip_test(f)
            @warn """
                  Skipping IPUCompiler test $(f).  To run this testset use
                      import Pkg; Pkg.test("IPUToolkit"; julia_args=`--check-bounds=auto`)
                  """
            @test_broken false
        end
        if Poplar.SDK_VERSION ≥ v"2.2.0" || !check_bounds
            if f in (test_linalg,) && check_bounds
                # * `test_linalg`: converting a `Vector` to `SMatrix` results
                #   into dynamic dispatch in the error path, this can be skipped
                #   with `@inbounds`, but `@inbounds` is no-op if we force
                #   bounds checks so we have no hope to run this nice test when
                #   using `--check-bounds=yes`.
                skip_test(f)
            else
                # Get a device
                device = @cxxtest @test_logs((:info, r"^Trying to attach to device"),
                                             (:info, r"^Successfully attached to device"),
                                             match_mode=:any,
                                             Poplar.get_ipu_device())
                # Run a test program
                f(device)
            end
        else
            # With --check-bounds=yes GPUCompiler generates a function mentioning an undefined
            # symbol `gpu_malloc`.  Mark the test as broken until we sort this out.  However
            # this function is optimised away when compiling with `-O1` or higher, and for
            # Poplar.SDK_VERSION ≥ v"2.2.0" we use `-O3`.
            skip_test(f)
        end
    end

    @testset "VertexVector" begin
        vec = VertexVector{Float32, Out}(undef, 10)
        @test vec.base == C_NULL
        @test vec.length == 10
        @test contains(repr(vec), r"VertexVector{Float32,.*Out}")
    end

    @testset "Printing to IPU" begin
        # Printing is already tested in the program above, here we only check
        # that disabling printing makes the `@ipu*` macros no-op.
        IPUCompiler.DISABLE_PRINT[] = true
        @test @macroexpand(@ipuprintf "Hello, world!") == :()
        @test @macroexpand(@ipuprint "Hello, world!") == :()
        @test @macroexpand(@ipushow x) == :()
        # Restore `DISABLE_PRINT`
        IPUCompiler.DISABLE_PRINT[] = false
    end
end

end # module IPUCompilerTest
