#include <systemc.h>

#include "arithmetic_logic_unit.hpp"
#include "test_bench.hpp"

int sc_main(int sc_argc, char* sc_argv[])
{
  sc_time PERIOD(10, SC_NS), DELAY(10, SC_NS);
  sc_clock clock("clock", PERIOD, 0.5, DELAY, true);

  sc_signal<sc_bv<8>> a_in("a_in"),
                                   b_in("b_in"),
                                   output("output");
  sc_signal<sc_bv<2>> operation("operation");

  arithmetic_logic_unit<8> prove("prove");
  prove.a_in(a_in);
  prove.b_in(b_in);
  prove.output(output);
  prove.operation(operation);


  test_bench<8> tb("tb");
  tb.clk_in(clock);
  tb.a_out(a_in);
  tb.b_out(b_in);
  tb.input(output);
  tb.operation(operation);

  sc_start();
  return 0;
}
