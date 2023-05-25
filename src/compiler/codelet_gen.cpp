extern "C" {
#include <stdint.h>
    extern void KERNEL_NAME();
    struct VertexVector {
        uintptr_t beginPtr;
        uint32_t  size_;
    };
    static VertexVector* vertclass;

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
