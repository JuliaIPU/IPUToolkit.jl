# Formatted Output.  Adapted from
# <https://github.com/JuliaGPU/CUDA.jl/blob/8ffdf3723ed6224ee7e2c7188ef6ab8d5a498905/src/device/intrinsics/output.jl>.

using LLVM
using LLVM.Interop
using Core: LLVMPtr

export @ipuprintf

"""
    $(@__MODULE__).DISABLE_PRINT::$(typeof(DISABLE_PRINT))

Global constant which controls whether printing through the various `@ipuprint*`
macros should be disabled or not.  You may want to completely disable printing
for production runs, to avoid the cost of printing on the device, but keep it
enabled during development.

Examples:

```julia
$(@__MODULE__).DISABLE_PRINT[] = false # Do not disable printing, this is the default.
$(@__MODULE__).DISABLE_PRINT[] = true  # Disable printing, the `@ipuprint*` macros are no-op.
```
"""
const DISABLE_PRINT = Ref(false)

@generated function promote_c_argument(arg)
    # > When a function with a variable-length argument list is called, the variable
    # > arguments are passed using C's old ``default argument promotions.'' These say that
    # > types char and short int are automatically promoted to int, and type float is
    # > automatically promoted to double. Therefore, varargs functions will never receive
    # > arguments of type char, short int, or float.

    if arg == Cchar || arg == Cshort || arg == Cuchar || arg == Cushort
        return :(Cint(arg))
    elseif arg == Cfloat
        return :(Cdouble(arg))
    else
        return :(arg)
    end
end

"""
    @ipuprintf("%Fmt", args...)

Print a formatted string in device context on the host standard output.

Note that this is not a fully C-compliant `printf` implementation.

Also beware that it is an untyped, and unforgiving `printf` implementation. Type widths need
to match, eg. printing a 64-bit Julia integer requires the `%ld` formatting string.

Printing can be completely disabled by setting
```julia
$(@__MODULE__).DISABLE_PRINT[] = true
```
"""
macro ipuprintf(fmt::String, args...)
    if DISABLE_PRINT[]
        return :()
    end

    fmt_val = Val(Symbol(fmt))

    return :(_ipuprintf($fmt_val, $(map(arg -> :(promote_c_argument($arg)), esc.(args))...)))
end

# Single argument calls can use `puts`, which has a simpler signature.
@generated function _ipuprintf(::Val{fmt}) where {fmt}
    @dispose ctx=Context() begin

        T_void = LLVM.VoidType(ctx)
        T_int32 = LLVM.Int32Type(ctx)
        T_pint8 = LLVM.PointerType(LLVM.Int8Type(ctx))

        # create functions
        llvm_f, llvm_ft = create_function(T_int32, LLVMType[])
        mod = LLVM.parent(llvm_f)

        # generate IR
        @dispose builder=IRBuilder(ctx) begin
            entry = BasicBlock(llvm_f, "entry"; ctx)
            position!(builder, entry)

            str = globalstring_ptr!(builder, String(fmt))

            # invoke puts and return
            puts_typ = LLVM.FunctionType(T_int32, [T_pint8])
            puts = LLVM.Function(mod, "puts", puts_typ)
            chars = call!(builder, puts_typ, puts, [str])

            ret!(builder, chars)
        end

        call_function(llvm_f, Int32, Tuple{})
    end
end

@generated function _ipuprintf(::Val{fmt}, argspec1, argspec...) where {fmt}
    @dispose ctx=Context() begin
        arg_exprs = vcat(:( argspec1 ), [:( argspec[$i] ) for i in 1:length(argspec)])
        arg_types = [argspec1, argspec...]

        T_void = LLVM.VoidType(ctx)
        T_int32 = LLVM.Int32Type(ctx)
        T_pint8 = LLVM.PointerType(LLVM.Int8Type(ctx))

        # create functions
        param_types = LLVMType[convert(LLVMType, typ; ctx) for typ in arg_types]
        llvm_f, llvm_ft = create_function(T_int32, param_types)
        mod = LLVM.parent(llvm_f)

        # generate IR
        @dispose builder=IRBuilder(ctx) begin
            entry = BasicBlock(llvm_f, "entry"; ctx)
            position!(builder, entry)

            str = globalstring_ptr!(builder, String(fmt))

            # invoke printf and return
            printf_typ = LLVM.FunctionType(T_int32, [T_pint8]; vararg=true)
            printf = LLVM.Function(mod, "printf", printf_typ)
            chars = call!(builder, printf_typ, printf, [str, parameters(llvm_f)...])

            ret!(builder, chars)
        end

        call_function(llvm_f, Int32, Tuple{arg_types...}, arg_exprs...)
    end
end

## print-like functionality

export @ipuprint, @ipuprintln

