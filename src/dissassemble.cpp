#include "dissassemble.hpp"
#include "bytecode.hpp"
#include <iostream>
#include <iomanip> 

int d_instruction(uint8_t inst, int i, Bytecode *block) {
	int ret = 0;
	switch(inst) {
		case RETURN:
			ret = 1;
			std::cout << std::hex << i << " | RETURN" << std::endl;
			break;
		case CONSTANT:
			ret = 2;
			std::cout << std::hex << i << " | CONSTANT " << block->values[block->code[i+1]] << std::endl;
			break;
		default:
			// nothing lol
			break;
	}
	return ret;
}


void dissass(Bytecode *block) {
	std::size_t i = 0;
	while(i<block->code.size()) {
		i += d_instruction(block->code[i], i, block);
	}
}
