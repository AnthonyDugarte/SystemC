#include "microprocessor.hpp"

int sc_main(int sc_argc, char* sc_argv[])
{
  microprocessor trial("trial",  "fibonacci.rom", "data.rom");
  //microprocessor trial("trial",  "nth_fibonacci.rom", "data.rom");

  trial.start();

  trial.save_memories();
  return 0;
}
