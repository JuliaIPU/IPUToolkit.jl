using Documenter, IPUToolkit, IPUToolkit.Poplar, IPUToolkit.IPUCompiler

# Pretend to be GitHub Action to publish the documentation.  Note that in order to actually
# publish you also need to have other secret environment variables , `GITHUB_ACTOR` and
# `DOCUMENTER_KEY` set appropriately:
#
# * `GITHUB_TOKEN`: a GitHub Personal Access Token
#   (https://github.com/settings/tokens?type=beta) with write access to the repo
# * `GITHUB_ACTOR`: your GitHub username
# * `DOCUMENTER_KEY`: generate with `DocumenterTools.genkeys`
#   (https://documenter.juliadocs.org/stable/lib/public/#DocumenterTools.genkeys)
#
ENV["GITHUB_EVENT_NAME"] = "push"
ENV["GITHUB_REPOSITORY"] = "github.com/giordano/julia-ipu.git"
ENV["GITHUB_REF"] = "refs/heads/main"

makedocs(
    modules = [Poplar, IPUCompiler],
    sitename = "IPUToolkit.jl",
    pages    = [
        "IPUToolkit" => "index.md",
        "Poplar SDK" => "poplar.md",
        "Writing codelets" => "compiler.md",
    ],
    strict = true,
    format = Documenter.HTML(; edit_link="main"),
)

deploydocs(
    repo = "github.com/giordano/julia-ipu.git",
    target = "build",
    deps = nothing,
    make = nothing,
    devbranch = "main",
)
