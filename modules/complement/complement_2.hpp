#ifndef COMPLEMENT_2_HPP
#define COMPLEMENT_2_HPP

#include "complement_1.hpp"
#include "half_adder1b.hpp"

template<int N>
class complement_2 : public sc_module
{
public:
  sc_vector<sc_in<bool>> input;
  sc_vector<sc_out<bool>> output;
  sc_in<bool> flag;

  complement_2(const sc_module_name& nm) : sc_module(nm), input("input", N), output("output", N),
    comp_1st("comp_1st"), comp_1st_res("comp_1st_res", N), adders("adders", N), carries("carries", N)
  {
    comp_1st.input(input);
    comp_1st.output(comp_1st_res);
    comp_1st.flag(flag);

    adders[0].a_in(comp_1st_res[0]);
    adders[0].b_in(flag);
    adders[0].output(output[0]);
    adders[0].carry_output(carries[0]);

    for(size_t it{1}; it < N; ++it)
    {
      adders[it].a_in(comp_1st_res[it]);
      adders[it].b_in(carries[it - 1]);
      adders[it].output(output[it]);
      adders[it].carry_output(carries[it]);
    }
  }
private:
  complement_1<N> comp_1st;
  sc_vector<half_adder1b> adders;

  sc_vector<sc_signal<bool>> comp_1st_res;
  sc_vector<sc_signal<bool>> carries;
};
#endif
