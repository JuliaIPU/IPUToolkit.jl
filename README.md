# IPUToolkit.jl

[![](https://img.shields.io/badge/docs-stable-blue.svg)](https://juliaipu.github.io/IPUToolkit.jl/stable)
[![](https://img.shields.io/badge/docs-dev-blue.svg)](https://juliaipu.github.io/IPUToolkit.jl/dev)
[![Tests and docs](https://github.com/JuliaIPU/IPUToolkit.jl/actions/workflows/ci.yml/badge.svg?branch=main&event=push)](https://github.com/JuliaIPU/IPUToolkit.jl/actions/workflows/ci.yml)

This package allows you to interface the [Intelligence Processing Unit (IPU) by Graphcore](https://www.graphcore.ai/products/ipu) using the [Julia programming language](https://julialang.org/).

***Disclaimer**: at the moment this is package is in a proof-of-concept stage, not suitable for production usage.*

## Usage and documentation

The package is called `IPUToolkit` because it provides different tools to interface the IPU from Julia:

* you can use functionalities in the [Poplar SDK](https://www.graphcore.ai/products/poplar);
* you can use Julia's code generation capabilities to automatically compile native code that can be run on the IPU;
* there is a small [embedded Domain-Specific Language](https://en.wikipedia.org/wiki/Domain-specific_language) (eDSL) to automatically generate the code of a program.

These approaches are exploratory of the functionalities, and are often limited in scope and are described in more details in the [documentation](https://juliaipu.github.io/IPUToolkit.jl/).
For examples of usage of this package, see the [`examples/`](https://github.com/JuliaIPU/IPUToolkit.jl/tree/main/examples) directory of the official repository.

## Talks and demos

Here is some material that you may find useful for learning more about Julia on the IPU and trying it out yourself:

* [Pluto notebook](https://giordano.github.io/blog/2023-07-20-julia-ipu/) of presentation given at Graphcore and at JuliaCon in July 2023
* [JuliaIpuDemo](https://github.com/JuliaIPU/JuliaIpuDemo), repository with instructions for running some Jupyter notebooks on Paperspace cloud.
  This service offers also IPU time for free, these sessions are limited to 6 hours each and one at the time, but you can run as many as you want.
