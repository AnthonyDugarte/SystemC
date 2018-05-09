#ifndef ARITHMETIC_LOGIC_UNIT_HPP
#define ARITHMETIC_LOGIC_UNIT_HPP

//for now it's just an adder-substractor, multiplier, that's all we need
template<int size, int n_ops = 2> //2^n_ops
class arithmetic_logic_unit : public sc_module
{
public:
  sc_in<sc_bv<size>> a_in;
  sc_in<sc_bv<size>> b_in;
  sc_in<sc_bv<n_ops>> operation;

  sc_out<sc_bv<size>> output;

  arithmetic_logic_unit(const sc_module_name & nm)
    : sc_module(nm)
  {
    SC_METHOD(op);
    sensitive << a_in << b_in << operation;
  }
private:
  enum ops{ ADDRESS = 0,  SUM = 1, SUB = 2, MUL = 3};

  SC_HAS_PROCESS(arithmetic_logic_unit);

  void op()
  {
    switch(operation.read().to_uint())
    {
      case ADDRESS:
        output.write(a_in.read().to_uint() + b_in.read().to_uint());
        break;

      default:
      case SUM:
        output.write(a_in.read().to_int() + b_in.read().to_int());
        break;

      case SUB:
        output.write(a_in.read().to_int() - b_in.read().to_int());
        break;

      case MUL:
        output.write(a_in.read().to_int() * b_in.read().to_int());
        break;
    }
  }
};
#endif
