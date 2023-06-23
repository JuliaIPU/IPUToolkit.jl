using Test
using CxxWrap

# We often want to check that some CxxWrap objects are not NULL.
macro cxxtest(ex)
    return quote
        local out = $(esc(ex))
        Test.@test out.cpp_object != C_NULL
        out
    end
end

# https://giordano.github.io/blog/2019-05-03-julia-get-pointer-value/
dereference(T::DataType, ptr::Ptr) = unsafe_load(Ptr{T}(ptr))
dereference(T::DataType, ptr::CxxRef) = dereference(T, ptr.cpp_object)
dereference(T::DataType, ptr::Poplar.Type_Allocated) = dereference(T, ptr.cpp_object)

# Do we have access to hardware IPU? If not, we have to skip tests which don't
# work on IPU model.
const USE_HARDWARE_IPU = get(ENV, "GITHUB_ACTIONS", "false") != "true"
