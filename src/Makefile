CC := clang++
cfiles := main.cpp bytecode.cpp vm.cpp scanner.cpp compiler.cpp value.cpp
hfiles := bytecode.hpp vm.hpp scanner.hpp compiler.hpp value.hpp
files := $(cfiles) $(hfiles) Makefile
out := ../bin/main
args := -O0 -ggdb3 -Wall -Wextra -o $(out)

main: $(files)
	$(CC) $(args) $(cfiles) && ./$(out)

clean:
	rm $(out)
