#ifndef INSTRUCTION_DECODER_HPP
#define INSTRUCTION_DECODER_HPP

template<int WordSize = 32, int OpSize = 4, int RgSize = 4, int OffsetSize = 16,
  typename =
    std::enable_if_t
    <
      OpSize + RgSize * 3 + OffsetSize == WordSize && WordSize % 2 == 0
    >
>
class instruction_decoder : public sc_module
{
public:
  sc_in<sc_bv<WordSize>> input;

  sc_out<sc_bv<OpSize>> op_output;
  sc_out<sc_bv<RgSize>> rgA_output,
                                       rgB_output,
                                       rgDest_output;
  sc_out<sc_bv<OffsetSize>> offset_output;


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
    (WordSize - 1, WordSize - OpSize));

    rgA_output.write(input.read().range
    (WordSize - OpSize, WordSize - OpSize - RgSize));

    rgB_output.write(input.read().range
    (WordSize - OpSize - RgSize, WordSize - OpSize - RgSize * 2));

    rgDest_output.write(input.read().range
    (WordSize - OpSize - RgSize * 2, WordSize - OpSize - RgSize * 3));

    offset_output.write(input.read().range
    (OffsetSize, 0));
  }
};
#endif
