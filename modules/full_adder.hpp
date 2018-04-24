#ifndef FULL_ADDER_HPP
#define FULL_ADDER_HPP

#include "full_adder1b.hpp"

template<int N>
class full_adder : public sc_module
{
public:
  sc_vector<sc_in<bool>> a_in;
  sc_vector<sc_in<bool>> b_in;
  sc_in<bool> carry_in;

  sc_vector<sc_out<bool>> output;
  sc_out<bool> carry_output;

  full_adder(const sc_module_name& nm) : sc_module(nm), a_in("a_in", N), b_in("b_in", N),
    output("output", N), adders("adders", N), carries("carries", N - 1)
  {
    adders[0].a_in(a_in[0]);
    adders[0].b_in(b_in[0]);
    adders[0].carry_in(carry_in);
    adders[0].output(output[0]);
    adders[0].carry_output(carries[0]);

    for(size_t it{1}; it < N - 1; ++it)
    {
      adders[it].a_in(a_in[it]);
      adders[it].b_in(b_in[it]);
      adders[it].carry_in(carries[it - 1]);
      adders[it].output(output[it]);
      adders[it].carry_output(carries[it]);
    }
    adders[N - 1].a_in(a_in[N - 1]);
    adders[N - 1].b_in(b_in[N - 1]);
    adders[N - 1].carry_in(carries[N - 2]);
    adders[N - 1].output(output[N - 1]);
    adders[N - 1].carry_output(carry_output);
  }
private:
  sc_vector<full_adder1b> adders;

  sc_vector<sc_signal<bool>> carries;
};

#endif
