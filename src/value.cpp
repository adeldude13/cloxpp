#include "value.hpp" 
#include <string>
#include <stdexcept>
#include <iostream>

Value::Value(double number) {
	this->number = number;
	this->type = V_NUM;
}

Value::Value(bool b) {
	this->b = b;
	this->type = V_BOOL;
}

Value::Value() {
	this->type = V_NIL;
}

void Value::print() {
	if(isNil()) {
		std::cout << getNil();
	}
	else if(isNumber()) {
		std::cout << getNumber();
	}
	else if(isBool()) {
		std::cout << (this->b ? "true" : "false");
	}
}

bool Value::isBool() {return this->type == V_BOOL;}
bool Value::isNumber() {return this->type == V_NUM;}
bool Value::isNil() {return this->type == V_NIL;}

double Value::getNumber() {
	if(!isNumber()) { throw std::runtime_error("Non Numeric Value"); }
	return this->number; 
}

bool Value::getBool() {
	if(!isBool()) { throw std::runtime_error("Non Boolean Value"); }
	return this->b;
}

std::string Value::getNil() {
	if(!isNil()) { throw std::runtime_error("Non Nil Value"); }
	return "Nil";
}
