#ifndef TEST_BENCH_HPP
#define TEST_BENCH_HPP

template<int WordSize = 32, int OpSize = 4, int RgSize = 4, int OffsetSize = 16,
  typename =
    std::enable_if_t
    <
      OpSize + RgSize * 3 + OffsetSize == WordSize && WordSize % 2 == 0
    >
>
class test_bench : public sc_module
{
public:
  sc_out<sc_bv<WordSize>> output;

  sc_in<sc_bv<OpSize>> op_input;
  sc_in<sc_bv<RgSize>> rgA_input,
                                     rgB_input,
                                     rgDest_input;
  sc_in<sc_bv<OffsetSize>> offset_input;

  sc_in<bool> clk_in;

  SC_HAS_PROCESS(test_bench);


  test_bench(const sc_module_name& nm) : sc_module(nm)
  {
    SC_THREAD(test);
    sensitive << clk_in.pos();
  }
private:
  void print()
  {
    std::cout << "addres: " << output.read().to_string() << std::endl;
    std::cout << "\top: " << op_input.read().to_string() << std::endl;
    std::cout << "\tRgA: " << rgA_input.read().to_string() << std::endl;
    std::cout << "\tRgB: " << rgB_input.read().to_string() << std::endl;
    std::cout << "\tRgD: " << rgDest_input.read().to_string() << std::endl;
    std::cout << "\toffset: " << offset_input.read().to_string() << std::endl;
    std::cout << "\n\n";
  }

  void test()
  {
    output.write("00101000010100011101000000000101");
    wait(); print();
    output.write("11101010001001000000000010000001");
    wait(); print();
    output.write("00001010111011010000000000001111");
    wait(); print();
    output.write("00000110111001100000111000000001");
    wait(); print();
    sc_stop();
  }
};
#endif
