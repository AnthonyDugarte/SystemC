#include <systemc.h>

#include "instruction_decoder.hpp"
#include "test_bench.hpp"

int sc_main(int sc_argc, char* sc_argv[])
{
  sc_time PERIOD(10, SC_NS), DELAY(10, SC_NS);
  sc_clock clock("clock", PERIOD, 0.5, DELAY, true);

  sc_signal<sc_bv<32>> input("input");

  sc_signal<sc_bv<4>> op_output("op_output");
  sc_signal<sc_bv<4>> rgA_output("rgA_output"),
                                   rgB_output("rgB_output"),
                                   rgDest_output("rgDest_output");
  sc_signal<sc_bv<16>> offset_output("offset_output");

  instruction_decoder<> prove("prove");
  prove.input(input);
  prove.op_output(op_output);
  prove.rgA_output(rgA_output);
  prove.rgB_output(rgB_output);
  prove.rgDest_output(rgDest_output);
  prove.offset_output(offset_output);


  test_bench<> tb("tb");
  tb.clk_in(clock);
  tb.output(input);
  tb.op_input(op_output);
  tb.rgA_input(rgA_output);
  tb.rgB_input(rgB_output);
  tb.rgDest_input(rgDest_output);
  tb.offset_input(offset_output);

  sc_start();
  return 0;
}
