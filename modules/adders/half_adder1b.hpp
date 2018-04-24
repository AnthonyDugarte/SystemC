#ifndef HALF_ADDER1B_HPP
#define HALF_ADDER1B_HPP

#include "xor_gate.hpp"
#include "and_gate.hpp"

class half_adder1b : public sc_module
{
public:
  sc_in<bool> a_in;
  sc_in<bool> b_in;

  sc_out<bool> output;
  sc_out<bool> carry_output;

  half_adder1b(const sc_module_name& nm) : sc_module(nm),
    xor_sum_result("xor_sum_result"), and_carry_result("and_carry_result")
  {
    xor_sum_result.input[0](a_in);
    xor_sum_result.input[1](b_in);
    xor_sum_result.output[0](output);

    and_carry_result.input[0](a_in);
    and_carry_result.input[1](b_in);
    and_carry_result.output[0](carry_output);
  }
private:
  xor_gate<2> xor_sum_result;
  and_gate<2> and_carry_result;
};
#endif
