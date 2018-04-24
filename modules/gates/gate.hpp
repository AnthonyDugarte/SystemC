#ifndef GATE_HPP
#define GATE_HPP

template<int N, bool (*cmp)(const bool& A, const bool& B)>
class gate : public sc_module
{
public:
  sc_vector<sc_in<bool>> input;
  sc_vector<sc_out<bool>> output;

  SC_HAS_PROCESS(gate);

  gate(const sc_module_name& nm) : sc_module(nm), input("input", N), output("output", 1)
  {
    SC_METHOD(operation);

    for(auto& it : input)
      sensitive << it;
  }

private:
  void operation()
  {
    bool out = input[0].read();

    for(int i{1}; i < N; ++i)
      out = cmp(out, input[i].read());

    output[0].write(out);
  }
};
#endif
