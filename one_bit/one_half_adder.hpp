#ifndef ONE_HALF_ADDER_HPP
#define ONE_HALF_ADDER_HPP

#include "xor_gate.hpp"
#include "and_gate.hpp"
#include "or_gate.hpp"

//RECIBE DOS BITS PARA SER SUMADOS Y RETORNA SU RESULTADO Y ACARREO
class one_half_adder : public sc_module
{
public:
  sc_in<bool> b1_in;
  sc_in<bool> b2_in;

  sc_out<bool> b_out;//result
  sc_out<bool> c_out;//carry

  SC_CTOR(one_half_adder)
  {
    xor_gate1 = new xor_gate("xor_gate");
    and_gate1 = new and_gate("and_gate");

    xor_gate1->b1_in(b1_in);
    xor_gate1->b2_in(b2_in);
    xor_gate1->b1_out(b_out);

    and_gate1->b1_in(b1_in);
    and_gate1->b2_in(b2_in);
    and_gate1->b1_out(c_out);
  }

  ~one_half_adder()
  {
    delete xor_gate1;
    delete and_gate1;
  }
private:
  xor_gate* xor_gate1;
  and_gate* and_gate1;
};
#endif
