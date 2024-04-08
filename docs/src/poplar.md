# Interfacing the Poplar SDK

A quick example of use of the Poplar SDK functionalities, available in the `IPUToolkit.Poplar` submodule:

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

julia> Poplar.detach_devices()
```

A couple of basic examples of programs running on the IPU written using the interface to the Poplar SDK are available in the files [`examples/tutorial1.jl`](https://github.com/JuliaIPU/IPUToolkit.jl/blob/main/examples/tutorial1.jl) and [`examples/tutorial2.jl`](https://github.com/JuliaIPU/IPUToolkit.jl/blob/main/examples/tutorial2.jl).

We automatically generate the bindings of the Poplar SDK using [`Clang.jl`](https://github.com/JuliaInterop/Clang.jl) and [`CxxWrap.jl`](https://github.com/JuliaInterop/CxxWrap.jl).
There is not automatic documentation at the moment, but functions can be accessed from the `Poplar` submodule.
Also, the `IPUToolkit.Poplar` submodule wraps a subset of the functionalities available in the Poplar SDK, do not expect to be able to use all functionalities.
Remember that Julia does not use class-based object-oriented programming, class instances will usually be first arguments of the methods you want to use.

Function naming convention and signature is usually as follows:

* class name in [CamelCase](https://en.wikipedia.org/wiki/Camel_case), followed by method name also in CamelCase.  Note that first letter of method name is always uppercase in this naming convention, even if it is lowercase in the Poplar SDK.  For example, the method `getNumDevices` of the `DeviceManager` class can be accessed in the `Poplar` submodule with `Poplar.DeviceManagerGetNumDevices`;
* the first argument of the function is the class instance.  For example, to use the Julia function `Poplar.DeviceManagerGetNumDevices`, you need to pass as first argument an instance of `DeviceManager`;
* the following arguments are the same as in the method you want to use in the SDK.  For example, the method `getNumDevices` of the `DeviceManager` class doesn't take any argument, so the Julia function `Poplar.DeviceManagerGetNumDevices` will take an instance of `DeviceManager` as *only* argument.

## Convenient methods

In addition to this, for some functions (e.g. `EngineWriteTensor`, `EngineConnectStream`, `EngineReadTensor`) we provide more user-friendly methods where the last argument can be a Julia's `Array`, without having to pass additional arguments for pointers or array size.
Furthermore, the custom functions [`Poplar.get_ipu_device`](@ref) and [`Poplar.get_ipu_devices`](@ref) can be used to access one more IPU devices, as shown in the example above.

Another function for which we provide a convenient method is `Poplar.GraphAddConstant`:
```julia
Poplar.GraphAddConstant(graph, host_array)
```
adds the `host_array` (a plain standard Julia `Array` living on the host) to `graph`, automatically inferring from `host_array` the type and the shape of the tensor in the graph.
This works also with `host_array::Array{Float16}`.

You can slice a tensor with the usual Julia notation `tensor[index1:index2]`, this corresponds to a call to [`Tensor.slice(index1, index2+1)`](https://docs.graphcore.ai/projects/poplar-api/en/latest/poplar/graph/Tensor.html#_CPPv4NK6poplar6Tensor5sliceENSt6size_tENSt6size_tE).

[`similar`](@ref) can be used to add to `graph` a tensor with the same shape and optionally element type as `tensor`, while [`copyto!`](@ref) can be used to copy elements of a CPU host array into an IPU tensor.

## Using `IPUToolkit.jl` without an IPU

While this package requires a physical IPU to use all the available features, you can still experiment with the IPU programming model even if you do not have access to a hardware IPU.
The Poplar SDK provides a feature called IPU Model, which is a software emulation of the behaviour of the IPU hardware.
While the IPU model comes with [some limitations](https://docs.graphcore.ai/projects/poplar-user-guide/en/latest/poplar_programs.html#programming-with-poplar), it can be useful for testing or debugging.

To use the IPU model in `IPUToolkit.jl`, define the device of your IPU program with `Poplar.IPUModelCreateDevice` (which calls [`IPUModel::createDevice`](https://docs.graphcore.ai/projects/poplar-api/en/3.4.0/poplar/profiling/IPUModel.html#_CPPv4NK6poplar8IPUModel12createDeviceE11OptionFlagsbj) under the hood):
```julia
device = Poplar.get_ipu_model()
# Then the rest of the program continues as usual
target = Poplar.DeviceGetTarget(device)
graph = Poplar.Graph(target)
# ...
```

```@autodocs
Modules = [IPUToolkit.Poplar]
```
