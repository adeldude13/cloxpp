#include "bytecode.hpp"
#include "vm.hpp"

int main() {
	Bytecode block;
	block.addValue(3, 1);
	block.addValue(1, 1);
	block.addOp(ADD, 2);
	block.addOp(RETURN, 1);
	VM vm(&block);
	vm.run();
	return 0;
}
