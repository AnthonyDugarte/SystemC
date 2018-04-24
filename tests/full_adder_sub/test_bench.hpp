#ifndef TEST_BENCH_HPP
#define TEST_BENCH_HPP

template<int N>
class test_bench : public sc_module
{
public:
  sc_vector<sc_out<bool>> a_out;
  sc_vector<sc_out<bool>> b_out;
  sc_out<bool> S_R;

  sc_vector<sc_in<bool>> input;
  sc_in<bool> sign_rem;

  sc_in<bool> clk_in;

  SC_HAS_PROCESS(test_bench);

  test_bench(const sc_module_name& nm) : sc_module(nm), a_out("a_out", N),
    b_out("b_out", N), input("input", N), S_R("S_R"), sign_rem("sign_rem"), clk_in("clk_in")
  {
    SC_THREAD(test);
    sensitive << clk_in.pos();
  }
private:
  void print()
  {
    for(int it{N - 1}; it >= 0; --it)
      std::cout << a_out[it].read();

    if(S_R.read())
      std::cout << " - ";
    else std::cout << " + ";

    for(int it{N - 1}; it >= 0; --it)
      std::cout << b_out[it].read();

    std::cout << " = " << sign_rem.read();

    for(int it{N - 1}; it >= 0; --it)
      std::cout << input[it].read();
    std::cout << std::endl;
  }

  void test()
  {
    std::cout << std::endl;
    std::cout << "upper-case = inputs || lower-case = outputs" << std::endl << std::endl;

    sc_bv<N + 1> numbers;
    size_t printed_numbers { 1 << (N +1)};
    std::cout << "Numbers cheat sheet" << std::endl << std::endl;
    for(size_t it{0}; it < printed_numbers; ++it)
    {
      for(size_t snd{0}; snd < N + 1; ++snd)
        numbers.set_bit(snd, (1 << snd) & it);

      std::cout << numbers.to_string() << " = " << numbers.to_int() << std::endl;
    }
    std::cout << std::endl;


    for(size_t it{0}; it < N; ++it)
      std::cout << "A";
    std::cout << " o ";

    for(size_t it{0}; it < N; ++it)
      std::cout << "B";
    std::cout << " = s";

    for(size_t it{0}; it < N; ++it)
      std::cout << "r";
    std::cout << std::endl;


    size_t tests = 1 << N;

    for(size_t carry{0}; carry < 2; ++carry)
    {
      S_R.write(carry);

      for(size_t it{0}; it < tests; ++it)
      {
        for(size_t a{0}; a < N; ++a)
          a_out[a].write((1 << a) & it);

        for(size_t it_2{0}; it_2 < tests; ++it_2)
        {
          for(size_t b{0}; b < N; ++b)
            b_out[b].write((1 << b) & it_2);

          wait();
          print();
        }
      }
    }

    sc_stop();
  }
};
#endif
