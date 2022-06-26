#ifndef VM_H
#define VM_H
#include <stack>

#include "bytecode.hpp"
#include "compiler.hpp"

typedef enum {
	SUCCESS,
	COMPILE_ERROR,
	RUN_ERROR,
} STATUS;


class VM {
	public:
		VM();
		STATUS run(Bytecode *);
		STATUS interpret(std::string source);
		void printStack();
	private:
		std::stack<double> st;
};

#endif
