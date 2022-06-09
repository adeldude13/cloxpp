#ifndef DISSASSEMBLE_H
#define DISSASSEMBLE_H

#include "bytecode.hpp"

void dissass(Bytecode *);
int d_instruction(OPCODE, int, Bytecode *);


#endif
