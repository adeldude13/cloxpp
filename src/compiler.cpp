#include "compiler.hpp" 
#include "bytecode.hpp"

#include <iostream>
#include <string>

#define MAX_V 255

Compiler::Compiler(std::string src) {
	scanner = new Scanner(src);
	bytecode = new Bytecode;
	typedef Compiler C;
	
	p_map[T_NUM] = {&C::number, NULL, P_NONE}; 
	p_map[T_STR] = {NULL, NULL, P_NONE}; 
	p_map[T_IDEN] = {NULL, NULL, P_NONE}; 
	p_map[T_BANG] = {&C::unary, NULL, P_NONE}; 
	p_map[T_BANG_EQUAL] = {NULL, &C::binary, P_EQUAL}; 
	p_map[T_EQUAL_EQUAL] = {NULL, &C::binary, P_EQUAL}; 
	p_map[T_LESS] = {NULL, &C::binary, P_COMPARE}; 
	p_map[T_GREATER] = {NULL, &C::binary, P_COMPARE}; 
	p_map[T_LESS_EQUAL] = {NULL, &C::binary, P_COMPARE}; 
	p_map[T_GREATER_EQUAL] = {NULL, &C::binary, P_COMPARE}; 
	p_map[T_PLUS] = {NULL, &C::binary, P_TERM}; 
	p_map[T_MINUS] = {&C::unary, &C::binary, P_UNARY}; 
	p_map[T_STAR] = {NULL, &C::binary, P_FACTOR}; 
	p_map[T_SLASH] = {NULL, &C::binary, P_FACTOR}; 
	p_map[T_EQUAL] = {NULL, NULL, P_NONE}; 
	p_map[T_LEFT_P] = {&C::grouping, NULL, P_NONE}; 
	p_map[T_RIGHT_P] = {NULL, NULL, P_NONE}; 
	p_map[T_LEFT_B] = {NULL, NULL, P_NONE}; 
	p_map[T_RIGHT_B] = {NULL, NULL, P_NONE}; 
	p_map[T_DOT] = {NULL, NULL, P_NONE}; 
	p_map[T_COMMA] = {NULL, NULL, P_NONE}; 
	p_map[T_SEMICOLON] = {NULL, NULL, P_NONE}; 
	p_map[T_CLASS] = {NULL, NULL, P_NONE}; 
	p_map[T_IF] = {NULL, NULL, P_NONE}; 
	p_map[T_ELSE] = {NULL, NULL, P_NONE}; 
	p_map[T_FOR] = {NULL, NULL, P_NONE}; 
	p_map[T_WHILE] = {NULL, NULL, P_NONE}; 
	p_map[T_VAR] = {NULL, NULL, P_NONE}; 
	p_map[T_RETURN] = {NULL, NULL, P_NONE}; 
	p_map[T_SUPER] = {NULL, NULL, P_NONE}; 
	p_map[T_OR] = {NULL, NULL, P_NONE}; 
	p_map[T_AND] = {NULL, NULL, P_NONE}; 
	p_map[T_NIL] = {&Compiler::literal, NULL, P_NONE}; 
	p_map[T_TRUE] = {&Compiler::literal, NULL, P_NONE}; 
	p_map[T_FALSE] = {&Compiler::literal, NULL, P_NONE}; 
	p_map[T_FUN] = {NULL, NULL, P_NONE}; 
	p_map[T_PRINT] = {NULL, NULL, P_NONE}; 
	p_map[T_THIS] = {NULL, NULL, P_NONE}; 
	p_map[T_ERROR] = {NULL, NULL, P_NONE}; 
	p_map[T_EOF] = {NULL, NULL, P_NONE}; 
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
	status = false;
}

void Compiler::errorM(std::string message) {
	std::cout << message << std::endl;
	status = false;
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

int Compiler::addValue(Value v) {
	bytecode->values.push_back(v);
	int ret = bytecode->values.size() - 1;
	if(ret > 255) {
		errorM("Too Many Constants");
		return 0;
	}
	return ret;	
}

void Compiler::addConst(Value v) {
	this->addBytes(CONSTANT, addValue(v));
}

void Compiler::parsePrio(Prio p) {
	this->next();
	parseRule token = this->getRule(prev.type);
	if(token.prev == NULL) {
		errorAtPrev("Expected Expression");
	}
	(this->*token.prev)(); // unary -- grouping
	while(p <= getRule(curr.type).prio) {
		this->next();
		(this->*(getRule(prev.type).mid))();
	}
}


void Compiler::expr() {
	parsePrio(P_ASSIGN);
}

// std::stof() -- String to Double
void Compiler::number() {
	double v = std::stof(prev.content);
	this->addConst(Value(v));
}

void Compiler::grouping() {
	this->expr();	
	if(curr.type != T_RIGHT_P) {
		errorAtPrev("Expected ')' After Expression");
	}
	this->next();
}

void Compiler::unary() {
	TokenType op = prev.type;
	parsePrio(P_UNARY);	
	switch(op) {
		case T_MINUS: this->addByte(NEGATE); break;
		case T_BANG: this->addByte(NOT); break;
		default:
			return;
	}
}

void Compiler::binary() {
	TokenType op = prev.type;
	parseRule rule = getRule(op);
	parsePrio((Prio)(rule.prio + 1));
	switch(op) {
		case T_PLUS: this->addByte(ADD); return;
		case T_MINUS: this->addByte(SUB); return;
		case T_STAR: this->addByte(MULTI); return;
		case T_SLASH: this->addByte(DIV); return;
		case T_EQUAL_EQUAL: this->addByte(EQUAL); return;
		case T_BANG_EQUAL: this->addBytes(EQUAL, NOT); return;
		case T_GREATER_EQUAL: this->addBytes(LESS, NOT); return;
		case T_LESS_EQUAL: this->addBytes(GREATER, NOT); return;
		case T_GREATER: this->addByte(GREATER); return;
		case T_LESS: this->addByte(LESS); return;
		default:
			return;
	}
}

void Compiler::literal() {
	switch(prev.type) {
		case T_NIL: this->addByte(NIL); break;
		case T_TRUE: this->addByte(TRUE); break;
		case T_FALSE: this->addByte(FALSE); break;
		default:
			return;
	}
}

Bytecode *Compiler::compile() {
	this->next();
	this->expr();
	this->addByte(RETURN);
	return bytecode;
}

void Compiler::free() {
	delete scanner;
	delete bytecode;
}
