#include <systemc.h>

#include "decoder.hpp"
#include "test_bench.hpp"

int sc_main(int sc_argc, char* sc_argv[])
{
  sc_time PERIOD(10, SC_NS), DELAY(10, SC_NS);
  sc_clock clock("clock", PERIOD, 0.5, DELAY, true);

  const int N{4};

  sc_vector<sc_signal<bool>> input("input", N);
  sc_vector<sc_signal<bool>> output("output", 1 << N);

  decoder<N> prove("prove");
  prove.input(input);
  prove.output(output);

  test_bench<N, 1 << N> tb1("tb1");
  tb1.output(input);
  tb1.input(output);

  tb1.clk_in(clock);
  sc_start();

  return 0;
}
