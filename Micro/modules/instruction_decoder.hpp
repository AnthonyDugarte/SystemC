#ifndef INSTRUCTION_DECODER_HPP
#define INSTRUCTION_DECODER_HPP

class instruction_decoder : public sc_module
{
public:
  sc_in<Address> input;

  sc_out<Reg> op_output;
  sc_out<Reg> rgA_output,
                              rgB_output,
                              rgDest_output;
  sc_out<Data> offset_output;


  instruction_decoder(const sc_module_name & nm)
    : sc_module(nm)
  {
    SC_METHOD(segment);
    sensitive << input;
  }

private:
  SC_HAS_PROCESS(instruction_decoder);

  void segment()
  {
    op_output.write(input.read().range
    (Word_bits - 1, Word_bits - Register_bits));

    rgA_output.write(input.read().range
    (Word_bits - Register_bits, Word_bits - 2 * Register_bits));

    rgB_output.write(input.read().range
    (Word_bits - 2 * Register_bits, Word_bits - 3 * Register_bits));

    rgDest_output.write(input.read().range
    (Word_bits - 3 * Register_bits, Word_bits - 4 * Register_bits));

    offset_output.write(input.read().range
    (Data_bits, 0));
  }
};
#endif
