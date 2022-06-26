#include <iostream>

#include <stack>
#include "vm.hpp"
#include "bytecode.hpp"

VM::VM() {
}


STATUS VM::run(Bytecode *bytecode) {
	#define ARITH(op) do { \
		double b = st.top();st.pop(); \
		double a = st.top();st.pop(); \
		st.push(a op b); \
	} while(0)


	std::size_t curr = 0;
	while(curr < bytecode->code.size()) {
		switch(bytecode->code[curr]) {
			case CONSTANT: {
				double v = bytecode->getValue(curr++);
				st.push(v);
				break;
			}
			
			case NEGATE: {
				double t = st.top();
				st.pop();st.push(-t);
			}
			break;
			case ADD: ARITH(+); break;
			case SUB: ARITH(-); break;
			case MULTI: ARITH(*); break;
			case DIV: ARITH(/); break;

			case RETURN:
				goto END;	
		}

		curr++;
	}
#undef ARITH
END:
	return SUCCESS;
}

void VM::printStack() {
	std::stack<double> temp = st;
	while(!temp.empty()) {
		std::cout << temp.top() << std::endl;
		temp.pop();
	}
}

STATUS VM::interpret(std::string source) {
	Compiler compiler(source);
	Bytecode *c = compiler.compile();
	if(compiler.status == false) {
		return COMPILE_ERROR;
	}
	STATUS status = run(c);
	this->printStack();
	compiler.free();
	return status;
}
