# Test the world, publish later

This is a small test repository containing WIP work and a playground full of joy to
be released into the world of Julia Researchers working with AI/ML Accelerators.

## How to setup this mess

We are currently depending on julia `1.6`, `g++-10` as compiler, and `poplar v1.3.0`.
Start Julia activating the provided environment with the command:

```shell
julia --project=.
```

To setup the code:

```julia
julia> using Pkg; Pkg.instantiate()
julia> using CPPBindgen
julia> CPPBindgen.build_bindings()
```

## Use the bindings

Using the bindings in julia is facilitated by cxxwarp, refer to `src/bindings.jl`.

To finally use the generated library:

```julia
julia> include("bindings.jl")
julia> m = Poplar.DeviceManager()
julia> Int(Poplar.DeviceManagerGetNumDevices(m))
```

---
