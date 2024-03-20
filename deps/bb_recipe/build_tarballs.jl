using BinaryBuilder
using Pkg

name = "libpoplar_wrapper"
version = v"1.0"

# `POPLAR_SDK_ENABLED` should point to where the Poplar SDK is installed,
# otherwise fallback to `/opt/poplar` (default dir in Graphcore Docker
# containers).
poplar_dir = get(ENV, "POPLAR_SDK_ENABLED", "/opt/poplar")

sources = [
    # The generated wrappers
    DirectorySource("../wrapper"),
    DirectorySource(dirname(poplar_dir)),
]

script = "POPLAR_DIR=$(basename(poplar_dir))\n" * raw"""
cd ${WORKSPACE}/srcdir/

mkdir -p "${libdir}"

c++ \
    -O0 \
    -std=c++17 \
    -fPIC \
    -shared \
    -I${POPLAR_DIR}/include \
    -I${includedir} \
    -I${includedir}/julia \
    -I. \
    -o "${libdir}/libpoplar_julia.${dlext}" \
    template.cpp \
    -L${POPLAR_DIR}/lib \
    -L${libdir} \
    -lpopops \
    -lpoplar \
    -lcxxwrap_julia \
    -ljulia

install_license /usr/share/licenses/MIT
"""

platforms = [
    Platform("x86_64", "linux"; libc="glibc", cxxstring_abi="cxx11", julia_version="1.10.0"),
]

products = [
    LibraryProduct("libpoplar_julia", :libpoplar_julia; dont_dlopen=true),
]

dependencies = [
    BuildDependency(PackageSpec(;name="libjulia_jll", version=v"1.10.9")),
    Dependency("libcxxwrap_julia_jll"; compat = "~0.11.2"),
]

build_tarballs(ARGS, name, version, sources, script, platforms, products, dependencies;
               julia_compat="1.9", preferred_gcc_version=v"10", dont_dlopen=true)
