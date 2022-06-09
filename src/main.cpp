#include "bytecode.hpp"
#include "vm.hpp"

int main() {
	Bytecode block;
	block.addValue(123, 1);
	block.addOp(NEGATE, 2);
	block.addOp(RETURN, 1);
	VM vm(&block);
	vm.run();
	return 0;
}
