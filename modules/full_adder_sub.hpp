#ifndef FULL_ADDER_SUB_HPP
#define FULL_ADDER_SUB_HPP

#include "half_adder_sub.hpp"
#include "xor_gate.hpp"
#include "mutex.hpp"

template<int N>
class full_adder_sub : public sc_module
{
public:
  sc_vector<sc_in<bool>> a_in;
  sc_vector<sc_in<bool>> b_in;
  sc_in<bool> S_R;

  sc_vector<sc_out<bool>> output;
  sc_out<bool> sign_rem;

  full_adder_sub(const sc_module_name& nm) : sc_module(nm), a_in("a_in", N), b_in("b_in", N),
    S_R("S_R"), sign_rem("sign_rem"), output("output", N), adder("adder"), carry("carry"),
    remainder("remainder"), xor_ctrl("xor_ctrl"), ctrl("ctrl")
  {
    adder.a_in(a_in);
    adder.b_in(b_in);
    adder.S_R(S_R);
    adder.output(output);
    adder.carry_output(carry);

    xor_ctrl.input[0](a_in[N - 1]);
    xor_ctrl.input[1](b_in[N - 1]);
    xor_ctrl.input[2](S_R);
    xor_ctrl.output[0](ctrl);

    remainder.input[0](carry);
    remainder.input[1](output[N - 1]);
    remainder.ctrl_input[0](ctrl);
    remainder.output(sign_rem);
  }
private:
  half_adder_sub<N> adder;
  xor_gate<3> xor_ctrl;
  mutex<1, bool> remainder;

  sc_signal<bool> carry, ctrl;
};
#endif
