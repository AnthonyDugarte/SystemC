#ifndef INSTRUCTION_MEMORY_HPP
#define INSTRUCTION_MEMORY_HPP

class instruction_memory : public sc_module
{
public:
  sc_in<bool> clk_in,
                     read_input;
  sc_in<Address> input;
  sc_out<Address> output;

  sc_in<Data> address_input;

  instruction_memory(const sc_module_name& nm)
    : sc_module(nm), data(1 << Data_bits)
  {
    wire_up();
  }

  instruction_memory(const sc_module_name& nm, ifstream & alt_input)
    : sc_module(nm), data(1 << Data_bits)
  {
    read_file(alt_input);
    wire_up();
  }

  instruction_memory(const sc_module_name& nm, ifstream && alt_input)
    : sc_module(nm), data(1 << Data_bits)
  {
    read_file(alt_input);
    wire_up();

    alt_input.close();
  }

  void saveData(ofstream & path, short unsigned option)
  {
    write_file(path, option);
  }
  void saveData(ofstream && path, short unsigned option)
  {
    write_file(path, option);
    path.close();
  }

private:
  SC_HAS_PROCESS(instruction_memory);

  vector<Address> data;

  void wire_up()
  {
    SC_METHOD(write);
    sensitive << clk_in.pos();

    SC_METHOD(read);
    sensitive << clk_in.neg();
  }

  void write()
  {
    output.write(data[address_input.read().to_uint()]);
  }
  void read()
  {
    if(read_input.read())
      data[address_input.read().to_uint()] = input.read();
  }

  void read_file(ifstream & alt_input)
  {
    if(not alt_input.is_open())
     throw  runtime_error("cannot open memory field");

    string aux_data;

    size_t it{ 0 };

    while(not alt_input.eof() and it < data.size())
    {
      getline(alt_input, aux_data);
      if(aux_data.size() == 0)
        break;
      data[it++] = aux_data.c_str();
    }
  }
  void write_file(ofstream & path, short unsigned option)
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
