#ifndef ARITHMETIC_LOGIC_UNIT_HPP
#define ARITHMETIC_LOGIC_UNIT_HPP

class arithmetic_logic_unit : public sc_module
{
public:
  sc_in<Data> a_in,
                            b_in,
                            offset;
  sc_in<Reg> operation;

  sc_out<Data> output;

  arithmetic_logic_unit(const sc_module_name & nm)
    : sc_module(nm)
  {
    SC_METHOD(op);
    sensitive << a_in << b_in << offset << operation;
  }
private:
  SC_HAS_PROCESS(arithmetic_logic_unit);

  void op()
  {
    switch(operation.read().to_uint())
    {
      case STORE:
      case LOAD:
      case JEZ:
      case JMP:
        output.write(a_in.read().to_uint() + offset.read().to_uint());
        break;

      case LOAD_I:
        output.write(a_in.read().to_int() + offset.read().to_int());
        break;

      case ADD:
      case ADD_I:
        output.write(a_in.read().to_int() + b_in.read().to_int() + offset.read().to_int());
        break;

        case MUL:
          output.write(a_in.read().to_int() * (b_in.read().to_int() + offset.read().to_int()));
          break;

        case MUL_I:
          output.write(b_in.read().to_int() * (a_in.read().to_int() + offset.read().to_int()));
          break;

      case SUB:
        output.write(a_in.read().to_int() - (b_in.read().to_int() + offset.read().to_int()));
        break;

      case SUB_I:
        output.write(b_in.read().to_int() - (a_in.read().to_int() + offset.read().to_int()));
        break;

      default:
        output.write(0);
        break;
    }
  }
};
#endif
