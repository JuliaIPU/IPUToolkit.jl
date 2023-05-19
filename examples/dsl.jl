using IPUToolkit.IPUCompiler, IPUToolkit.Poplar

# Define the arrays that will be used during the program.  `input` is a host array that will
# be automatically copied to an IPU array, the other `PoplarVector`s are placeholders for
# IPU arrays that will be populated during the execution of the program.
input = Float32[5, 2, 10, 102, -10, 2, 256, 15, 32, 100]
outvec1 = PoplarVector{Float32, Out}(undef, 10)
outvec2 = PoplarVector{Float32, Out}(undef, 10)
outvec3 = PoplarVector{Float32, Out}(undef, 10)

# Get the device.
device = Poplar.get_ipu_device()

# Inside `@ipuprogram` you can do only the following things:
#
# * define functions, which will be used as codelets in the IPU program
# * call these functions, which will automatically build the graph of the calls for you
# * print tensors on the IPU with the "special" function `print_tensor`
# * copy IPU tensors to the host
@ipuprogram device begin
    # Define the functions/codelets.  All arguments must be `PoplarVector`s.
    function TimesTwo(inconst::PoplarVector{Float32, In}, outvec::PoplarVector{Float32, Out})
        outvec .= 2 .* inconst
    end
    function Sort(invec::PoplarVector{Float32, In}, outvec::PoplarVector{Float32, Out})
        outvec .= invec
        sort!(outvec)
    end
    function Sin(invec::PoplarVector{Float32, In}, outvec::PoplarVector{Float32, Out})
        for idx in eachindex(outvec)
            @inbounds outvec[idx] = sin(invec[idx])
        end
    end

    # Run the functions.  Arguments must be the arrays defined above, either host arrays
    # (which will be copied to the IPU automatically) or `PoplarVector`s.
    TimesTwo(input, outvec1)
    Sort(outvec1, outvec2)
    Sin(outvec2, outvec3)

    # `print_tensor` is a special function which prints tensors to the host
    # using `Poplar.ProgramPrintTensor` under the hood.  Syntax is
    #     print_tensor(<LABEL>, <tensor variable>)
    print_tensor("Input",    input)
    print_tensor("TimesTwo", outvec1)
    print_tensor("Sorted",   outvec2)
    print_tensor("Sin",      outvec3)

    # Copy IPU tensors to the host.  The right-hand side must be one of the tensors defined
    # above, the left-hand side is the name of a host array which will be created
    # automatically for you, so you will be able to reference them after the `@ipuprogram`.
    jl_outvec1 = outvec1
    jl_outvec2 = outvec2
    jl_outvec3 = outvec3
end

# Detach the device when we're done.
Poplar.DeviceDetach(device)
