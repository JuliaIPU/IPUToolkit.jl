module IPUToolkit

if get(ENV, "JULIA_REGISTRYCI_AUTOMERGE", "false") != "true"
    include("poplar.jl")
    include("compiler/compiler.jl")
end

end # module IPUToolkit
