#ifndef VM_H
#define VM_H
#include <stack>

#include "bytecode.hpp"
#include "compiler.hpp"
#include <unordered_map>

typedef enum {
	SUCCESS,
	COMPILE_ERROR,
	RUNTIME_ERROR,
} STATUS;


class VM {
	public:
		VM();
		STATUS run(Bytecode *);
		STATUS interpret(std::string source);
		void printStack();
		bool COMP();
		void free();
	private:
		std::stack<Value> st;
		Str *strHead;
		std::unordered_map<std::string, Value> global_map;
};

#endif
