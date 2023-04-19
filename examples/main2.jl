using IPUToolkit.IPUCompiler, IPUToolkit.Poplar
input = Float32[5, 2, 10, 102, -10, 2, 256, 15, 32, 100]
outvec1 = PoplarVec{Float32, Out}(undef, 10)
outvec2 = PoplarVec{Float32, Out}(undef, 10)
outvec3 = PoplarVec{Float32, Out}(undef, 10)
device = Poplar.get_ipu_device()
@ipuprogram device begin
    function TimesTwo(inconst::PoplarVec{Float32, In}, outvec::PoplarVec{Float32, Out})
        outvec .= 2 .* inconst
    end
    function Sort(invec::PoplarVec{Float32, In}, outvec::PoplarVec{Float32, Out})
        outvec .= invec
        sort!(outvec)
    end
    function Sin(invec::PoplarVec{Float32, In}, outvec::PoplarVec{Float32, Out})
        for idx in eachindex(outvec)
            @inbounds outvec[idx] = sin(invec[idx])
        end
    end
    TimesTwo(input, outvec1)
    Sort(outvec1, outvec2)
    Sin(outvec2, outvec3)
    # `print_tensor` is a special function which prints tensors to the host
    # using `Poplar.ProgramPrintTensor` under the hood.
    print_tensor("Input",    input)
    print_tensor("TimesTwo", outvec1)
    print_tensor("Sorted",   outvec2)
    print_tensor("Sin",      outvec3)
    # Copy IPU tensors to the host
    jl_outvec1 = outvec1
    jl_outvec2 = outvec2
    jl_outvec3 = outvec3
end
Poplar.DeviceDetach(device)
