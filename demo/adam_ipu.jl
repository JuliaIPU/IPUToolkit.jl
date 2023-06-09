using IPUToolkit.IPUCompiler, IPUToolkit.Poplar
using Plots

include("adam_common.jl")

IPUCompiler.KEEP_LLVM_FILES[] = true
ENV["POPLAR_RUNTIME_OPTIONS"] = """{"target.hostSyncTimeout":"120"}"""

device = Poplar.get_ipu_device()
target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)

num_tiles = Int(Poplar.TargetGetNumTiles(target))

∂(f, x, y) = first(autodiff_deferred(Reverse, f, Active(x), Active(y)))

@codelet graph function RosenAdam(x::VertexVector{Float32, In},
                                  y::VertexVector{Float32, In},
                                  num_iterations::VertexVector{Int32, Out})
    for idx in eachindex(num_iterations)
        num_iterations[idx] = adam(rosenbrock′, x[idx], y[idx])
    end
end

x₀_ipu = Poplar.GraphAddConstant(graph, x₀)
y₀_ipu = Poplar.GraphAddConstant(graph, y₀)
num_iterations_ipu = similar(graph, x₀_ipu, Int32);

prog = Poplar.ProgramSequence()

add_vertex(graph, prog, 0:(num_tiles - 1), RosenAdam, x₀_ipu, y₀_ipu, num_iterations_ipu)

Poplar.GraphCreateHostRead(graph, "iterations-read", num_iterations_ipu)

engine = Poplar.Engine(graph, prog)
elapsed = @elapsed Poplar.EngineLoadAndRun(engine, device)
Poplar.EngineReadTensor(engine, "iterations-read", num_iterations)

Poplar.DeviceDetach(device)

seriescolor = :linear_tritanopic_krjcw_5_95_c24_n256
xticks = yticks = -10:2:10
m = reshape(sqrt.(Int.(num_iterations)), length(y_range), length(x_range))
fig = heatmap(x_range, y_range, m;
              seriescolor,
              xlabel = "x₀",
              ylabel = "y₀",
              xticks,
              yticks,
              colorbar_title = "sqrt(iterations)",
              title = "Minimisation of Rosenbrock function",
              )
savefig(fig, "rosenbrock_iterations.png")
savefig(fig, "rosenbrock_iterations.pdf")

fig = heatmap(x_range, y_range, log10.(rosenbrock.(x_range', y_range));
              seriescolor,
              xlabel = "x",
              ylabel = "y",
              xticks,
              yticks,
              colorbar_title = "log10(rosenbrock)",
              title = "Rosenbrock function",
              )
savefig(fig, "rosenbrock_fun.png")
savefig(fig, "rosenbrock_fun.pdf")