# simple conversions, defining an expression and the resulting argument type. nothing fancy,
# `@ipuprint` pretty directly maps to `@ipuprintf`; we should just support `write(::IO)`.
const ipuprint_conversions = Dict(
    Float32         => (x->:(Float64($x)),                  Float64),
    Ptr{<:Any}      => (x->:(convert(Ptr{Cvoid}, $x)),      Ptr{Cvoid}),
    LLVMPtr{<:Any}  => (x->:(reinterpret(Ptr{Cvoid}, $x)),  Ptr{Cvoid}),
    Bool            => (x->:(Int32($x)),                    Int32),
)

# format specifiers
const ipuprint_specifiers = Dict(
    # integers
    Int16       => "%hd",
    Int32       => "%d",
    Int64       => Sys.iswindows() ? "%lld" : "%ld",
    UInt16      => "%hu",
    UInt32      => "%u",
    UInt64      => Sys.iswindows() ? "%llu" : "%lu",

    # floating-point
    Float64     => "%f",

    # other
    Cchar       => "%c",
    Ptr{Cvoid}  => "%p",
    Cstring     => "%s",
)

@inline @generated function _ipuprint(parts...)
    fmt = ""
    args = Expr[]

    for i in 1:length(parts)
        part = :(parts[$i])
        T = parts[i]

        # put literals directly in the format string
        if T <: Val
            fmt *= string(T.parameters[1])
            continue
        end

        # try to convert arguments if they are not supported directly
        if !haskey(ipuprint_specifiers, T)
            for Tmatch in keys(ipuprint_conversions)
                if T <: Tmatch
                    conv, T = ipuprint_conversions[Tmatch]
                    part = conv(part)
                    break
                end
            end
        end

        # render the argument
        if haskey(ipuprint_specifiers, T)
            fmt *= ipuprint_specifiers[T]
            push!(args, part)
        elseif T <: Tuple
            fmt *= "("
            for (j, U) in enumerate(T.parameters)
                if haskey(ipuprint_specifiers, U)
                    fmt *= ipuprint_specifiers[U]
                    push!(args, :($part[$j]))
                    if j < length(T.parameters)
                        fmt *= ", "
                    elseif length(T.parameters) == 1
                        fmt *= ","
                    end
                else
                    @error("@ipuprint does not support values of type $U")
                end
            end
            fmt *= ")"
        elseif T <: String
            @error("@ipuprint does not support non-literal strings")
        else
            @error("@ipuprint does not support values of type $T")
        end
    end

    quote
        $(@__MODULE__).@ipuprintf($fmt, $(args...))
    end
end

"""
    @ipuprint(xs...)
    @ipuprintln(xs...)

Print a textual representation of values `xs` to standard output from the IPU. The
functionality builds on `@ipuprintf`, and is intended as a more use friendly alternative of
that API. However, that also means there's only limited support for argument types, handling
16/32/64 signed and unsigned integers, 32 and 64-bit floating point numbers, `Cchar`s and
pointers. For more complex output, use `@ipuprintf` directly.

Limited string interpolation is also possible:

```julia
    @ipuprint("Hello, World ", 42, "\\n")
    @ipuprint "Hello, World \$(42)\\n"
```

Printing can be completely disabled by setting
```julia
$(@__MODULE__).DISABLE_PRINT[] = true
```
"""
macro ipuprint(parts...)
    if DISABLE_PRINT[]
        return :()
    end

    args = Union{Val,Expr,Symbol}[]

    parts = [parts...]
    while true
        isempty(parts) && break

        part = popfirst!(parts)

        # handle string interpolation
        if isa(part, Expr) && part.head == :string
            parts = vcat(part.args, parts)
            continue
        end

        # expose literals to the generator by using Val types
        if isbits(part) # literal numbers, etc
            push!(args, Val(part))
        elseif isa(part, QuoteNode) # literal symbols
            push!(args, Val(part.value))
        elseif isa(part, String) # literal strings need to be interned
            push!(args, Val(Symbol(part)))
        else # actual values that will be passed to printf
            push!(args, part)
        end
    end

    quote
        _ipuprint($(map(esc, args)...))
    end
end

@doc (@doc @ipuprint) ->
macro ipuprintln(parts...)
    esc(quote
            $(@__MODULE__).@ipuprint($(parts...), "\n")
    end)
end

export @ipushow

"""
    @ipushow(ex)

IPU analog of `Base.@show`. It comes with the same type restrictions as [`@ipuprintf`](@ref).

```julia
@ipushow x
```

Printing can be completely disabled by setting
```julia
$(@__MODULE__).DISABLE_PRINT[] = true
```
"""
macro ipushow(exs...)
    if DISABLE_PRINT[]
        return :()
    end

    blk = Expr(:block)
    for ex in exs
        push!(blk.args, :(@ipuprintln($(sprint(Base.show_unquoted,ex)*" = "),
                                      begin local value = $(esc(ex)) end)))
    end
    isempty(exs) || push!(blk.args, :value)
    blk
end
