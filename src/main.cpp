#include "bytecode.hpp"

int main() {
	Bytecode block;
	block.addValue(123);
	block.addOp(RETURN);
	block.debug();
	return 0;
}
