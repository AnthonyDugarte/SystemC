#ifndef OR_GATE
#define OR_GATE

#include "gate.hpp"

namespace helpers
{
  bool or_helper(const bool& A, const bool& B)
  {
    return A | B;
  }
}

template<int N>
class or_gate : public gate<N, helpers::or_helper>
{
public:
  or_gate(const sc_module_name& nm) : gate<N, helpers::or_helper>(nm)
  {
    //empty
  }
};

#endif
