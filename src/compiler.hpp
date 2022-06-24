#ifndef COMPILER_HPP
#define COMPILER_HPP


#include "scanner.hpp"
#include "bytecode.hpp"
#include <string>
#include <inttypes.h>

typedef enum {
 	P_NONE,
  P_ASSIGN,  //			=
  P_OR,          // or
  P_AND,         // and
  P_EQUAL,    // == !=
  P_COMPARE,  // < > <= >=
  P_TERM,        // + -
  P_FACTOR,      // * /
  P_UNARY,       // ! -
  P_CALL,        // . ()
  P_PRIMARY
} Prio;


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

		typedef struct {
			void (Compiler::*prev)(void);
			void (Compiler::*mid)(void);
			Prio prio;
		} parseRule;

		void parsePrio(Prio);
		void expr();
		void number();
		void grouping();
		void unary();
		void binary();
		parseRule getRule(TokenType t) {
			return p_map[t];	
		}
	private:

		Token curr, prev;
		Scanner *scanner;
		Bytecode *bytecode;
		std::unordered_map<TokenType, parseRule> p_map;
};


#endif
