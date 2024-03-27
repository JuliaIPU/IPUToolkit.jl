template<size_t ndims>
struct VertexVector {
    uint64_t beginPtr;
    uint32_t  size_[ndims];
    constexpr size_t numDims() { return ndims; }
};




extern "C" {
#include <stdint.h>
    extern void KERNEL_NAME();
    struct VertexVector {
        uint64_t beginPtr;
        uint64_t  numDims;
        uint32_t  size_[0];
    };
    static VertexVector* vertclass;

/*
struct VertexVector* construct(void* baseptr, std::vector<uint64_t> dims) {
    VertexVector* vert = (struct VertexVector)malloc(sizeof(VertexVector) + dims.size() * sizeof(uint32_t));
    alloca(...) // stack allocation
    vert->beginPtr = baseptr;
    vert->numDims = dims.size();
    for (size_t i=0; i<dims.size(); i++)
      vert->size_[i] = dims[i];
    return vert;
}
*/

    // Function to get the pointer to the i-th vector.
    uintptr_t GET_VEC_PTR_NAME(int32_t i) {
        return vertclass[i].beginPtr;
    }

    // Function to get the size of the i-th vector.
    uint32_t GET_VEC_SIZE_NAME(int32_t i) {
        return vertclass[i].size_;
    }
}

#include <poplar/Vertex.hpp>
#include <poplar/StackSizeDefs.hpp>
#include <poplar/HalfFloat.hpp>

#ifdef DEF_STACK_USAGE
static_assert(sizeof(void*) == 4);

DEF_STACK_USAGE(0x2000, KERNEL_NAME);
DEF_STACK_USAGE(0x1000, GET_VEC_PTR_NAME);
DEF_STACK_USAGE(0x1000, GET_VEC_SIZE_NAME);
#endif

class CLASS_NAME : public poplar::Vertex {
public:
/*
struct VectorBase {
  void *beginPtr;
  std::uint32_t size_;
  void *begin() const { return beginPtr; }
  std::uint32_t size() const { return size_; }
};
*/

  // Fields
  //poplar::InOut<poplar::Vector<int>> out;
#include "gen_codelet.cpp"

  // Compute function
    bool compute() {
        vertclass = (VertexVector*) &FIRST_NAME;

        KERNEL_NAME();
        return true;
    }
};
