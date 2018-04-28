#ifndef D_REGISTER_HPP
#define D_REGISTER_HPP

template<typename Data>
class d_register : public sc_module
{
public:
  sc_in<bool> clk_in,
                     read_input;

  sc_in<Data> input;
  sc_out<Data> output;

  SC_HAS_PROCESS(d_register);

  d_register(const sc_module_name& nm) : sc_module(nm), input("input"), output("output"),
    data(0), clk_in("clk_in"), read_input("read_input")
  {
    SC_METHOD(write);
    sensitive << clk_in.pos();

    SC_METHOD(read);
    sensitive << clk_in.neg();
  }
private:
  Data data;

  void write()
  {
    output.write(data);
  }

  void read()
  {
    if(read_input.read())
      this->data = input.read();
  }
};
#endif
