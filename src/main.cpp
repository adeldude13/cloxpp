#include "bytecode.hpp"
#include "vm.hpp"

int main() {
	Bytecode block;
	block.addValue(3, 1);
	block.addValue(1, 1);
	block.addOp(DIV, 2);
	
	block.addValue(4, 1);
	block.addValue(1, 1);

	block.addOp(MULTI, 1);

	block.addOp(ADD, 1);
	
	block.addOp(RETURN, 1);

	VM vm(&block);
	vm.run();
	return 0;
}
