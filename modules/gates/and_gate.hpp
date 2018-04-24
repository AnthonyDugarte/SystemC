#ifndef AND_GATE
#define AND_GATE

#include "gate.hpp"

namespace helpers
{
  bool and_helper(const bool& A, const bool& B)
  {
    return A & B;
  }
}

template<int N>
class and_gate : public gate<N, helpers::and_helper>
{
public:
  and_gate(const sc_module_name& nm) : gate<N, helpers::and_helper>(nm)
  {
    //empty
  }
};

#endif
