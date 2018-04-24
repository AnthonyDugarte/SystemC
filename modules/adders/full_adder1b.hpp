#ifndef FULL_ADDER1B_HPP
#define FULL_ADDER1B_HPP

#include "xor_gate.hpp"
#include "and_gate.hpp"
#include "or_gate.hpp"

class full_adder1b : public sc_module
{
public:
  sc_in<bool> a_in;
  sc_in<bool> b_in;
  sc_in<bool> carry_in;

  sc_out<bool> output;
  sc_out<bool> carry_output;

  full_adder1b(const sc_module_name& nm) : sc_module(nm), ab_xor("ab_xor"), abc_xor("abc_xor"),
    ab_and("ab_and"), rc_and("rc_and"), ab_or_rc("ab_or_rc")
  {
    ab_xor.input[0](a_in);
    ab_xor.input[1](b_in);
    ab_xor.output[0](ab_xor_res);

    abc_xor.input[0](ab_xor_res);
    abc_xor.input[1](carry_in);
    abc_xor.output[0](output);

    ab_and.input[0](a_in);
    ab_and.input[1](b_in);
    ab_and.output[0](ab_and_res);
    rc_and.input[0](ab_xor_res);
    rc_and.input[1](carry_in);
    rc_and.output[0](rc_and_res);

    ab_or_rc.input[0](ab_and_res);
    ab_or_rc.input[1](rc_and_res);
    ab_or_rc.output[0](carry_output);
  }
private:
  xor_gate<2> ab_xor, abc_xor;
  and_gate<2> ab_and, rc_and;
  or_gate<2> ab_or_rc;

  sc_signal<bool> ab_xor_res, ab_and_res, rc_and_res;
};
#endif
