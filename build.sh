#!/bin/bash
set -euxo pipefail
set -x

# todo: makefile
g++-10 -O0 -std=c++20 -fPIC -shared -I`readlink -f ../libcxxwrap-julia/include`\
    -I/home/lukb/opt/julia-1.6.6/include/julia  -o libpoc.so  template.cpp -lpoplar -lpopops
