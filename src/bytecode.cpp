#include "dissassemble.hpp"
#include "bytecode.hpp"
#include <inttypes.h>

int Bytecode::addValue(double value) {
	this->values.push_back(value);
	this->code.push_back(CONSTANT);
	this->code.push_back(values.size() - 1);
	return this->values.size() - 1;
}

void Bytecode::debug() {
	dissass(this);	
}

void Bytecode::addOp(uint8_t op) {
	this->code.push_back(op);
}
