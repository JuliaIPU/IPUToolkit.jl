# IPUToolkit.jl

This package allows you to interface the [Intelligence Processing Unit (IPU) by Graphcore](https://www.graphcore.ai/products/ipu) using the [Julia programming language](https://julialang.org/).

***Disclaimer**: at the moment this is package is in a proof-of-concept stage, not suited for production usage.*

## Requirements

This package requires Julia v1.6+ (currently tested up to Julia v1.9), GCC 10+ as compiler (it requires support for the C++20 standard), and the Poplar SDK v1.3, or v2.0-v2.5.
Other versions of the Poplar SDK are not currently supported.

Note that both Julia and the Poplar SDK are coupled to a specific version of the LLVM compiler framework, and you will need to match a specific version of the Poplar SDK with a version of Julia using the same major version of LLVM.
For example, the Poplar SDK v2.2 uses LLVM 13, which is available in Julia v1.8, while the Poplar SDK versions 2.3-2.5 use LLVM 14, which is available in Julia v1.9.

## Installation

To install the package, run the commands

```julia
using Pkg
Pkg.add(; url="https://github.com/giordano/julia-ipu")
```

and then build the package with

```julia
Pkg.build()
```

This step will compile a wrapper around the Poplar SDK that can be used by Julia.
It will take a while, without printing an update to screen, hold on.

## Usage

The package is called IPUToolkit because it provides different tools to interface the IPU from Julia:

* you can use functionalities in the [Poplar SDK](https://www.graphcore.ai/products/poplar);
* you can use Julia's code generation capabilities to automatically compile native code that can be run on the IPU;
* small [embedded Domain-Specific Language](https://en.wikipedia.org/wiki/Domain-specific_language) (eDSL) to automatically generate the code of a program.

These approaches are exploratory of the functionalities, and are often limited in scope.

### Interface to Poplar SDK

A taster of use of the Poplar SDK functionalities, available in the `IPUToolkit.Poplar` submodule:

```julia
julia> using IPUToolkit.Poplar

julia> dm = Poplar.DeviceManager();

julia> Int(Poplar.DeviceManagerGetNumDevices(dm))
129

julia> device = Poplar.get_ipu_device();
[ Info: Trying to attach to device 0...
[ Info: Successfully attached to device 0

julia> Int(Poplar.DeviceGetId(device))
0

julia> Poplar.DeviceDetach(device)
```

A couple of complete basic examples of programs running on the IPU written using the interface to the Poplar SDK are available in the files [`examples/tutorial1.jl`](./examples/tutorial1.jl) and [`examples/tutorial2.jl`](./examples/tutorial2.jl).

We automatically generate the bindings of the Poplar SDK using [`Clang.jl`](https://github.com/JuliaInterop/Clang.jl) and [`CxxWrap.jl`](https://github.com/JuliaInterop/CxxWrap.jl).
There is not automatic documentation at the moment, but functions can be accessed from the `Poplar` submodule.
Also, the `IPUToolkit.Poplar` submodule wraps a subset of the functionalities available in the Poplar SDK, do not expect to be able to use all functionalities.
Remember that Julia does not use class-based object-oriented programming, class instances will usually be first arguments of the methods you want to use.

Function naming convention and signature is usually as follows:

* class name in [CamelCase](https://en.wikipedia.org/wiki/Camel_case), followed by method name also in CamelCase.  Note that first letter of method name is always uppercase in this naming convention, even if it is lowercase in the Poplar SDK.  For example, the method `getNumDevices` of the `DeviceManager` class can be accessed in the `Poplar` submodule with `Poplar.DeviceManagerGetNumDevices`;
* the first argument of the function is the class instance.  For example, to use the Julia function `Poplar.DeviceManagerGetNumDevices`, you need to pass as first argument an instance of `DeviceManager`;
* the following arguments are the same as in the method you want to use in the SDK.  For example, the method `getNumDevices` of the `DeviceManager` class doesn't take any argument, so the Julia function `Poplar.DeviceManagerGetNumDevices` will take an instance of `DeviceManager` as *only* argument.

#### Convenient methods for some functions

In addition to this, for some functions (e.g. `EngineWriteTensor`, `EngineConnectStream`, `EngineReadTensor`) we provide more user-friendly methods where the last argument can be a Julia's `Array`, without having to pass additional arguments for pointers or array size.
Furthermore, the custom functions `Poplar.get_ipu_device` and `Poplar.get_ipu_devices` can be used to access one more IPU devices, as shown in the example above.
Read their docstrings for further details.

Another function for which we provide a convenient method is `Poplar.GraphAddConstant`:
```julia
Poplar.GraphAddConstant(graph, host_array)
```
adds the `host_array` (a plain standard Julia `Array` living on the host) to `graph`, automatically inferring from `host_array` the type and the shape of the tensor in the graph.

You can slice a tensor with the usual Julia notation `tensor[index1:index2]`, this corresponds to a call to [`Tensor.slice(index1, index2+1)`](https://docs.graphcore.ai/projects/poplar-api/en/latest/poplar/graph/Tensor.html#_CPPv4NK6poplar6Tensor5sliceENSt6size_tENSt6size_tE).

### Writing codelets in Julia

You can write [codelets](https://docs.graphcore.ai/projects/poplar-user-guide/en/3.2.0/vertices_overview.html) for the IPU in Julia with the `IPUCompiler.@codelet` macro, and use them inside a program, written using the interface to the Poplar SDK described above.
This mechanism uses the [`GPUCompiler.jl`](https://github.com/JuliaGPU/GPUCompiler.jl) package, which is a generic framework for generating LLVM IR code for specialised targets, not limited to GPUs despite the historical name.
The `IPUCompiler.@codelet` macro takes two arguments:

* the graph to which to add the codelet with the `Poplar.GraphAddCodelets` function
* the function definition of the kernel you want to compile for the device.

The arguments of a codelet function have to be `VertexVector{T,S}`, a subtype of `AbstractVector{T}` which represents a [vertex vector](https://docs.graphcore.ai/projects/poplar-user-guide/en/3.2.0/vertex_vectors.html), passed as argument to a codelet.
The parameters of `VertexVector{T,S}` are

* `T`: the type of the elements of the vector;
* `S`: the scope of the vector in the codelet, `In`, `Out`, or `InOut`.

Examples of codelets written in Julia are shown in the files [`examples/main.jl`](./examples/main.jl), [`examples/adam.jl`](./examples/adam.jl), and [`examples/pi.jl`](./examples/pi.jl).

The code inside a codelet has the same limitations as all the compilation models based on [`GPUCompiler.jl`](https://github.com/JuliaGPU/GPUCompiler.jl):

* the code has to be statically inferred and compiled, dynamic dispatch is not admitted;
* you cannot use functionalities which require the Julia runtime, most notably the garbage collector;
* you cannot call into any other external binary library at runtime, for example you cannot call into a BLAS library.

After defining a codelet with `@codelet` you can add a vertex calling this codelet to the graph with the function `add_vertex`, which also allows controlling the tile mapping in a basic way.
Read its docstring for more details.

During compilation of codelets a spinner is displayed to show the progress, as this step can take a few seconds for each codelet to be generated.
This can be disabled with
```julia
IPUCompiler.PROGRESS_SPINNER[] = false
```

Inside codelets you can print text and value of variables using the macros `@ipuprintf`, `@ipuprint`, `@ipuprintln`, and `@ipushow`, read their docstrings for more details.
These macros are useful for debugging purposes but printing inside a codelet might incur performance penalty.
To completely disable all printing and make these macros no-op you can set
```julia
IPUCompiler.DISABLE_PRINT[] = true
```

To benchmark expressions inside codelets you can use the macros `@ipucycles`, `@ipushowcycles`, and `@ipuelapsed`, which report the number of cycles spent in the wrapped expression.
They are similar to Julia's `@time`, `@showtime`, and `@elapsed` macros, but report the number of cycles, as the clockspeed of tiles cannot be easily obtained _inside_ a codelet.
The corresponding time can be obtained by dividing the number of cycles by the clock frequency of the the tile, which you can get with `Poplar.TargetGetTileClockFrequency(target)` outside of the codelet, and should usually be 1.330 GHz or 1.850 GHz depending on the model of your IPU.
The printing macros `@ipucycles` and `@ipushowcycles` can be made completely no-op by setting `IPUCompiler.DISABLE_PRINT[] = true`.
***NOTE***: timing of expressions taking longer than `typemax(UInt32) / tile_clock_frequency` (about 2 or 3 seconds depending on your IPU model) is unreliable because the difference between the starting and the ending cycle counts would overflow.

Other options related to codelet generation are:

* `IPUCompiler.KEEP_LLVM_FILES`: it controls whether to keep the files with the LLVM IR of the codelets;
* `IPUCompiler.POPC_FLAGS`: flags to pass to the `popc` compiler.

### Domain-Specific Language: `@ipuprogram`

The `IPUCompiler.@ipuprogram` macro provides a very simple and limited DSL to automatically generate most of the boilerplate code needed when writing an IPU program.
You can do *very* little with this DSL, which is mainly a showcase of Julia's meta-programming capabilities.
A fully commented examples of use of the `@ipuprogram` macro is available in the [`examples/dsl.jl`](./examples/dsl.jl) file.
