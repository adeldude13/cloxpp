#ifndef BYTECODE_H
#define BYTECODE_H

#include <inttypes.h>
#include <vector>
#include <stack>

#include "value.hpp"

typedef enum {
	CONSTANT,
	NEGATE,
	ADD,
	SUB,
	MULTI,
	DIV,
	PRINT,
	TRUE,
	FALSE,
	NIL,
	NOT,
	RETURN,
} OPCODE;

class Bytecode {
	public:
		int addConst(Value, std::size_t);
		Value getValue(std::size_t);
		int addValue(Value, std::size_t);
		void addOp(uint8_t, std::size_t);
		std::vector<uint8_t> code;
		std::vector<std::size_t> lines;
		std::vector<Value> values;
	private:

};


#endif
