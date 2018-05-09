#ifndef TEST_BENCH_HPP
#define TEST_BENCH_HPP

template<typename Data>
class test_bench : public sc_module
{
public:
  sc_out<Data> output;
  sc_out<bool> read_output;

  sc_in<Data> input;

  sc_in<bool> clk_in;

  SC_HAS_PROCESS(test_bench);

  test_bench(const sc_module_name& nm) : sc_module(nm), clk_in("clk_in"), output("output"),
    read_output("read_output"), input("input")
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

    std::cout << input.read() << std::endl;
  }

  void test()
  {
    std::cout << "D o R" << std::endl;

    output.write(3);
    read_output.write(0);
    wait();
    print();

    output.write(2);
    read_output.write(1);
    wait();
    print();

    output.write(7);
    read_output.write(1);
    wait();
    print();

    output.write(8);
    read_output.write(1);
    wait();
    print();

    output.write(7);
    read_output.write(0);
    wait();
    print();

    output.write(9);
    read_output.write(0);
    wait();
    print();

    sc_stop();
  }
};
#endif
