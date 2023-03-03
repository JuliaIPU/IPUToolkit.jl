extern "C" {
#include <stdint.h>
extern void KERNEL_NAME();
struct PoplarVector {
  uint32_t beginPtr;
  uint32_t size_;
};
static PoplarVector* vertclass;

uint32_t GET_VEC_NAME(uint32_t i, uint32_t type) {
  if(type == 0) 
    return vertclass[i].beginPtr;
  return vertclass[i].size_;
}

}

#include <poplar/Vertex.hpp>
#include <poplar/StackSizeDefs.hpp>

#ifdef DEF_STACK_USAGE
static_assert(sizeof(void*) == 4);

DEF_STACK_USAGE(0x1000, KERNEL_NAME);
DEF_STACK_USAGE(0x1000, GET_VEC_NAME);
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
  #include"gen_codelet.txt"

  // Compute function
  bool compute() {
    vertclass = (PoplarVector*) &FIRST_NAME;
  
    KERNEL_NAME();
    return true;
  }
};
