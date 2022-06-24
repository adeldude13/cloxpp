#include "compiler.hpp" 
#include "bytecode.hpp"

#include <iostream>
#include <string>

#define MAX_V 255

Compiler::Compiler(std::string src) {
	scanner = new Scanner(src);
	bytecode = new Bytecode;
}

void Compiler::next() {
	prev = curr;
	curr = scanner->fetch();
	if(curr.type == T_ERROR) {
		errorAtCurr();
	}
}

void Compiler::errorAtCurr() {
	error(curr.content, curr.line);
}

void Compiler::error(std::string message, int line) {
	std::cout << message << " line: " << line << std::endl; 
}

void Compiler::errorM(std::string message) {
	std::cout << message << std::endl;
}

void Compiler::errorAtPrev(std::string m) {
	error(m, prev.line);
}

void Compiler::addByte(uint8_t b) {
	bytecode->addOp(b, prev.line);
}


void Compiler::addBytes(uint8_t b, uint8_t a) {
	this->addByte(b);
	this->addByte(a);
}

int Compiler::addValue(double v) {
	bytecode->values.push_back(v);
	int ret = bytecode->values.size() - 1;
	if(ret > 255) {
		errorM("Too Many Constants");
		return 0;
	}
	return ret;	
}

void Compiler::addConst(double v) {
	this->addBytes(CONSTANT, addValue(v));
}



void Compiler::expr() {
	// TODO
}

// std::stof() -- String to Double
void Compiler::number() {
	double v = std::stof(prev.content);
	this->addConst(v);
}

void Compiler::grouping() {
	this->expr();
	if(prev.type != T_RIGHT_P) {
		errorAtPrev("Expected ')' After Expression");
	}
}

void Compiler::unary() {
	TokenType op = prev.type;
	this->expr();
	switch(op) {
		case T_MINUS:
			this->addByte(NEGATE);
			break;
		default:
			return;
	}
}
