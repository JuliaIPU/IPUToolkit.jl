using CxxWrap
using Libdl

@wrapmodule(joinpath(pwd(), "test.so"))

function __init__()
    @initcxx
end