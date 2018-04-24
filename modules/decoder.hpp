#ifndef DECODER_HPP
#define DECODER_HPP

#include <not_gate.hpp>
#include <and_gate.hpp>

template<int N>
class decoder : public sc_module
{
public:
  sc_vector<sc_in<bool>> input;
  sc_vector<sc_out<bool>> output;

  decoder(const sc_module_name& nm) : sc_module(nm), input("input", N), output("output", 1 << N),
    outs("outs", 1 << N), input_neg("input_neg", N), not_gate_input("not_gate_input")
  {
    not_gate_input.input(input);
    not_gate_input.output(input_neg);

    size_t connections = 1 << N;

    for(size_t it{0}; it < connections; ++it)
    {
      for(size_t i{0}; i < N; ++i)
        if((1 << i) & it)
          outs[it].input[i](input[i]);
        else outs[it].input[i](input_neg[i]);

      outs[it].output[0](output[it]);
    }
  }
private:
  not_gate<N> not_gate_input;
  sc_vector<and_gate<N>> outs;

  sc_vector<sc_signal<bool>> input_neg;

};
#endif
