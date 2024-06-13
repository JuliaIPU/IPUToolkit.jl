# In Julia register CI, do nothing
if get(ENV, "JULIA_REGISTRYCI_AUTOMERGE", "false") == "true"
    exit(0)
end

##
using libcxxwrap_julia_jll
using Scratch
using Pkg.TOML
using UUIDs
##

include("generate_wrapper.jl")

const libpoplar_dir = joinpath(get_scratch!(UUID(TOML.parsefile(joinpath(dirname(@__DIR__), "Project.toml"))["uuid"]), "libpoplar"), "v$(Base.thispatch(VERSION))")

function build_bindings(; path::String=joinpath(libpoplar_dir, "libpoplar_julia.so"), generate_bindings::Bool=true, compile::Bool=true)
    if generate_bindings
        generate_wrapper()
    end

    if compile
        cxxwrap_include_dir = joinpath(libcxxwrap_julia_jll.artifact_dir, "include")
        julia_include_dir = joinpath(dirname(Sys.BINDIR), "include", "julia")
        mkpath(dirname(path))
        dir = joinpath(@__DIR__, "wrapper")
        run(```
            $(cxx)
            -O0
            -std=c++2a
            -fPIC
            -shared
            -I$(julia_include_dir)
            -I$(cxxwrap_include_dir)
            -I$(dir)
            -o $(path)
            $(joinpath(dir, "template.cpp"))
            -lpopops
            -lpoplar
            ```)
    end
    return nothing
end

build_bindings()
