#ifndef MICROPROCESSOR
#define MICROPROCESSOR

#include "globals.hpp"
#include "program_counter.hpp"
#include "instruction_memory.hpp"
#include "instruction_decoder.hpp"
#include "pipe_0.hpp"
#include "general_register.hpp"
#include "pipe_1.hpp"
#include "arithmetic_logic_unit.hpp"
#include "pipe_2.hpp"
#include "data_memory.hpp"
#include "control_unit.hpp"

using namespace std;

class microprocessor : public sc_module
{
public:
  microprocessor(const sc_module_name & nm, string Instructions, string Data)
    : sc_module(nm), clock("clock", sc_time(10, SC_NS), 0.5, sc_time(10, SC_NS), true),
      PC("PC"), instructionMemory("instructionMemory", ifstream(Instructions)),
      instructionDecoder("instructionDecoder"), pipe0("pipe0"), generalRegister("generalRegister"),
      pipe1("pipe1"), ALU("ALU"), pipe2("pipe2"), dataMemory("dataMemory", ifstream(Data)),
      controlUnit("controlUnit")
  {
    wire_up();
  }

  void start()
  {
    sc_start();
  }
  void save_memories()
  {
    instructionMemory.saveData(std::ofstream("instructions.out"), ADDRESSES);
    dataMemory.saveData(std::ofstream("data.out"), VALUES);
    generalRegister.saveData(std::ofstream("registers.out"), VALUES);
  }

private:
  SC_HAS_PROCESS(microprocessor);

  sc_clock clock;

  /*PC*/program_counter PC;
  sc_signal<bool> pc_readInput;
  sc_signal<Data> instructionAddress;

  /*Instructions Memory*/instruction_memory instructionMemory;
  sc_signal<Address> instructionMemory_input; //empty
  sc_signal<bool> instructionMemory_readInput; //empty
  sc_signal<Address> instruction;

  /*instructionDecoder*/instruction_decoder instructionDecoder;
  sc_signal<Reg> operation0;
  sc_signal<Reg> rgA_address0,
                                  rgB_address0,
                                  rgDest_address0;
  sc_signal<Data> offset0;

  /*pipe0*/pipe_0 pipe0;
  sc_signal<Reg> operation1;
  sc_signal<Reg> rgA_address1,
                                  rgB_address1,
                                  rgDest_address1;
  sc_signal<Data> offset1;


  /*generalRegister*/general_register generalRegister;
  sc_signal<Data> generalRegister_input;
  sc_signal<bool> generalRegister_readInput;
  sc_signal<Reg> generalRegister_addressInput;
  sc_signal<Data> rgA0,
                                    rgB0;

  /*pipe1*/pipe_1 pipe1;
  sc_signal<Reg> operation2;
  sc_signal<Data> rgA1,
                                    rgB1;
  sc_signal<Reg> rgDest_address2;
  sc_signal<Data> offset2;

  /*ALU*/arithmetic_logic_unit ALU;
  sc_signal<Data> ALU_result;

  /*pipe2*/pipe_2 pipe2;
  sc_signal<Reg> operation3;
  sc_signal<Reg> rgDest_address3;
  sc_signal<Data> result0;
  sc_signal<Data> rgDest0;

  /*dataMemory*/data_memory dataMemory;
  sc_signal<bool> dataMemory_readInput;
  sc_signal<Data> dataMemory_output;

  /*controlUnit*/control_unit controlUnit;


