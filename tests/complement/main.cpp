#include <systemc.h>

#include "complement_1.hpp"
#include "complement_2.hpp"
#include "test_bench.hpp"

int sc_main(int sc_argc, char* sc_argv[])
{
  sc_time PERIOD(10, SC_NS), DELAY(10, SC_NS);
  sc_clock clock("clock", PERIOD, 0.5, DELAY, true);

  const int N{3};

  sc_vector<sc_signal<bool>> input("a_in", N);
  sc_vector<sc_signal<bool>> output("output", N);
  sc_signal<bool> flag;

  complement_2<N> prove("prove");
  prove.input(input);
  prove.flag(flag);
  prove.output(output);

  test_bench<N> tb1("tb1");
  tb1.output(input);
  tb1.flag(flag);
  tb1.input(output);

  tb1.clk_in(clock);


  sc_start();
  return 0;
}
