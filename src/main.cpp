#include "bytecode.hpp"

int main() {
	Bytecode block;
	block.addValue(123, 1);
	block.addOp(RETURN, 1);
	block.debug();
	return 0;
}
