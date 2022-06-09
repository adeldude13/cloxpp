#ifndef BYTECODE_H
#define BYTECODE_H

#include <inttypes.h>
#include <vector>
#include <stack>

typedef enum {
	CONSTANT,
	RETURN,
} OPCODE;

class Bytecode {
	public:
		int addValue(double);
		void addOp(uint8_t);
		void debug();
		std::vector<uint8_t> code;
		std::vector<double> values;
		
	private:

};


#endif
