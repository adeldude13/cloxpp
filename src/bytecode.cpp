#include "bytecode.hpp"
#include <inttypes.h>

int Bytecode::addConst(double value, std::size_t line) {
	this->values.push_back(value);
	this->addOp(CONSTANT, line);	
	this->addOp(this->values.size()-1, line);	
	return this->values.size() - 1;
}

int Bytecode::addValue(double value, std::size_t line) {
	this->values.push_back(value);
	this->lines.push_back(line);
	return this->values.size() - 1;
}

void Bytecode::addOp(uint8_t op, std::size_t line) {
	this->code.push_back(op);
	this->lines.push_back(line);
}

double Bytecode::getValue(std::size_t index) {
	return this->values[this->code[index+1]];
}
