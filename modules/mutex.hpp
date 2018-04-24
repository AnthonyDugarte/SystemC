#ifndef MUTEX_HPP
#define MUTEX_HPP

#include "not_gate.hpp"
#include "and_gate.hpp"

template<int N, typename data>
class mutex : public sc_module
{
public:
  sc_vector<sc_in<bool>> ctrl_input;
  sc_vector<sc_in<data>> input;

  sc_out<data> output;

  SC_HAS_PROCESS(mutex);

  mutex(const sc_module_name& nm) : sc_module(nm), ctrl_input("ctrl_input", N), input("input", 1 << N),
    output("output")
  {
    SC_METHOD(operation);
    for(auto& it : ctrl_input)
      sensitive << it;
    for(auto& it : input)
      sensitive << it;
  }
private:
  void operation()
  {
    for(size_t it{0}; it < N; ++it)
      pos[it] = ctrl_input[it].read();
    output.write(input[pos.to_int()].read());
  }

  sc_bv<N + 1> pos;

  sc_signal<data> out_flag;
};
#endif
