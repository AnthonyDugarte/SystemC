#ifndef COMPLEMENT_1_HPP
#define COMPLEMENT_1_HPP

#include "xor_gate.hpp"

template<int N>
class complement_1: public sc_module
{
public:
  sc_vector<sc_in<bool>> input;
  sc_vector<sc_out<bool>> output;
  sc_in<bool> flag;

  complement_1(const sc_module_name& nm) : sc_module(nm), input("input", N), output("output", N),
    xor_1st("xor_1st", N)
  {
    for(size_t it{0}; it < N; ++it)
    {
      xor_1st[it].input[0](flag);
      xor_1st[it].input[1](input[it]);
      xor_1st[it].output[0](output[it]);
    }
  }
private:
  sc_vector<xor_gate<2>> xor_1st;
};
#endif
