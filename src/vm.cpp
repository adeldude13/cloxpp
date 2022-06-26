#include <iostream>

#include <stack>
#include "vm.hpp"
#include "bytecode.hpp"

VM::VM() {
}

STATUS VM::run(Bytecode *bytecode) {
	#define PUSH(v) do { st.push(Value(v)); } while(0)
	#define runTimeError(message) do { std::cout << "RunTime Error: " << message << std::endl; goto ERR; } while(0)
	#define ARITH(op) do { \
		Value b = st.top();st.pop(); \
		Value a = st.top();st.pop(); \
		if(!(a.type == b.type && (a.isNumber() && b.isNumber()))) runTimeError("RunTime Error: Cant Have Arithmetic on non numeric values");\
		st.push(Value(a.getNumber() op b.getNumber())); \
	} while(0)


	std::size_t curr = 0;
	while(curr < bytecode->code.size()) {
		switch(bytecode->code[curr]) {
			case CONSTANT: {
				Value v = bytecode->getValue(curr++);
				st.push(v);
				break;
			}
			
			case NEGATE: {
				Value t = st.top();
				if(!t.isNumber()) { runTimeError("Cant Negate A none Numeric Value"); }
				st.pop();st.push(Value(-t.getNumber()));
			}
			break;
			case ADD: ARITH(+); break;
			case SUB: ARITH(-); break;
			case MULTI: ARITH(*); break;
			case DIV: ARITH(/); break;
			
			case TRUE: PUSH(true); break;
			case FALSE: PUSH(false); break;
			case NIL: st.push(Value()); break;

			case PRINT: st.top().print();
			case RETURN:
				goto END;	
		}

		curr++;
	}
#undef ARITH

ERR:
		return RUNTIME_ERROR;

END:
	return SUCCESS;
}

void VM::printStack() {
	std::stack<Value> temp = st;
	while(!temp.empty()) {
		temp.top().print();
		std::cout << "\n";
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
