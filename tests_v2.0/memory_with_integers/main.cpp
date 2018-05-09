#include <systemc.h>

#include "memory.hpp"
#include "test_bench.hpp"
#include "fstream"

int sc_main(int sc_argc, char* sc_argv[])
{
  sc_time PERIOD(10, SC_NS), DELAY(10, SC_NS);
  sc_clock clock("clock", PERIOD, 0.5, DELAY, true);

  const int N = 2;

  sc_signal<sc_uint<4>> input("input");
  sc_signal<sc_uint<4>> output("output");
  sc_signal<bool> read_input("read_input");
  sc_signal<sc_bv<N>> addres_input("addres_input");

  memory<N, sc_uint<4>> prove("prove", std::ifstream("data.txt"));

  prove.clk_in(clock);
  prove.input(input);
  prove.output(output);
  prove.read_input(read_input);
  prove.addres_input(addres_input);

  test_bench<N, sc_uint<4>> tb("tb");
  tb.clk_in(clock);
  tb.output(input);
  tb.input(output);
  tb.read_output(read_input);
  tb.addres_output(addres_input);

  sc_start();
  return 0;
}
