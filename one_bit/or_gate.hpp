#ifndef OR_GATE_HPP
#define OR_GATE_HPP

#include <systemc.h>

class or_gate : public sc_module
{
public:
  sc_in<bool> b1_in;
  sc_in<bool> b2_in;
  sc_out<bool> b1_out;

  SC_CTOR(or_gate)
  {
    SC_METHOD(operation);
    sensitive << b1_in << b2_in;
  }
private:
  void operation()
  {
    b1_out.write(b1_in.read() or b2_in.read());
  }
};
#endif
