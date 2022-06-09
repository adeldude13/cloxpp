#include "dissassemble.hpp"
#include "bytecode.hpp"
#include <iostream>
#include <iomanip> 
#include <string>

std::size_t last = 0;

int d_instruction(uint8_t inst, int i, Bytecode *block) {
	int ret = 0;
	std::string lString = last == block->lines[i] ? " " : std::to_string(block->lines[i]);
	std::cout << lString;
	switch(inst) {
		case RETURN:
			ret = 1;
			std::cout << " | RETURN" << std::endl;
			break;
		case CONSTANT:
			ret = 2;
			std::cout << " | CONSTANT " << block->values[block->code[i+1]] << std::endl;
			break;
		default:
			// nothing lol
			break;
	}
	last = block->lines[i];
	return ret;
}


void dissass(Bytecode *block) {
	std::size_t i = 0;
	while(i<block->code.size()) {
		i += d_instruction(block->code[i], i, block);
	}
}
