#ifndef GENERAL_REGISTER_HPP
#define GENERAL_REGISTER_HPP

#include <fstream>
#include <vector>

class general_register : public sc_module
{
public:
  sc_in<bool> clk_in,
                           read_input;

  sc_in<Data> input;
  sc_in<Reg> address_input, //A.K.A regDest_address
                          rgA_address,
                          rgB_address,
                          rgDest_address,
                          operation;

  sc_out<Data> rgA,
                                rgB;

  general_register(const sc_module_name nm)
    : sc_module(nm), data(1 << Register_bits)
  {
    wire_up();
  }

  general_register(const sc_module_name& nm, std::ifstream & alt_input)
    : sc_module(nm), data(1 << Register_bits)
  {
    read_file(alt_input);
    wire_up();
  }
  general_register(const sc_module_name nm, std::ifstream && alt_input)
    : sc_module(nm), data(1 << Register_bits)
  {
    read_file(alt_input);
    wire_up();

    alt_input.close();
  }

  void saveData(std::ofstream & path, short unsigned option)
  {
    write_file(path, option);
  }

  void saveData(std::ofstream && path, short unsigned option)
  {
    write_file(path, option);
    path.close();
  }

private:
  std::vector<Data> data;

  SC_HAS_PROCESS(general_register);

  void wire_up()
  {
    SC_METHOD(write);
    sensitive << rgA_address << rgB_address << rgDest_address;

    SC_METHOD(read);
    sensitive << clk_in.neg();
  }

  void write()
  {
    read(); //?

    rgA.write(data[rgA_address.read().to_uint()]);

    switch (operation.read().to_uint())
    {
      case ADD_I:
      case MUL_I:
      case SUB_I:
      case STORE:
        rgB.write(data[rgDest_address.read().to_uint()]);
        break;

      default:
        rgB.write(data[rgB_address.read().to_uint()]);
        break;
    }
  }

  void read()
  {
    if(read_input.read())
      data[address_input.read().to_uint()] = input.read();
  }

  void read_file(std::ifstream & alt_input)
  {
    if(not alt_input.is_open())
     throw  std::runtime_error("cannot open memory field");

    std::string aux_data;

    size_t it{ 0 };

    if(std::is_base_of<sc_dt::sc_bv_base , std::decay_t<Data>>::value)
    {
      while(not alt_input.eof() and it < data.size()) //binary string input
      {
        std::getline(alt_input, aux_data);
        if(aux_data.size() == 0)
          break;
        data[it++] = aux_data.c_str();
      }
    }
    else while(not alt_input.eof() and it < data.size()) //integer assignment
    {
      std::getline(alt_input, aux_data);
      if(aux_data.size() == 0)
        break;
      data[it++] = std::stoi(aux_data);
    }
  }
  void write_file(std::ofstream & path, short unsigned option)
  {
    if(option == VALUES)
      for(auto && it : data)
      {
        path << it.to_int();
        path << "\n";
      }
    else if(option == ADDRESSES)
      for(auto && it : data)
      {
        path << it.to_string();
        path << "\n";
      }
  }
};
#endif