  void wire_up()
  {
    //PC
    PC.clk_in(clock);

    PC.input(result0);
    PC.read_input(pc_readInput);

    PC.output(instructionAddress);

    //instructionMemory
    instructionMemory.clk_in(clock);

    instructionMemory.input(instructionMemory_input); //*initialize
    instructionMemory.read_input(instructionMemory_readInput); //*initialize
    instructionMemory.address_input(instructionAddress);

    instructionMemory.output(instruction);

    //instructionDecoder
    instructionDecoder.input(instruction);

    instructionDecoder.op_output(operation0);
    instructionDecoder.rgA_output(rgA_address0);
    instructionDecoder.rgB_output(rgB_address0);
    instructionDecoder.rgDest_output(rgDest_address0);
    instructionDecoder.offset_output(offset0);

    //pipe0
    pipe0.clk_in(clock);

    pipe0.op_input(operation0);
    pipe0.rgA_input(rgA_address0);
    pipe0.rgB_input(rgB_address0);
    pipe0.rgDest_input(rgDest_address0);
    pipe0.offset_input(offset0);

    pipe0.op_output(operation1);
    pipe0.rgAaddress_output(rgA_address1);
    pipe0.rgBaddress_output(rgB_address1);
    pipe0.rgDest_output(rgDest_address1);
    pipe0.offset_output(offset1);

    //generalRegister
    generalRegister.clk_in(clock);

    generalRegister.input(generalRegister_input);
    generalRegister.read_input(generalRegister_readInput);
    generalRegister.address_input(generalRegister_addressInput);
    generalRegister.rgA_address(rgA_address1);
    generalRegister.rgB_address(rgB_address1);
    generalRegister.rgDest_address(rgDest_address1);
    generalRegister.operation(operation1);

    generalRegister.rgA(rgA0);
    generalRegister.rgB(rgB0);

    //pipe1
    pipe1.clk_in(clock);

    pipe1.op_input(operation1);
    pipe1.rgA_input(rgA0);
    pipe1.rgB_input(rgB0);
    pipe1.rgDest_input(rgDest_address1);
    pipe1.offset_input(offset1);

    pipe1.op_output(operation2);
    pipe1.rgA_output(rgA1);
    pipe1.rgB_output(rgB1);
    pipe1.rgDest_output(rgDest_address2);
    pipe1.offset_output(offset2);

    //ALU
    ALU.a_in(rgA1);
    ALU.b_in(rgB1);
    ALU.offset(offset2);
    ALU.operation(operation2);

    ALU.output(ALU_result);

    //pipe2
    pipe2.clk_in(clock);

    pipe2.operation_input(operation2);
    pipe2.rgDest_input(rgDest_address2);
    pipe2.result_input(ALU_result);
    pipe2.rgDestVal_input(rgB1);

    pipe2.operation_output(operation3);
    pipe2.rgDest_output(rgDest_address3);
    pipe2.result_output(result0);
    pipe2.rgDestVal_output(rgDest0);


    //dataMemory
    dataMemory.clk_in(clock);
    dataMemory.input(rgDest0);
    dataMemory.read_input(dataMemory_readInput);
    dataMemory.address_input(result0);

    dataMemory.output(dataMemory_output);

    //controlUnit
    controlUnit.result_rgDestInput(rgDest_address3);
    controlUnit.result_operationInput(operation3);
    controlUnit.result_input(result0);
    controlUnit.alu_input(ALU_result);
    controlUnit.alu_rgDestInput(rgDest_address2);
    controlUnit.alu_operationInput(operation2);
    controlUnit.pc_readInput(pc_readInput);
    controlUnit.generalRegister_input(generalRegister_input);
    controlUnit.generalRegister_readInput(generalRegister_readInput);
    controlUnit.generalRegister_addressInput(generalRegister_addressInput);
    controlUnit.dataMemory_input(dataMemory_output);
    controlUnit.dataMemory_readInput(dataMemory_readInput);

    initialize();
    micro_threads();
  }

  void initialize()
  {
    instructionMemory_input.write(0);
    instructionMemory_readInput.write(0);
  }
  void micro_threads()
  {
    SC_THREAD(pos_event);
    sensitive << clock.posedge_event();

    SC_THREAD(neg_event);
    sensitive << clock.negedge_event();
  }

  void pos_event()
  {
    for(size_t it{ 0 }; it < 1000; ++it)
    {
      wait();
      print_pos();
    }
  }
  void print_pos()
  {
    //cout << "inst Nº " << instructionAddress.read().to_uint();
  }

  void neg_event()
  {
    for(size_t it{ 0 }; it < 1000; ++it)
    {
      wait();
      print_neg();
    }
    sc_stop();
  }
  void print_neg()
  {
    //cout << " instruction: " << instruction.read().to_string() << endl;
    print_inst();
    print_pipe0();
    print_pipe1();
    print_pipe2();
    print_pipe3();
    cout << endl;
  }

  void print_inst()
  {
    cout << "pipe0 stats: ";
    cout << "op: " << operation0.read().to_string() << " rgA: "  << rgA_address0.read().to_string()
              << " rgB: " << rgB_address0.read().to_string() << " rgDest: " << rgDest_address0.read().to_string()
              << " offset: " << offset0.read().to_int() << endl;
  }
  void print_pipe0()
  {
    cout << "pipe1 stats: ";
    cout << "op: " << operation1.read().to_string() << " rgA: "  << rgA_address1.read().to_string()
              << " rgB: " << rgB_address1.read().to_string() << " rgDest: " << rgDest_address1.read().to_string()
              << " offset: " << offset1.read().to_int() << endl;
  }
  void print_pipe1()
  {
    cout << "pipe2 stats: ";
    cout << "op: " << operation2.read().to_string() << " datoA: "  << rgA1.read().to_int()
              << " datoB: " << rgB1.read().to_int() << " rgDest: " << rgDest_address2.read().to_string()
              << " offset: " << offset2.read().to_int() << endl;
  }
  void print_pipe2()
  {
    cout << "pipe3 stats: ";
    cout << "op: " << operation3.read().to_string() << " ALU val: "  << result0.read().to_int()
              << " rgDestVal: " << rgDest0.read().to_int() << " rgDest: " << rgDest_address3.read().to_string()
              << endl;
  }
  void print_pipe3()
  {
    cout << "pipe4 stats: ";
    cout << "PC_read: " << pc_readInput.read() << " GR_input: "  << generalRegister_input.read().to_int()
              << " GR_read: " << generalRegister_readInput.read() << " GR_add: " << generalRegister_addressInput.read().to_string()
              << " DM_out: " << dataMemory_output.read().to_int()
              << " DM_input: " << rgDest0.read().to_int() << " DM_read: " << dataMemory_readInput.read()
              << " DM_add: " << result0.read().to_int() << endl;
  }
};
#endif
