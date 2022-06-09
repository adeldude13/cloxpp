#include "dissassemble.hpp"
#include "bytecode.hpp"
#include <inttypes.h>

int Bytecode::addValue(double value, std::size_t line) {
	this->values.push_back(value);
	this->addOp(CONSTANT, line);	
	this->addOp(this->values.size()-1, line);	
	return this->values.size() - 1;
}

void Bytecode::debug() {
	dissass(this);	
}

void Bytecode::addOp(uint8_t op, std::size_t line) {
	this->code.push_back(op);
	this->lines.push_back(line);
}

