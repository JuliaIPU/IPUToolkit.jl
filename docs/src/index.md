# IPUToolkit.jl

[`IPUToolkit.jl`](https://github.com/giordano/julia-ipu) allows you to interface the [Intelligence Processing Unit (IPU) by Graphcore](https://www.graphcore.ai/products/ipu) using the [Julia programming language](https://julialang.org/).

!!! warning "Disclaimer"

    This is package is currently a proof-of-concept, not suited for production usage.
	Its API is subject to frequent development and breaking changes.

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

!!! note

	This step will compile a wrapper around the Poplar SDK that can be used by Julia.
	It will take a while, without printing an update to screen.
	Hold on.

## Usage

The package is called IPUToolkit because it provides different tools to interface the IPU from Julia:

* you can use functionalities in the [Poplar SDK](https://www.graphcore.ai/products/poplar);
* you can use Julia's code generation capabilities to automatically compile native code that can be run on the IPU;
* there is a small [embedded Domain-Specific Language](https://en.wikipedia.org/wiki/Domain-specific_language) (eDSL) to automatically generate the code of a program.

These approaches are exploratory of the functionalities, and are often limited in scope and are described in more details in the following sections.
