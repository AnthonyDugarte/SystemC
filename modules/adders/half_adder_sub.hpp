#ifndef HALF_ADDER_SUB_HPP
#define HALF_ADDER_SUB_HPP

#include "complement_1.hpp"
#include "full_adder.hpp"

template<int N>
class half_adder_sub : public sc_module
{
public:
  sc_vector<sc_in<bool>> a_in;
  sc_vector<sc_in<bool>> b_in;
  sc_in<bool> S_R;

  sc_vector<sc_out<bool>> output;
  sc_out<bool> carry_output;

  half_adder_sub(const sc_module_name& nm) : sc_module(nm), a_in("a_in", N), b_in("b_in", N),
    output("output", N), complement("complement"), adder("adder"), b_comp("b_comp", N)
  {
    complement.input(b_in);
    complement.flag(S_R);
    complement.output(b_comp);

    adder.a_in(a_in);
    adder.b_in(b_comp);
    adder.carry_in(S_R);
    adder.output(output);
    adder.carry_output(carry_output);
  }
private:
  complement_1<N> complement;
  full_adder<N> adder;

  sc_vector<sc_signal<bool>> b_comp;
};
#endif
