#include <iostream>

#include <stack>
#include "vm.hpp"
#include "bytecode.hpp"


VM::VM() {
	strHead = NULL;
}

bool VM::COMP() {
	Value b = st.top();st.pop();
	Value a = st.top();st.pop();
	if(a.type != b.type) return false;
	switch(a.type) {
		case V_BOOL: return a.b == b.b;
		case V_NUM: return a.number == b.number;
		case V_NIL: return true;
		case V_STR: return a.getStr() == b.getStr();
		default:
			break;
	}
	return false;
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
	
	#define COMPARE(op) do { \
		Value b = st.top();st.pop(); \
		Value a = st.top();st.pop(); \
		if(!a.isNumber() || !b.isNumber()) runTimeError("Cant Compare Non Numeric Values"); \
		st.push(a.number op b.number); \
	} while(0)

	std::size_t curr = 0;
	while(curr < bytecode->code.size()) {
		switch(bytecode->code[curr]) {
			case CONSTANT: {
				Value v = bytecode->getValue(curr++);
				if(v.isStr()) {
					if(strHead == NULL) {
						strHead = v.str;
					} else {
						strHead->addObj(v.str);
					}
				}
				st.push(v);
				break;
			}
			
			case NEGATE: {
				Value t = st.top();
				if(!t.isNumber()) { runTimeError("Cant Negate A none Numeric Value"); }
				st.pop();st.push(Value(-t.getNumber()));
			}
			break;
			case ADD: {
				Value b = st.top();st.pop();
				Value a = st.top();st.pop();
				if(a.type == b.type && a.isStr()) {
					st.push(Value(a.getStr() + b.getStr()));
					break;
				} else {
					// return values to the stack for arithmtic
					st.push(a);
					st.push(b);
				}
				ARITH(+); 
			}
			break;
			case SUB: ARITH(-); break;
			case MULTI: ARITH(*); break;
			case DIV: ARITH(/); break;
			
			case TRUE: PUSH(true); break;
			case FALSE: PUSH(false); break;
			case NIL: st.push(Value()); break;
			case NOT:	{
					if(!st.top().isNil() && !st.top().isBool()) runTimeError("Not Operation on a non Boolean/Nil value");
					Value v = st.top();st.pop();
					if(v.isBool()) {st.push(!v.b);break;}
					st.push(true); // if it was nil
				}
				break;
			case PRINT: st.top().print(); break;
			case EQUAL: st.push(this->COMP());break;
			case LESS: COMPARE(<); break;
			case GREATER: COMPARE(>); break;
			case POP: st.pop(); break;
			case DEFINE_GLOBAL:{
				std::string var = (bytecode->getValue(curr++)).getStr();

				global_map[var] = st.top();st.pop(); 
			}
			break;
			case READ_GLOBAL: {
				std::string var = (bytecode->getValue(curr++)).getStr();
				if(global_map.find(var) == global_map.end()) runTimeError("Cant Find Varible");
				st.push(global_map[var]);
			}
			break;
			case SET_GLOBAL: {
				std::string var = (bytecode->getValue(curr++)).getStr();
				if(global_map.find(var) == global_map.end()) runTimeError("Cant Find Varible");
				global_map[var] = st.top();
				st.pop();
			}
			break;

			case RETURN:
				goto END;	
		}

		curr++;
	}
#undef ARITH


END:
	return SUCCESS;

ERR:
		return RUNTIME_ERROR;
}

void VM::printStack() {
	std::stack<Value> temp = st;
	while(!temp.empty()) {
		temp.top().print();
		std::cout << "\n";
		temp.pop();
	}
}

void VM::free() {
	Str *curr = strHead;
	while(curr) {
		Str *temp = curr->next;
		delete curr;
		curr = temp;
	}
	strHead = NULL;
}

STATUS VM::interpret(std::string source) {
	Compiler compiler(source);
	Bytecode *c = compiler.compile();
	if(compiler.status == false) {
		return COMPILE_ERROR;
	}
	STATUS status = run(c);
	compiler.free();
	return status;
}
