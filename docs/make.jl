using Documenter, IPUToolkit, IPUToolkit.Poplar, IPUToolkit.IPUCompiler

makedocs(
    modules = [Poplar, IPUCompiler],
    sitename = "IPUToolkit.jl",
    pages    = [
        "IPUToolkit" => "index.md",
        "Poplar SDK" => "poplar.md",
        "Writing codelets" => "compiler.md",
    ],
    format = Documenter.HTML(; edit_link="main"),
)

deploydocs(
    repo = "github.com/JuliaIPU/IPUToolkit.jl.git",
    target = "build",
    deps = nothing,
    make = nothing,
    devbranch = "main",
)
