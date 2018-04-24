#ifndef TEST_BENCH_HPP
#define TEST_BENCH_HPP

template<int N>
class test_bench : public sc_module
{
public:
  sc_vector<sc_out<bool>> output;
  sc_out<bool> flag;
  sc_vector<sc_in<bool>> input;

  sc_in<bool> clk_in;

  SC_HAS_PROCESS(test_bench);

  test_bench(const sc_module_name& nm) : sc_module(nm), output("output", N),
  input("input", N)
  {
    SC_THREAD(test);
    sensitive << clk_in.pos();
  }
private:
  void print()
  {
    std::cout << flag.read() << " ";

    for(int it{N - 1}; it >= 0; --it)
      std::cout << output[it].read();
    std::cout << " = ";

    for(int it{N - 1}; it >= 0; --it)
      std::cout << input[it].read();
    std::cout << std::endl;
  }

  void test()
  {
    std::cout << std::endl;
    std::cout << "upper-case = inputs || lower-case = outputs" << std::endl << std::endl;
    std::cout << "F ";
    for(size_t it{0}; it < N; ++it)
      std::cout << "A";
    std::cout << " = ";

    for(size_t it{0}; it < N; ++it)
      std::cout << "B";
    std::cout << std::endl;

    size_t tests = 1 << N;

    for(size_t ban{0}; ban < 2; ++ban)
    {
      flag.write(ban);
      for(size_t it{0}; it < tests; ++it)
      {
        for(size_t i{0}; i < N; ++i)
          output[i].write((1 << i) & it);

        wait();
        print();
      }
    }
    sc_stop();
  }
};
#endif
