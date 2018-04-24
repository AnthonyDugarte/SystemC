#include <systemc.h>

#include "half_adder_sub.hpp"
#include "test_bench.hpp"

int sc_main(int sc_argc, char* sc_argv[])
{
  sc_time PERIOD(10, SC_NS), DELAY(10, SC_NS);
  sc_clock clock("clock", PERIOD, 0.5, DELAY, true);

  const int N{3};

  sc_vector<sc_signal<bool>> a_in("a_in", N);
  sc_vector<sc_signal<bool>> b_in("b_in", N);
  sc_signal<bool> S_R;

  sc_vector<sc_signal<bool>> output("output", N);
  sc_signal<bool> carry_output;

  half_adder_sub<N> prove("prove");
  prove.a_in(a_in);
  prove.b_in(b_in);
  prove.S_R(S_R);

  prove.output(output);
  prove.carry_output(carry_output);


  test_bench<N> tb1("tb1");
  tb1.a_out(a_in);
  tb1.b_out(b_in);
  tb1.S_R(S_R);

  tb1.input(output);
  tb1.carry_in(carry_output);

  tb1.clk_in(clock);

  sc_start();
  return 0;
}
