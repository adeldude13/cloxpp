CC := clang++
cfiles := main.cpp bytecode.cpp dissassemble.cpp 
hfiles := bytecode.hpp dissassemble.hpp
files := $(cfiles) $(hfiles) Makefile
out := ../bin/main
args := -O0 -ggdb3 -Wall -Wextra -o $(out)

main: $(files)
	$(CC) $(args) $(cfiles) && ./$(out)

clean:
	rm $(out)
