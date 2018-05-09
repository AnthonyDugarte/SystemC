#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <vector>
#include <string>
#include <fstream>

template<unsigned int size, typename Data>
class memory : public sc_module
{
public:
  sc_in<bool> clk_in,
                     read_input;

  sc_in<Data> input;
  sc_out<Data> output;


  sc_in<sc_bv<size>> addres_input;

  memory(const sc_module_name& nm) : sc_module(nm), input("input"), output("output"),
    clk_in("clk_in"), read_input("read_input"), addres_input("addres_input"), data(1 << size)
  {
    wire_up();
  }


  /*
   * @brief: T parameter is to check if alt_input is a input file type, it is used as an universal
   * parameter to avoid copying.
   * @T plus: if alt_input is an rvalue parameter, at the end of the constructor, the file it has openend
   * is closed.
   *
   * @brief: R parameter if for the data types memory is allow to save:
   *  -> standar c++ integer values and systemC integer values.
   *  -> memory addresses
   */
  template<
    typename T, typename = std::enable_if_t<
      std::is_same<std::ifstream, std::decay_t<T>>::value
    >,
    typename R = Data, typename = std::enable_if_t<
        std::is_integral<std::decay_t<R>>::value
      || std::is_base_of<sc_dt::sc_value_base, std::decay_t<R>>::value
      || std::is_base_of<sc_dt::sc_bv_base , std::decay_t<R>>::value
    >
  >
  memory(const sc_module_name& nm, T&& alt_input)
    : sc_module(nm), data(1 << size)
  {
    if(not alt_input.is_open())
     throw  std::runtime_error("cannot open memory field");

    std::string aux_data;

    size_t it{0};

    if(std::is_base_of<sc_dt::sc_bv_base , std::decay_t<R>>::value)
      while(not alt_input.eof() and it < data.size()) //binary string input
      {
        std::getline(alt_input, aux_data);
        data[it++] = aux_data.c_str();
      }
    else while(not alt_input.eof() and it < data.size()) //integer assignment
    {
      std::getline(alt_input, aux_data);
      data[it++] = std::stoi(aux_data);
    }

    wire_up();

    if(std::is_rvalue_reference<T>::value)
      alt_input.close();
  }

private:
  std::vector<Data> data;

  SC_HAS_PROCESS(memory);

  void write()
  {
    output.write(data[addres_input.read().to_uint()]);
  }
  void read()
  {
    if(read_input.read())
      data[addres_input.read().to_uint()] = input.read();
  }

  void wire_up()
  {
    SC_METHOD(write);
      sensitive << clk_in.pos();
    SC_METHOD(read);
      sensitive << clk_in.neg();
  }
};
#endif
