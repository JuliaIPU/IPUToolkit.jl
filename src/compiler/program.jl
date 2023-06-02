function _get_name_args(expr::Expr)
    name = expr.args[1].args[1]
    args = [(arg.args[1], arg.args[2].args[2], arg.args[2].args[3]) for arg in expr.args[1].args[2:end]]
    return name, args
end

function _add_vertex!(initialised_tensors::Dict{Symbol, Symbol}, graph, prog, name_args::Dict, expr::Expr)
    # NOTE: this dictionary can't be `const` because the Poplar types like
    # `FLOAT()` have to be evaluated at runtime.
    jl_type_to_poplar_type = Dict(
        :Float32 => Poplar.FLOAT(),
    )

    name = expr.args[1]
    f_args = name_args[name]
    compute_set = string(name, "_compute_set")
    compute_set_sym = gensym(compute_set)
    vertex = gensym(Symbol(name, "_vertex"))
    out = quote end
    add_vertex = :( $(esc(@__MODULE__().add_vertex))($(esc(graph)), $(esc(prog)), $(esc(name))) )
    if length(expr.args) > 1
        for (idx, arg) in enumerate(expr.args[2:end])
            arg_info = f_args[idx]
            vec = gensym(arg_info[1])
            if arg ∉ keys(initialised_tensors)
                append!(out.args,
                        (quote
                             if $(esc(arg)) isa PoplarArray
                                 $(esc(vec)) = $(esc(Poplar.GraphAddVariable))($(esc(graph)), $(esc(jl_type_to_poplar_type[arg_info[2]])), collect(UInt64.(size($(esc(arg))))), $(string(arg)))
                             elseif $(esc(arg)) isa Array
                                 $(esc(vec)) = $(esc(Poplar.GraphAddConstant))($(esc(graph)), $(esc(jl_type_to_poplar_type[arg_info[2]])), collect(UInt64.(size($(esc(arg))))), $(esc(arg)))
                             else
                                 error("`$(string(arg))` is a `$(typeof(esc(arg)))`, it must be either an `Array` or a `PoplarArray`")
                             end
                         end).args)
                initialised_tensors[arg] = vec
            end
            push!(add_vertex.args, esc(initialised_tensors[arg]))
        end
    end
    push!(out.args, add_vertex)
    return out
end

function _print_tensor(prog::Symbol, initialised_tensors::Dict{Symbol, Symbol}, expr::Expr)
    (length(expr.args) == 3 && expr.args[2] isa String && expr.args[3] isa Symbol) || error("""
        The `print_tensor` function must have as first argument a `String` and second argument the tensor name:
            print_tensor("Description", tensor_name)
        """)
    return quote
        $(esc(Poplar.ProgramSequenceAdd))($(esc(prog)), $(esc(Poplar.ProgramPrintTensor))($(expr.args[2]), $(esc(initialised_tensors[expr.args[3]]))))
    end
end

function _read_tensor(engine::Symbol, graph::Symbol, initialised_tensors::Dict{Symbol,Symbol}, expr::Expr)
    (length(expr.args) == 2 && expr.args[1] isa Symbol && expr.args[2] isa Symbol) || error("""
        Assignment can only be done between two variable names:
            jl_var = ipu_tensor
        where `jl_var` is a newly created Julia variable on the host, and `ipu_tensor` is the name of a tensor on the IPU.
        """)
    jl_var = expr.args[1]
    ipu_tensor = expr.args[2]
    read_name = string(ipu_tensor, "_read")
    return (:($(esc(Poplar.GraphCreateHostRead))($(esc(graph)), $(read_name), $(esc(initialised_tensors[ipu_tensor])))),
            quote
                $(esc(jl_var)) = $(esc(_similar))($(esc(ipu_tensor)))
                $(esc(Poplar.EngineReadTensor))($(esc(engine)), $(read_name), $(esc(jl_var)))
            end)
end

macro ipuprogram(device, program::Expr)
    program.head === :block || error("The second argument to the `@ipuprogram` macro must be a begin-end block")
    graph = gensym("graph")
    prog = gensym("prog")
    engine = gensym("engine")
    out = quote
        $(esc(graph)) = $(esc(Poplar.Graph))($(esc(Poplar.DeviceGetTarget))($(esc(device))))
        $(esc(prog)) = $(esc(Poplar.ProgramSequence))()
    end
    postamble = quote end
    name_args = Dict{Symbol,Any}()
    initialised_tensors = Dict{Symbol,Symbol}()
    for expr in program.args
        expr isa LineNumberNode && continue
        if expr.head ∈ (:function, :(=)) && (expr.args[1] isa Expr && expr.args[1].head === :call)
            append!(out.args, _codelet(graph, expr).args)
            na = _get_name_args(expr)
            name_args[na[1]] = na[2]
        elseif expr.head === :call
            if expr.args[1] === :print_tensor
                append!(out.args, _print_tensor(prog, initialised_tensors, expr).args)
            else
                append!(out.args, _add_vertex!(initialised_tensors, graph, prog, name_args, expr).args)
            end
        elseif expr.head == :(=)
            o, p = _read_tensor(engine, graph, initialised_tensors, expr)
            push!(out.args, o)
            append!(postamble.args, p.args)
        end
    end
    flags = gensym("flags")
    append!(out.args,
            (quote
                 $(esc(flags)) = Poplar.OptionFlags()
                 $(esc(Poplar.OptionFlagsSet))($(esc(flags)), "debug.instrument", "true")
                 $(esc(engine)) = $(esc(Poplar.Engine))($(esc(graph)), $(esc(prog)), $(esc(flags)))
                 $(esc(Poplar.EngineLoadAndRun))($(esc(engine)), $(esc(device)))
             end).args)
    append!(out.args, postamble.args)
    return out
end
