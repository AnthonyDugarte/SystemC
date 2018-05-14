#ifndef PIPE_0_HPP
#define PIPE_0_HPP

class pipe_0 : public sc_module
{
public:
  sc_in<bool> clk_in;

  sc_in<Reg> op_input,
                          rgA_input,
                          rgB_input,
                          rgDest_input;
  sc_in<Data> offset_input;

  sc_out<Reg> op_output,
                              rgAaddress_output,
                              rgBaddress_output,
                              rgDest_output;
  sc_out<Data> offset_output;

  pipe_0(const sc_module_name & nm) : sc_module(nm)
  {
    SC_METHOD(write);
    sensitive << clk_in.pos();

    SC_METHOD(read);
    sensitive << clk_in.neg();
  }
private:
  SC_HAS_PROCESS(pipe_0);

  Reg op,
            rgA,
            rgB,
            rgDest;
  Data offset;

  void write()
  {
    op_output.write(op);
    rgAaddress_output.write(rgA);
    rgBaddress_output.write(rgB);
    rgDest_output.write(rgDest);
    offset_output.write(offset);
  }
  void read()
  {
    op = op_input.read();
    rgA = rgA_input.read();
    rgB = rgB_input.read();
    rgDest = rgDest_input.read();
    offset = offset_input.read();
  }
};
#endif
