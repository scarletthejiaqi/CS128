CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fsanitize=address -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/cord_utilities.cc ./src/cord.cc ./includes/cord_utilities.hpp ./includes/cord.hpp ./includes/shared_pointer.hpp
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/cord_utilities.cc ./src/cord.cc -o $@

bin/tests: ./tests/tests.cc ./src/cord_utilities.cc ./src/cord.cc ./includes/cord_utilities.hpp ./includes/cord.hpp ./includes/shared_pointer.hpp
	$(CXX) $(CXXFLAGS) ./tests/tests.cc ./src/cord_utilities.cc ./src/cord.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* 