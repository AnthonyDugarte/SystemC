/*Anthony Dugarte
  Falta verificar el complemento y la suma con complemento, están fallas
*/

#ifndef FULL_ADDER_HPP
#define FULL_ADDER_HPP

#include <one_full_adder.hpp>
#include <one_half_adder.hpp>

class half_adder : public sc_module
{
public:
  sc_in<bool> a4_in;
  sc_in<bool> b4_in;

  sc_in<bool> a3_in;
  sc_in<bool> b3_in;

  sc_in<bool> a2_in;
  sc_in<bool> b2_in;

  sc_in<bool> a1_in;
  sc_in<bool> b1_in;

  sc_out<bool> a4b4_out;
  sc_out<bool> a3b3_out;
  sc_out<bool> a2b2_out;
  sc_out<bool> a1b1_out;
  sc_out<bool> c_out;

  SC_CTOR(half_adder)
  {
    adder4 = new one_half_adder("adder4");
    adder3 = new one_full_adder("adder3");
    adder2 = new one_full_adder("adder2");
    adder1 = new one_full_adder("adder1");

    adder4->b1_in(a4_in);
    adder4->b2_in(b4_in);
    adder4->b_out(a4b4_out);
    adder4->c_out(sg3);

    adder3->b1_in(a3_in);
    adder3->b2_in(b3_in);
    adder3->c_in(sg3);
    adder3->b_out(a3b3_out);
    adder3->c_out(sg2);

    adder2->b1_in(a2_in);
    adder2->b2_in(b2_in);
    adder2->c_in(sg2);
    adder2->b_out(a2b2_out);
    adder2->c_out(sg1);

    adder1->b1_in(a1_in);
    adder1->b2_in(b1_in);
    adder1->c_in(sg1);
    adder1->b_out(a1b1_out);
    adder1->c_out(c_out);
  }
  ~half_adder()
  {
    delete adder1;
    delete adder2;
    delete adder3;
    delete adder4;
  }
private:
  one_full_adder* adder1;
  one_full_adder* adder2;
  one_full_adder* adder3;
  one_half_adder* adder4;

  sc_signal<bool> sg1, sg2, sg3;
};


class full_adder : public sc_module
{
public:
  sc_in<bool> c_in;

  sc_in<bool> a4_in;
  sc_in<bool> b4_in;

  sc_in<bool> a3_in;
  sc_in<bool> b3_in;

  sc_in<bool> a2_in;
  sc_in<bool> b2_in;

  sc_in<bool> a1_in;
  sc_in<bool> b1_in;


  sc_out<bool> a4b4_out;
  sc_out<bool> a3b3_out;
  sc_out<bool> a2b2_out;
  sc_out<bool> a1b1_out;
  sc_out<bool> c_out;

  SC_CTOR(full_adder)
  {
    adder4 = new one_full_adder("adder4");
    adder3 = new one_full_adder("adder3");
    adder2 = new one_full_adder("adder2");
    adder1 = new one_full_adder("adder1");

    adder4->b1_in(a4_in);
    adder4->b2_in(b4_in);
    adder4->b_out(a4b4_out);
    adder4->c_in(c_in);
    adder4->c_out(sg3);

    adder3->b1_in(a3_in);
    adder3->b2_in(b3_in);
    adder3->c_in(sg3);
    adder3->b_out(a3b3_out);
    adder3->c_out(sg2);

    adder2->b1_in(a2_in);
    adder2->b2_in(b2_in);
    adder2->c_in(sg2);
    adder2->b_out(a2b2_out);
    adder2->c_out(sg1);

    adder1->b1_in(a1_in);
    adder1->b2_in(b1_in);
    adder1->c_in(sg1);
    adder1->b_out(a1b1_out);
    adder1->c_out(c_out);
  }
  ~full_adder()
  {
    delete adder1;
    delete adder2;
    delete adder3;
    delete adder4;
  }
private:
  one_full_adder* adder1;
  one_full_adder* adder2;
  one_full_adder* adder3;
  one_full_adder* adder4;

  sc_signal<bool> sg1, sg2, sg3;
};

class complementer : public sc_module
{
public:
  sc_in<bool> b1_in, b2_in, b3_in, b4_in;
  sc_out<bool> b1_out, b2_out, b3_out, b4_out;

