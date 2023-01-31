# Test the world, publish later

This is a small test repository containing WIP work and a playground full of joy to
be released into the world of Julia Researchers working with AI/ML Accelerators.

## Requirements

We currently require `1.6` (only this minor version is supported), GCC 10 as compiler (it
requires support for the C++20 standard), and the Poplar SDK v1.3.0.

## Installation

After cloning the repository, enter inside this directory and start Julia with

```
julia --project
```

and then build the package with

```julia
using Pkg
Pkg.build()
```

This step will compile a wrapper around the Poplar SDK that can be used by Julia.  It will
take a while, without printing an update to screen, hold on.

## Usage

After having built the package, you can start using it by loading the `Poplar` module:

```julia
julia> using Poplar

julia> dm = Poplar.DeviceManager();

julia> Int(Poplar.DeviceManagerGetNumDevices(dm))
129
```
