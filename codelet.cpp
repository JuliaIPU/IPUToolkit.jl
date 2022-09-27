extern "C" {
#include <stdint.h>
//extern void KERNEL_NAME();
struct PoplarVector {
  void *beginPtr;
  uint32_t size_;
};
void* vec1;
struct PoplarVector getVec() {
    return *(PoplarVector*)vec1;
}
}

#include <poplar/Vertex.hpp>
#include <poplar/StackSizeDefs.hpp>


#ifdef DEF_STACK_USAGE
DEF_STACK_USAGE(0x1000, KERNEL_NAME);
#endif

class JuliaVertex : public poplar::Vertex {
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
  poplar::Output<poplar::Vector<float>> out;

  // Compute function
  bool compute() {
    int j = 2;
    for (int i = 0; i < 10; i++) {
      out[i] = j;
      j*=2;
    }
    return true;
  }
};