  SC_CTOR(complementer)
  {
    or_gate1 = new or_gate("or_gate1");
    xor_gate1 = new xor_gate("xor_gate1");
    xor_gate2 = new xor_gate("xor_gate2");
    xor_gate3 = new xor_gate("xor_gate3");
    xor_gate4 = new xor_gate("xor_gate4");
    adder1 = new full_adder("adder1");

    sc_sg_flag.write(0);

    or_gate1->b1_in(b1_in);
    or_gate1->b2_in(sc_sg_flag);
    or_gate1->b1_out(sc_sg1);

    xor_gate1->b2_in(sc_sg1);
    xor_gate2->b2_in(sc_sg1);
    xor_gate3->b2_in(sc_sg1);
    xor_gate4->b2_in(sc_sg1);


    xor_gate1->b1_in(b1_in);
    xor_gate1->b1_out(sc_sg_b1);

    xor_gate2->b1_in(b2_in);
    xor_gate2->b1_out(sc_sg_b2);

    xor_gate3->b1_in(b3_in);
    xor_gate3->b1_out(sc_sg_b3);

    xor_gate4->b1_in(b4_in);
    xor_gate4->b1_out(sc_sg_b4);


    adder1->c_in(sc_sg1);

    adder1->a1_in(sc_sg_b1);
    adder1->a2_in(sc_sg_b2);
    adder1->a3_in(sc_sg_b3);
    adder1->a4_in(sc_sg_b4);

    sc_sg2.write(0);
    sc_sg3.write(0);
    sc_sg4.write(0);
    sc_sg5.write(1);

    adder1->b1_in(sc_sg2);
    adder1->b2_in(sc_sg3);
    adder1->b3_in(sc_sg4);
    adder1->b4_in(sc_sg5);

    adder1->a1b1_out(b1_out);
    adder1->a2b2_out(b2_out);
    adder1->a3b3_out(b3_out);
    adder1->a4b4_out(b4_out);

    adder1->c_out(sc_sg6);
  }
  ~complementer()
  {
    delete or_gate1;
    delete xor_gate1;
    delete xor_gate2;
    delete xor_gate3;
    delete xor_gate4;
    delete adder1;
  }
private:
  or_gate* or_gate1;
  xor_gate* xor_gate1;
  xor_gate* xor_gate2;
  xor_gate* xor_gate3;
  xor_gate* xor_gate4;
  full_adder* adder1;

  sc_signal<bool> sc_sg_flag, sc_sg1, sc_sg2, sc_sg3, sc_sg4, sc_sg5, sc_sg6;
  sc_signal<bool> sc_sg_b1, sc_sg_b2, sc_sg_b3, sc_sg_b4;
};


class adder_w_comp : public sc_module
{
public:
  sc_in<bool> a1_in, a2_in, a3_in, a4_in,
              b1_in, b2_in, b3_in, b4_in;

  sc_out<bool>a1b1_out, a2b2_out, a3b3_out, a4b4_out;
  sc_out<bool> c_out;

  SC_CTOR(adder_w_comp)
  {
    adder1 = new half_adder("adder1");
    comp1 = new complementer("comp1");


    comp1->b1_in(b1_in);
    comp1->b2_in(b2_in);
    comp1->b3_in(b3_in);
    comp1->b4_in(b4_in);

    comp1->b1_out(sc_sg1);
    comp1->b2_out(sc_sg2);
    comp1->b3_out(sc_sg3);
    comp1->b4_out(sc_sg4);


    adder1->a1_in(a1_in);
    adder1->a2_in(a2_in);
    adder1->a3_in(a3_in);
    adder1->a4_in(a4_in);

    adder1->b1_in(sc_sg1);
    adder1->b2_in(sc_sg2);
    adder1->b3_in(sc_sg3);
    adder1->b4_in(sc_sg4);

    adder1->a1b1_out(a1b1_out);
    adder1->a2b2_out(a2b2_out);
    adder1->a3b3_out(a3b3_out);
    adder1->a4b4_out(a4b4_out);

    adder1->c_out(c_out);
  }
private:
  half_adder* adder1;
  complementer* comp1;

  sc_signal<bool> sc_sg1, sc_sg2, sc_sg3, sc_sg4;
};

#endif
