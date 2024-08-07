all: main

CXX = clang++
CXX_FLAGS=-std=c++20 -Iincludes -gdwarf-4 -fstandalone-debug -O0 -Wall -Wextra -Werror

exec: bin/exec

bin/exec: ./src/main.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: exec clean

clean:
	rm -rf bin/*