#include <systemc.h>

#include "mutex.hpp"
#include "test_bench.hpp"

int sc_main(int sc_argc, char* sc_argv[])
{
  sc_time PERIOD(10, SC_NS), DELAY(10, SC_NS);
  sc_clock clock("clock", PERIOD, 0.5, DELAY, true);

  const int N{5};

  sc_vector<sc_signal<bool>> ctrl_input("ctrl_input", N);
  sc_vector<sc_signal<sc_int<8>>> input("input", 1 << N);
  sc_signal<sc_int<8>> output("output");

  mutex<N, sc_int<8>> prove("prove");
  prove.ctrl_input(ctrl_input);
  prove.input(input);
  prove.output(output);

  test_bench<N, sc_int<8>> tb1("tb1");
  tb1.output(ctrl_input);
  tb1.input(output);
  tb1.clk_in(clock);


  for(size_t i{0}; i < 1 << N; ++i)
    input[i].write(i + 1);


  sc_start();
  return 0;
}
