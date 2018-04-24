#ifndef NOT_GATE_HPP
#define NOT_GATE_HPP

template<int N>
class not_gate : public sc_module
{
public:
  sc_vector<sc_in<bool>> input;
  sc_vector<sc_out<bool>> output;

  SC_HAS_PROCESS(not_gate);

  not_gate(const sc_module_name& nm) : sc_module(nm), input("input", N), output("output", N)
  {
    SC_METHOD(operation);
    for(auto& it : input)
      sensitive << it;
  }

private:
  void operation()
  {
    for(int i{0}; i < N; ++i)
      output[i].write(! input[i].read());
  }
};
#endif
