#ifndef COMPILER_HPP
#define COMPILER_HPP


#include "scanner.hpp"
#include "bytecode.hpp"
#include <string>
#include <inttypes.h>


class Compiler {
	public:
		Compiler(std::string);
		void next();
		void errorAtCurr();
		void error(std::string, int);
		void errorM(std::string);
		void errorAtPrev(std::string);
		void addByte(uint8_t); // add a byte to bytecode
		void addBytes(uint8_t, uint8_t); // add a bytes to bytecode
		int addValue(double); // adds value returning its index
		void addConst(double); // adds value with CONSTANT opcode


		void expr();
		void number();
		void grouping();
		void unary();
	private:
		Token curr, prev;
		Scanner *scanner;
		Bytecode *bytecode;
};


#endif
