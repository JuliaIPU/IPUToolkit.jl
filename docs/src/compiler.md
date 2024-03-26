# Writing codelets in Julia

The `IPUToolkit.IPUCompiler` submodule allows you to write [codelets](https://docs.graphcore.ai/projects/poplar-user-guide/en/3.2.0/vertices_overview.html) for the IPU in Julia.
Codelets are defined with the [`@codelet`](@ref) macro, and then you can use them inside a program, written using the interface to the Poplar SDK described before.
This mechanism uses the [`GPUCompiler.jl`](https://github.com/JuliaGPU/GPUCompiler.jl) package, which is a generic framework for generating LLVM IR code for specialised targets, not limited to GPUs despite the historical name.

Examples of codelets written in Julia are shown in the files [`examples/main.jl`](https://github.com/JuliaIPU/IPUToolkit.jl/blob/main/examples/main.jl), [`examples/pi.jl`](https://github.com/JuliaIPU/IPUToolkit.jl/blob/main/examples/pi.jl), [`examples/adam.jl`](https://github.com/JuliaIPU/IPUToolkit.jl/blob/main/examples/adam.jl), [`examples/diffeq.jl`](https://github.com/JuliaIPU/IPUToolkit.jl/blob/main/examples/diffeq.jl).

The code inside a codelet has the same limitations as all the compilation models based on [`GPUCompiler.jl`](https://github.com/JuliaGPU/GPUCompiler.jl):

* the code has to be statically inferred and compiled, dynamic dispatch is not admitted;
* you cannot use functionalities which require the Julia runtime, most notably the garbage collector;
* you cannot call into any other external binary library at runtime, for example you cannot call into a BLAS library.

After defining a codelet with `@codelet` you can add a vertex calling this codelet to the graph with the function [`add_vertex`](@ref), which also allows controlling the tile mapping in a basic way, or `Poplar.GraphAddVertex`.

```@docs
@codelet
VertexVector
VertexScalar
add_vertex
IPUCompiler.TARGET_COLOSSUS
IPUCompiler.KEEP_LLVM_FILES
IPUCompiler.POPC_FLAGS
IPUCompiler.PROGRESS_SPINNER
```

## IPU builtins

Inside codelets defined with [`@codelet`](@ref) all calls to random functions

* `rand(Float16)`
* `rand(Float32)`
* `rand(UInt32)`
* `rand(UInt64)`
* `randn(Float16)`
* `randn(Float32)`

result to call to corresponding IPU builtins for [random number generation](https://docs.graphcore.ai/projects/poplar-api/en/latest/ipu_intrinsics/ipu_builtins.html#random-number-generation).
The uniformly distributed numbers follow the general semantic of the Julia function `rand` (floating point numbers are uniformely distributed in the $[0, 1)$ range), while the normally distributed numbers have the properties described in the Poplar SDK documentation (numbers are in the range $[-93/16, 93/16]$).

!!! note

    The IPU builtins for random numbers return pairs of numbers, but the Julia functions `randn(Float16)` and `randn(Float32)` return only a single number, discarding the second number of the pair.
    If you have a vector of even length that you want to fill in-place with normally distributed numbers, you can use the [`randn2!`](@ref) function to do that efficiently, without discarding any number.

Additionally, you can use the [IPU builtins](https://docs.graphcore.ai/projects/poplar-api/en/latest/ipu_intrinsics/ipu_builtins.html) listed below.

```@docs
get_scount_l
get_tile_id
randn2!
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

    Note also that the `Poplar.TargetGetTileClockFrequency(target)` function [may not return a reliable value](https://github.com/UoB-HPC/ipu-hpc-cookbook/blob/96a37c2f7c745fb4e1ca0bc12fa68fe39df067a7/timing-program-execution/README.md#using-counters-on-the-ipu), but this is an upstream bug (this has been observed at least up to Poplar SDK v3.0).
    You may have to use tools like `gc-monitor`, `gc-inventory`, or `gc-info --device-id <N> --tile-clock-speed` to obtain the correct tile clock frequency.

```@docs
@ipucycles
@ipushowcycles
@ipuelapsed
```

## Passing non-constant variables from global scope

If your kernel references a non-constant (`const`) global variable, the generated code will result in a reference to a memory address on the host, and this will fatally fail at runtime because programs running on the IPU don't have access to the host memory.
Constant variables are not affected by this problem because their values are inlined when the function is compiled.
If you can't or don't want to make a variable constant you can interpolate its value with a top-level [`@eval`](https://docs.julialang.org/en/v1/base/base/#Base.@eval) when defining the codelet.
For example:

```julia
using IPUToolkit.IPUCompiler, IPUToolkit.Poplar
device = Poplar.get_ipu_device()
target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)
tile_clock_frequency = Poplar.TargetGetTileClockFrequency(target)
@eval @codelet graph function test(invec::VertexVector{Float32, In}, outvec::VertexVector{Float32, Out})
    # We can use the intrinsic `get_scount_l` to get the cycle counter right
    # before and after some operations, so that we can benchmark it.
    cycles_start = get_scount_l()
    # Do some operations here...
    cycles_end = get_scount_l()
    # Divide the difference between the two cycle counts by the tile frequency
    # clock to get the time.
    time = (cycles_end - cycles_start) / $(tile_clock_frequency)
    # Show the time spent doing your operations
    @ipushow time
end
```

The use of `@eval` allows you not to have to pass an extra argument to your kernel just to use the value of the variable inside the codelet.

## Debugging compilation errors in codelets

Writing codelets for the IPU takes some practice, because you cannot use any arbitrary construct or package as you would normally do when running code on a CPU.
As mentioned above, codelets have to be statically compiled with `GPUCompiler.jl`, with all the limitations of this framework, which can only use a subset of the Julia language.
Therefore, it happens frequently that you run into compilation errors while developing a codelet function, and you have then to resolve the issues, which usually involves removing [dynamic dispatch](https://en.wikipedia.org/wiki/Dynamic_dispatch) calls (which would require the JIT compiler at runtime), resolving [type-instabilities](https://docs.julialang.org/en/v1/manual/performance-tips/#Write-%22type-stable%22-functions), [avoiding memory allocations](https://docs.julialang.org/en/v1/manual/performance-tips/#Measure-performance-with-[@time](@ref)-and-pay-attention-to-memory-allocation), etc...
If you have [`Cthulhu.jl`](https://github.com/JuliaDebug/Cthulhu.jl) installed, you can set [`IPUCompiler.DEBUG_COMPILATION_ERRORS`](@ref) to `true` to automatically open an interactive shell when compiling a codelet results into invalid LLVM IR, to more easily debug the codelet code.

We suggest again taking a look at the code samples in the [`examples/`](https://github.com/JuliaIPU/IPUToolkit.jl/tree/main/examples) directory for learning how to write working IPU codelets in Julia.

```@docs
IPUCompiler.DEBUG_COMPILATION_ERRORS
```

## Domain-Specific Language: `@ipuprogram`

The `IPUCompiler.@ipuprogram` macro provides a very simple and limited DSL to automatically generate most of the boilerplate code needed when writing an IPU program.
You can do *very* little with this DSL, which is mainly a showcase of Julia's meta-programming capabilities.
A fully commented examples of use of the `@ipuprogram` macro is available in the [`examples/dsl.jl`](https://github.com/JuliaIPU/IPUToolkit.jl/blob/main/examples/dsl.jl) file.
