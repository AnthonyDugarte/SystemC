#include <systemc.h>

#include "d_register.hpp"
#include "test_bench.hpp"

int sc_main(int sc_argc, char* sc_argv[])
{
  sc_time PERIOD(10, SC_NS), DELAY(10, SC_NS);
  sc_clock clock("clock", PERIOD, 0.5, DELAY, true);

  sc_signal<sc_uint<4>> input("input");
  sc_signal<sc_uint<4>> output("output");
  sc_signal<bool> read_input("read_input");

  d_register<sc_uint<4>> prove("prove");
  prove.input(input);
  prove.output(output);
  prove.read_input(read_input);
  prove.clk_in(clock);

  test_bench<sc_uint<4>> tb("tb");
  tb.output(input);
  tb.input(output);
  tb.read_output(read_input);

  tb.clk_in(clock);

  sc_start();
  return 0;
}
