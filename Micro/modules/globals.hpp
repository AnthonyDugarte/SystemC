#ifndef GLOBALS_HPP
#define GLOBALS_HPP

using namespace std;
#include <vector>
#include <string>
#include <fstream>

#include <systemc.h>

enum ops{ BUB = 0, STORE = 1, LOAD = 2, LOAD_I = 3, JEZ = 4,
                ADD = 8, ADD_I = 9, MUL = 10, MUL_I = 11, SUB = 12, SUB_I = 13 , JMP = 15};

enum memory_ops{ VALUES = 0, ADDRESSES = 1 };

constexpr uint Word_bits = 32;
constexpr uint Data_bits = 16;
constexpr uint Register_bits = 4;

using Address = sc_bv<Word_bits>;
using Data = sc_bv<Data_bits>;
using Reg = sc_bv<Register_bits>;


#endif
