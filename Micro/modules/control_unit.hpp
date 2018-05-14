#ifndef CONTROL_UNIT_HPP
#define CONTROL_UNIT_HPP

class control_unit : public sc_module
{
public:
  //pipe2 input
  sc_in<Reg> result_rgDestInput;
  sc_in<Reg> result_operationInput;
  sc_in<Data> result_input;

  //alu input
  sc_in<Data> alu_input;
  sc_in<Reg> alu_rgDestInput;
  sc_in<Reg> alu_operationInput;

  //dataMemory input
  sc_in<Data> dataMemory_input;

  //pc
  sc_out<bool> pc_readInput;

  //generalRegister
  sc_out<Data> generalRegister_input;
  sc_out<bool> generalRegister_readInput;
  sc_out<Reg> generalRegister_addressInput;

  //dataMemory
  sc_out<bool> dataMemory_readInput;

  control_unit(const sc_module_name & nm)
    : sc_module(nm), PC_flag(4)
  {
    SC_METHOD(write);
    sensitive << result_rgDestInput << result_operationInput
                       << alu_input << alu_rgDestInput << alu_operationInput << result_input;
  }
private:
  SC_HAS_PROCESS(control_unit);

  int PC_flag;
  bool JEZ_flag;

  void write()
  {
    switch(alu_operationInput.read().to_uint())
    {
      case LOAD_I:
      case ADD: case ADD_I:
      case MUL: case MUL_I:
      case SUB: case SUB_I:
        generalRegister_input.write(alu_input.read());
        generalRegister_addressInput.write(alu_rgDestInput.read());
        generalRegister_readInput.write(true);
        break;

      case JEZ:
        if(PC_flag == 4)
        {
          JEZ_flag = result_input.read().to_int() == 0 ? true : false;
          PC_flag = 0;
        }
        break;

      case JMP:
      if(PC_flag == 4)
      {
        JEZ_flag = true;
        PC_flag = 0;
      }
      break;
    }

    switch(result_operationInput.read().to_uint())
    {
      case STORE:
        generalRegister_readInput.write(false);
        dataMemory_readInput.write(true);
        break;

      case JEZ:
      case JMP:
        if(PC_flag == 0)
        {
          ++PC_flag;
          break;
        }
        ++PC_flag;
        pc_readInput.write(JEZ_flag);
        break;

      case LOAD:
        generalRegister_input.write(dataMemory_input.read());
        generalRegister_addressInput.write(result_rgDestInput.read());
        dataMemory_readInput.write(false);
        generalRegister_readInput.write(true);
        break;

        case LOAD_I:
        case ADD:
        case ADD_I:
        case MUL:
        case MUL_I:
        case SUB:
        case SUB_I:
          dataMemory_readInput.write(false);
          generalRegister_readInput.write(true);
        break;

      default:
        dataMemory_readInput.write(false);
        generalRegister_readInput.write(false);
        break;
    }

    if(PC_flag == 2)
      ++PC_flag;
    else if(PC_flag == 3)
    {
      ++PC_flag;
      pc_readInput.write(false);
    }
  }
};
#endif
