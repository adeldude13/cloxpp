#include "bytecode.hpp"
#include "vm.hpp"
#include <iostream>
#include "scanner.hpp"

void repl() {
	std::string line;
	while(1) {
		Token t;
		std::cout << ">> ";
		if(!getline(std::cin, line)) {
			std::cout << "failed to fetch a line!" << std::endl;
			return;
		}
		if(line == "q") {
			return;
		}
		Scanner scanner(line);
		while(1) {
			t = scanner.fetch();
			if(t.type == T_EOF) {
				break;
			}
			std::cout << t.type << " " << t.line << " " << t.content << std::endl;
		}
	}
}

int main() {
	repl(); // TODO	
	return 0;
}
