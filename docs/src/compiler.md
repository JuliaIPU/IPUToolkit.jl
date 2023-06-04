# Writing codelets in Julia

The `IPUToolkit.IPUCompiler` submodule allows you to write [codelets](https://docs.graphcore.ai/projects/poplar-user-guide/en/3.2.0/vertices_overview.html) for the IPU in Julia.
Codelets are defined with the `IPUCompiler.@codelet` macro, and then you can use them inside a program, written using the interface to the Poplar SDK described before.
This mechanism uses the [`GPUCompiler.jl`](https://github.com/JuliaGPU/GPUCompiler.jl) package, which is a generic framework for generating LLVM IR code for specialised targets, not limited to GPUs despite the historical name.
The `IPUCompiler.@codelet` macro takes two arguments:

* the graph to which to add the codelet with the `Poplar.GraphAddCodelets` function
* the function definition of the kernel you want to compile for the device.

The arguments of a codelet function have to be `VertexVector{T,S}`, a subtype of `AbstractVector{T}` which represents a [vertex vector](https://docs.graphcore.ai/projects/poplar-user-guide/en/3.2.0/vertex_vectors.html), passed as argument to a codelet.
The parameters of `VertexVector{T,S}` are

* `T`: the type of the elements of the vector;
* `S`: the scope of the vector in the codelet, `In`, `Out`, or `InOut`.

Examples of codelets written in Julia are shown in the files [`examples/main.jl`](https://github.com/giordano/IPUToolkit.jl/blob/main/examples/main.jl), [`examples/adam.jl`](https://github.com/giordano/IPUToolkit.jl/blob/main/examples/adam.jl), and [`examples/pi.jl`](https://github.com/giordano/IPUToolkit.jl/blob/main/examples/pi.jl).

The code inside a codelet has the same limitations as all the compilation models based on [`GPUCompiler.jl`](https://github.com/JuliaGPU/GPUCompiler.jl):

* the code has to be statically inferred and compiled, dynamic dispatch is not admitted;
* you cannot use functionalities which require the Julia runtime, most notably the garbage collector;
* you cannot call into any other external binary library at runtime, for example you cannot call into a BLAS library.

After defining a codelet with `@codelet` you can add a vertex calling this codelet to the graph with the function `add_vertex`, which also allows controlling the tile mapping in a basic way.
Read its docstring for more details.

During compilation of codelets a spinner is displayed to show the progress, as this step can take a few seconds for each codelet to be generated.
This can be disabled by setting [`IPUCompiler.PROGRESS_SPINNER`](@ref):
```julia
IPUCompiler.PROGRESS_SPINNER[] = false
```

```@docs
add_vertex
IPUCompiler.PROGRESS_SPINNER
```

## Printing

Inside codelets you can print text and value of variables using the macros [`@ipuprintf`](@ref), [`@ipuprint`](@ref), [`@ipuprintln`](@ref), and [`@ipushow`](@ref).
These macros are useful for debugging purposes but printing inside a codelet might incur performance penalty.
To completely disable all printing and make these macros no-op you can set [`IPUCompiler.DISABLE_PRINT`](@ref):
```julia
IPUCompiler.DISABLE_PRINT[] = true
```

```@docs
@ipuprintf
@ipuprint
@ipuprintln
@ipushow
IPUCompiler.DISABLE_PRINT
```

## Benchmarking

To benchmark expressions inside codelets you can use the macros [`@ipucycles`](@ref), [`@ipushowcycles`](@ref), and [`@ipuelapsed`](@ref), which report the number of cycles spent in the wrapped expression.
They are similar to Julia's `@time`, `@showtime`, and `@elapsed` macros, but report the number of cycles, as the clockspeed of tiles cannot be easily obtained _inside_ a codelet.
The corresponding time can be obtained by dividing the number of cycles by the clock frequency of the the tile, which you can get with [`Poplar.TargetGetTileClockFrequency(target)`](https://docs.graphcore.ai/projects/poplar-api/en/latest/poplar/device/Target.html#_CPPv4NK6poplar6Target21getTileClockFrequencyEv) outside of the codelet, and should usually be 1.330 GHz or 1.850 GHz depending on the model of your IPU.
The printing macros `@ipucycles` and `@ipushowcycles` can be made completely no-op by setting [`IPUCompiler.DISABLE_PRINT`](@ref).

!!! warning

    Timing of expressions taking longer than `typemax(UInt32) / tile_clock_frequency` (about 2 or 3 seconds depending on your IPU model) is unreliable because the difference between the starting and the ending cycle counts would overflow.

```@docs
@ipucycles
@ipushowcycles
@ipuelapsed
```

## Other options

Other options related to codelet generation are:

```@docs
IPUCompiler.KEEP_LLVM_FILES
IPUCompiler.POPC_FLAGS
```

## Domain-Specific Language: `@ipuprogram`

The `IPUCompiler.@ipuprogram` macro provides a very simple and limited DSL to automatically generate most of the boilerplate code needed when writing an IPU program.
You can do *very* little with this DSL, which is mainly a showcase of Julia's meta-programming capabilities.
A fully commented examples of use of the `@ipuprogram` macro is available in the [`examples/dsl.jl`](https://github.com/giordano/IPUToolkit.jl/blob/main/examples/dsl.jl) file.
