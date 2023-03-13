# IPUToolkit.jl

This package allows you to interface the [Intelligence Processing Unit (IPU) by Graphcore](https://www.graphcore.ai/products/ipu) using the [Julia programming language](https://julialang.org/).

***Disclaimer**: at the moment this is package is in a proof-of-concept stage, not suited for production usage.*

## Requirements

This package requires Julia v1.6+ (currently tested up to Julia v1.9), GCC 10+ as compiler (it requires support for the C++20 standard), and the Poplar SDK v1.3, or v2.0-v2.5.
Other versions of the Poplar SDK are not currently supported.

Note that both Julia and the Poplar SDK are coupled to a specific version of the LLVM compiler framework, and you will need to match a specific version of the Poplar SDK with a version of Julia using the same major version of LLVM.
For example, the Poplar SDK v2.2 uses LLVM 13, which is available in Julia v1.8, while the Poplar SDK versions 2.3-2.5 use LLVM 14, which is available in Julia v1.9.

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

This step will compile a wrapper around the Poplar SDK that can be used by Julia.
It will take a while, without printing an update to screen, hold on.

### Notes about build script

The build script uses the package [`Clang.jl`](https://github.com/JuliaInterop/Clang.jl) to automatically parse the headers of the Poplar SDK and generate a C++ file which is then compiled with [`CxxWrap.jl`](https://github.com/JuliaInterop/CxxWrap.jl), to be able to call the C++ methods in the SDK from Julia.

Currently the build script works correctly only with the minor version of Julia v1.6 (more specifically, it requires `Clang.jl` v0.14, which is coupled to Julia v1.6 only), see issue [#6](https://github.com/giordano/julia-ipu/issues/6) for more details.
This means that if you want to use Julia v1.7+, you need first to run with Julia v1.6 the build script for the Poplar SDK version you want to use.  When issue #6 will be fixed, this double pass will not be needed anymore.

## Usage

The package is called IPUToolkit because it provides different tools to interface the IPU from Julia:

* you can use functionalities in the [Poplar SDK](https://www.graphcore.ai/products/poplar);
* you can use Julia's code generation capabilities to automatically compile native code that can be run on the IPU.

These two approaches are available in two different submodules of the `IPUToolkit` package, `IPUToolkit.Poplar` and `IPUToolkit.IPUCompiler`.

### Interface to Poplar SDK

A taster of use of the Poplar SDK functionalities:

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
Also, the `IPUToolkit.Poplar` submodule wraps a subset of the functionalities available in the Poplar SDK, do not expect to be able to use all functionalities.
Remember that Julia does not use class-based object-oriented programming, class instances will usually be first arguments of the methods you want to use.

Function naming convention and signature is usually as follows:

* class name in [CamelCase](https://en.wikipedia.org/wiki/Camel_case), followed by method name also in CamelCase.  Note that first letter of method name is always uppercase in this naming convention, even if it is lowercase in the Poplar SDK.  For example, the method `getNumDevices` of the `DeviceManager` class can be accessed in the `Poplar` submodule with `Poplar.DeviceManagerGetNumDevices`;
* the first argument of the function is the class instance.  For example, to use the Julia function `Poplar.DeviceManagerGetNumDevices`, you need to pass as first argument an instance of `DeviceManager`;
* the following arguments are the same as in the method you want to use in the SDK.  For example, the method `getNumDevices` of the `DeviceManager` class doesn't take any argument, so the Julia function `Poplar.DeviceManagerGetNumDevices` will take an instance of `DeviceManager` as *only* argument.

In addition to this, for some functions (e.g. `EngineWriteTensor`, `EngineConnectStream`, `EngineReadTensor`) we provide more user-friendly methods where the last argument can be an `Array`, without having to pass additional arguments for pointers or array size.
Furthermore, the custom functions `Poplar.get_ipu_device` and `Poplar.get_ipu_devices` can be used to access one more IPU devices, as shown in the example above.
Read their docstrings for further details.
