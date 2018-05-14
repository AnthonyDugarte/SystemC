#ifndef PIPE_2_HPP
#define PIPE_2_HPP

class pipe_2 : public sc_module
{
public:
  sc_in<bool> clk_in;

  sc_in<Reg> operation_input,
                           rgDest_input;
  sc_in<Data> result_input,
                            rgDestVal_input;

  sc_out<Reg> operation_output,
                              rgDest_output;
  sc_out<Data> result_output,
                               rgDestVal_output;

    pipe_2(const sc_module_name & nm)
      : sc_module(nm)
    {
      SC_METHOD(write);
      sensitive << clk_in.pos();

      SC_METHOD(read);
      sensitive << clk_in.neg();
    }
private:
  SC_HAS_PROCESS(pipe_2);

  Reg operation,
            rgDest;
  Data result,
             rgDestVal;

   void write()
   {
     operation_output.write(operation);
     rgDest_output.write(rgDest);
     result_output.write(result);
     rgDestVal_output.write(rgDestVal);
   }
   void read()
   {
     operation = operation_input.read();
     rgDest = rgDest_input.read();
     result = result_input.read();
     rgDestVal = rgDestVal_input.read();
   }
};
#endif
