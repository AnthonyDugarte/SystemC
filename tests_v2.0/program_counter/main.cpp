#include <systemc.h>

#include "program_counter.hpp"
#include "test_bench.hpp"

int sc_main(int sc_argc, char* sc_argv[])
{
  sc_time PERIOD(10, SC_NS), DELAY(10, SC_NS);
  sc_clock clock("clock", PERIOD, 0.5, DELAY, true);

  sc_signal<sc_bv<8>> input("input"),
                                   output("output");
  sc_signal<bool> read_input("read_input");

  program_counter<8> prove("prove");
  prove.clk_in(clock);
  prove.input(input);
  prove.output(output);
  prove.read_input(read_input);


  test_bench<8> tb("tb");
  tb.clk_in(clock);
  tb.output(input);
  tb.input(output);
  tb.read_output(read_input);

  sc_start();
  return 0;
}
