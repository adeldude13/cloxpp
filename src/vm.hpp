#ifndef VM_H
#define VM_H
#include <stack>

#include "bytecode.hpp"

typedef enum {
	SUCCESS,
	COMPILE_ERROR,
	INTERPRET_ERROR,
} STATUS;


class VM {
	public:
		VM(Bytecode *);
		STATUS run();
		void printStack();
	private:
		Bytecode *bytecode;
		std::stack<double> st;
};

#endif
