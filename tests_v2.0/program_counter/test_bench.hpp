#ifndef TEST_BENCH_HPP
#define TEST_BENCH_HPP

template<int size>
class test_bench : public sc_module
{
public:
  sc_in<sc_bv<size>> input;
  sc_in<bool> clk_in;
  sc_out<bool> read_output;
  sc_out<sc_bv<size>> output;


  test_bench(const sc_module_name& nm) : sc_module(nm)
  {
    SC_THREAD(test);
    sensitive << clk_in.pos();
  }
private:
  SC_HAS_PROCESS(test_bench);

  void print()
  {
    std::cout << "write? ";
    if(read_output.read())
      std::cout << "Y ";
    else std::cout << "N ";

    std::cout << "addres: " << input.read().to_string();

    if(read_output.read())
      std::cout << " new one: " << output.read().to_string();

    std::cout << std::endl;
  }

  void test()
  {
    for(size_t it{ 0 }; it < 10; ++it)
    {
      wait();
      print();
    }
    std::cout << std::endl;

    read_output.write(1);
    output.write("00000011");
    wait();
    print();

    std::cout << std::endl;
    read_output.write(0);

    for(size_t it{ 0 }; it < 10; ++it)
    {
      wait();
      print();
    }
    sc_stop();
  }
};
#endif
