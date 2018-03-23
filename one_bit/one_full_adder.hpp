#ifndef ONE_FULL_ADDER_HPP
#define ONE_FULL_ADDER_HPP

#include "and_gate.hpp"
#include "or_gate.hpp"
#include "xor_gate.hpp"

class one_full_adder : public sc_module
{
public:
  sc_in<bool> b1_in;
  sc_in<bool> b2_in;

  sc_in<bool> c_in;

  sc_out<bool> b_out;
  sc_out<bool> c_out;

  SC_CTOR(one_full_adder)
  {
    xor_gate_bits_result = new xor_gate("xor_gate_bits_result");
    xor_gate_return = new xor_gate("xor_gate_return");

    and_gate_b1b2 = new and_gate("and_gate_b1b2");
    and_gate_cibo = new and_gate("and_gate_cibo");

    or_gate1 = new or_gate("or_gate");

    //resultado suma de bits
    xor_gate_bits_result->b1_in(b1_in);
    xor_gate_bits_result->b2_in(b2_in);
    xor_gate_bits_result->b1_out(sg1);

    //resutado suma de resultado de bits y acarreo
    xor_gate_return->b1_in(sg1);
    xor_gate_return->b2_in(c_in);
    xor_gate_return->b1_out(b_out);

    //resultado and de los bits
    and_gate_b1b2->b1_in(b1_in);
    and_gate_b1b2->b2_in(b2_in);
    and_gate_b1b2->b1_out(sg2);

    //resultado and del acarreo entrante y el resultado de la suma
    and_gate_cibo->b1_in(c_in);
    and_gate_cibo->b2_in(sg1);
    and_gate_cibo->b1_out(sg3);

    //resultado del acarreo saliente por parte las dos penúltimas compuertas
    or_gate1->b1_in(sg2);
    or_gate1->b2_in(sg3);
    or_gate1->b1_out(c_out);
  }
  ~one_full_adder()
  {
    delete xor_gate_bits_result;
    delete xor_gate_return;
    delete and_gate_b1b2;
    delete and_gate_cibo;
    delete or_gate1;
  }
private:
  xor_gate* xor_gate_bits_result;
  xor_gate* xor_gate_return;

  and_gate* and_gate_b1b2;
  and_gate* and_gate_cibo;

  or_gate* or_gate1;

  sc_signal<bool> sg1, sg2, sg3;
};
#endif
