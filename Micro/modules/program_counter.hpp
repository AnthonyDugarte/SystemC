#ifndef PROGRAM_COUNTER_HPP
#define PROGRAM_COUNTER_HPP

class program_counter : public sc_module
{
public:
  sc_in<Data> input;

  sc_in<bool> clk_in,
                     read_input;

  sc_out<Data> output;

  program_counter(const sc_module_name & nm)
    : sc_module(nm), addres(0)
  {
    SC_METHOD(write);
      sensitive << clk_in.pos();

    SC_METHOD(read);
      sensitive << clk_in.neg();
  }
private:
  SC_HAS_PROCESS(program_counter);

  Data addres;

  void write()
  {
    output.write(addres);
    addres = addres.to_uint() + 1;
  }

  void read()
  {
    if(read_input.read())
      addres = input.read();
  }
};
#endif
