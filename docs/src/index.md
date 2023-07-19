# IPUToolkit.jl

[`IPUToolkit.jl`](https://github.com/JuliaIPU/IPUToolkit.jl) allows you to interface the [Intelligence Processing Unit (IPU) by Graphcore](https://www.graphcore.ai/products/ipu) using the [Julia programming language](https://julialang.org/).

The main motivation for this project is to explore Julia's introspection and metaprogramming capabilities to write high-level code for the IPU using an alternative method to the tools developed by Graphcore, and leverage code-generation through LLVM to generate efficient code for the device: also the IPU compiler is based on this framework, so the LLVM IR constitutes a common language between Julia and the IPU compiler.

!!! warning "Disclaimer"

    This effort is not officially endorsed by Graphcore, although we gracefully received help through the public Graphcore support channels.
    This package is currently a proof-of-concept, not suitable for production usage.
	Its API may be subject to frequent development and breaking changes.

This package was initially created by Emily Dietrich and Luk Burchard, and later expanded by Mosè Giordano.
[Mosè](https://github.com/giordano)'s work on this package was funded by [UCL Centre for Advance Research Computing](https://www.ucl.ac.uk/advanced-research-computing).

## Requirements

This package requires

* Julia v1.6+ (currently tested up to Julia v1.10),
* the Poplar SDK v1.3 or v2.0-v3.2 including the `popc` compiler,
* a C++ compiler supporting C++17 standard for compiling the wrapper around the Poplar SDK (e.g. g++ 9 or following releases).

Other versions of the Poplar SDK are not currently supported.

!!! note "Compatibility between Julia and Poplar SDK"

    Both Julia and the Poplar SDK are coupled to a specific version of the LLVM compiler framework, and you will need to match a specific version of the Poplar SDK with a version of Julia using the same major version of LLVM.
    For example
    * the Poplar SDK version 2.2 uses LLVM 13, which is available in Julia v1.8;
    * the Poplar SDK versions 2.3-2.5 use LLVM 14, which is available in Julia v1.9;
    * the Poplar SDK versions 2.6-3.2 use LLVM 15, which is available in Julia v1.10;
    * the Poplar SDK version 3.3 use LLVM 16, which as of 2023-07-05 is not available in any Julia version.

## Installation

To install the package, run the commands

```julia
using Pkg
Pkg.add("IPUToolkit")
```

You will need to build the wrapper around the Poplar SDK.
This should happen automatically the first time you install the package, in any case you can run it with

```julia
Pkg.build()
```

This step requires a C++ compiler supporting C++17 standard.
You have to set the compiler with the `CXX` environment variable, this can be either its absolute path or simply its name if it is in the [`PATH`](https://en.wikipedia.org/wiki/PATH_(variable)) environment variable.
The compiler must be able to find Poplar header files automatically, depending on your installation of the Poplar SDK you may have to add its `include/` directory to the [`CPATH`](https://gcc.gnu.org/onlinedocs/cpp/Environment-Variables.html) environment variable, but this should be done automatically by the script to activate a Poplar SDK.

!!! note

	Compiling the wrapper around the Poplar SDK will take several minutes (up to about 7 minutes, depending on the Poplar version), without printing any progress to screen.
	Hold on.

## Usage

The package is called IPUToolkit because it provides different tools to interface the IPU from Julia:

* you can use functionalities in the [Poplar SDK](https://www.graphcore.ai/products/poplar);
* you can use Julia's code generation capabilities to automatically compile native code that can be run on the IPU;
* there is a small [embedded Domain-Specific Language](https://en.wikipedia.org/wiki/Domain-specific_language) (eDSL) to automatically generate the code of a program.

These approaches are exploratory of the functionalities, and are often limited in scope and are described in more details in the following sections.

## Talks and demos

Here is some material that you may find useful for learning more about Julia on the IPU and trying it out yourself:

* [Pluto notebook](https://giordano.github.io/blog/2023-07-20-julia-ipu/) of presentation given at Graphcore and at JuliaCon in July 2023
* [JuliaIpuDemo](https://github.com/JuliaIPU/JuliaIpuDemo), repository with instructions for running some Jupyter notebooks on Paperspace cloud.
  This service offers also IPU time for free, these sessions are limited to 6 hours each and one at the time, but you can run as many as you want.
