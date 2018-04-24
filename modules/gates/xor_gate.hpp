#ifndef XOR_GATE
#define XOR_GATE

#include "gate.hpp"

namespace helpers
{
  bool xor_helper(const bool& A, const bool& B)
  {
    return A ^ B;
  }
}

template<int N>
class xor_gate : public gate<N, helpers::xor_helper>
{
public:
  xor_gate(const sc_module_name& nm) : gate<N, helpers::xor_helper>(nm)
  {
    //empty
  }
};

#endif
