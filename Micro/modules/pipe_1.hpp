#ifndef PIPE_1_HPP
#define PIPE_1_HPP

class pipe_1 : public sc_module
{
public:
  sc_in<bool> clk_in;

  sc_in<Reg> op_input,
                           rgDest_input;
  sc_in<Data> offset_input,
                             rgA_input,
                             rgB_input;


  sc_out<Reg> op_output,
                              rgDest_output;
  sc_out<Data> offset_output,
                                rgA_output,
                                rgB_output;

  pipe_1(const sc_module_name & nm)
    : sc_module(nm)
  {
    SC_METHOD(write);
    sensitive << clk_in.pos();

    SC_METHOD(read);
    sensitive << clk_in.neg();
  }
private:
  SC_HAS_PROCESS(pipe_1);

  Reg op,
            rgDest;
  Data offset;

  Data rgA,
             rgB;

  void write()
  {
    op_output.write(op);
    rgA_output.write(rgA);
    rgB_output.write(rgB);
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
