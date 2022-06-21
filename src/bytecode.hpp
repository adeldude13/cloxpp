#ifndef BYTECODE_H
#define BYTECODE_H

#include <inttypes.h>
#include <vector>
#include <stack>

typedef enum {
	CONSTANT,
	NEGATE,
	ADD,
	SUB,
	MULTI,
	DIV,
	RETURN,
} OPCODE;

class Bytecode {
	public:
		int addConst(double, std::size_t);
		double getValue(std::size_t);
		int addValue(double, std::size_t);
		void addOp(uint8_t, std::size_t);
		std::vector<uint8_t> code;
		std::vector<std::size_t> lines;
		std::vector<double> values;
	private:

};


#endif
