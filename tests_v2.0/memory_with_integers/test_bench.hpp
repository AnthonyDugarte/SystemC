#ifndef TEST_BENCH_HPP
#define TEST_BENCH_HPP

template<unsigned int size, typename Data>
class test_bench : public sc_module
{
public:
  sc_out<Data> output;
  sc_out<bool> read_output;
  sc_out<sc_bv<size>> addres_output;
  sc_in<Data> input;

  sc_in<bool> clk_in;

  SC_HAS_PROCESS(test_bench);

  test_bench(const sc_module_name& nm) : sc_module(nm), clk_in("clk_in"), output("output"),
    read_output("read_output"), input("input"), addres_output("addres_output")
  {
    SC_THREAD(test);
    sensitive << clk_in.neg();
  }
private:
  void print()
  {
    std::cout << output.read() << " ";

    if(read_output.read())
      std::cout << "1 ";
    else std::cout << "0 ";
    std::cout << addres_output.read().to_uint() << " ";

    std::cout << input.read() << std::endl;
  }

  void test()
  {
    std::cout << "D o P R" << std::endl;

    read_output.write(0);
    size_t cases{1 << size};

    for(size_t it{0}; it < cases; ++it)
    {
      addres_output.write(it);
      wait();
      print();
    }

    sc_stop();
  }
};
#endif
