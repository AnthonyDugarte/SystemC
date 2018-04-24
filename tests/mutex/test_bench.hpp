#ifndef TEST_BENCH_HPP
#define TEST_BENCH_HPP

/*
  test bench para pruebas de una entrada y una salida
*/
template <int N, typename data>
class test_bench : public sc_module
{
public:
  sc_vector<sc_out<bool>> output;
  sc_in<data> input;
  sc_in<bool> clk_in;

  SC_HAS_PROCESS(test_bench);

  test_bench(const sc_module_name& nm) : sc_module(nm), output("output", N)
  {
    SC_THREAD(test);
    sensitive << clk_in.pos();
  }
private:
  void print()
  {
    for(int it{N - 1}; it >= 0; --it)
      std::cout << output[it].read();
    std::cout << " ";

    cout << input.read() << endl;
  }

  void test()
  {
    std::cout << std::endl;
    std::cout << "upper-case = inputs || lower-case = outputs" << std::endl << std::endl;

    for(size_t it{0}; it < N; ++it)
      std::cout << static_cast<char>(it + 65);
    std::cout << " a" << std::endl;

    size_t tests = 1 << N;
    for(size_t it{0}; it < tests; ++it)
    {
      for(size_t i{0}; i < N; ++i)
        output[i].write(((1 << i) & it));

      wait();
      print();
    }
    sc_stop();
  }
};
#endif
