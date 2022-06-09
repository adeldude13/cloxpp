#include <iostream>

#include <stack>
#include "vm.hpp"
#include "bytecode.hpp"

VM::VM(Bytecode *block) {
	bytecode = block;
}


STATUS VM::run() {
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
				break;
			}
		
			case ADD: {
				double v1 = st.top();
				st.pop();
				if(st.empty()) {
					std::cout << "Wrong Use Of The Plus Operator" << std::endl;
					return RUN_ERROR;
				}
				double v2 = st.top();
				st.pop();
				st.push(v2 + v1);
				break;
			}
		

			case SUB: {
				double v1 = st.top();
				st.pop();
				if(st.empty()) {
					std::cout << "Wrong Use Of The Minus Operator" << std::endl;
					return RUN_ERROR;
				}
				double v2 = st.top();
				st.pop();
				st.push(v2 - v1);
				break;
			}

			case MULTI: {
				double v1 = st.top();
				st.pop();
				if(st.empty()) {
					std::cout << "Wrong Use Of The Minus Operator" << std::endl;
					return RUN_ERROR;
				}
				double v2 = st.top();
				st.pop();
				st.push(v2 * v1);
				break;
			}

			case DIV: {
				double v1 = st.top();
				st.pop();
				if(st.empty()) {
					std::cout << "Wrong Use Of The Minus Operator" << std::endl;
					return RUN_ERROR;
				}
				double v2 = st.top();
				st.pop();
				st.push(v2 / v1);
				break;
			}

			case RETURN:
				goto END;	
		}

		curr++;
	}
END:
	this->printStack();
	return SUCCESS;
}

void VM::printStack() {
	std::stack<double> temp = st;
	while(!temp.empty()) {
		std::cout << temp.top() << std::endl;
		temp.pop();
	}
}
