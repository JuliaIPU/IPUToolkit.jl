# IPUToolkit.jl

This is a small test repository containing WIP work and a playground full of joy to
be released into the world of Julia Researchers working with AI/ML Accelerators.

## Requirements

We currently require Julia v1.6 (only this minor version is supported), GCC 10+ as compiler (it requires support for the C++20 standard), and the Poplar SDK v1.3, v2.0, v2.1, v2.2, v2.3, or v2.4.
Other versions of the Poplar SDK are not currently supported.

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

### Interface to Poplar SDK

After having built the package, you can start using it by loading the `IPUToolkit.Poplar` module:

```julia
julia> using IPUToolkit.Poplar

julia> dm = Poplar.DeviceManager();

julia> Int(Poplar.DeviceManagerGetNumDevices(dm))
129

julia> device = Poplar.get_ipu_device()
[ Info: Trying to attach to device 0...
[ Info: Successfully attached to device 0
[ Info: Attached to devices with IDs [0]
IPUToolkit.Poplar.DeviceAllocated(Ptr{Nothing} @0x00000000016bd680)

julia> Int(Poplar.DeviceGetId(device))
0

julia> Poplar.DeviceDetach(device)
```

We automatically generate the bindings of the Poplar SDK using [`Clang.jl`](https://github.com/JuliaInterop/Clang.jl) and [`CxxWrap.jl`](https://github.com/JuliaInterop/CxxWrap.jl).
There is not automatic documentation at the moment, but functions can be accessed from the `Poplar` submodule.
Remember that Julia does not use class-based object-oriented programming, class instances will usually be first arguments of the methods you want to use.

Function naming convention and signature is usually as follows:

* class name in [CamelCase](https://en.wikipedia.org/wiki/Camel_case), followed by method name also in CamelCase.  Note that first letter of method name is always uppercase in this naming convention, even if it is lowercase in the Poplar SDK.  For example, the method `getNumDevices` of the `DeviceManager` class can be accessed in the `Poplar` submodule with `Poplar.DeviceManagerGetNumDevices`;
* the first argument of the function is the class instance.  For example, to use the Julia function `Poplar.DeviceManagerGetNumDevices`, you need to pass as first argument an instance of `DeviceManager`;
* the following arguments are the same as in the method you want to use in the SDK.  For example, the method `getNumDevices` of the `DeviceManager` class doesn't take any argument, so the Julia function `Poplar.DeviceManagerGetNumDevices` will take an instance of `DeviceManager` as *only* argument.
