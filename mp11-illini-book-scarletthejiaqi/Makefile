CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fsanitize=address -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/utilities.cc ./src/illini_book.cc ./includes/illini_book.hpp ./includes/utilities.hpp ./includes/node.hpp ./includes/circular-linked-list.hpp
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/utilities.cc ./src/illini_book.cc ./src/circular-linked-list.cc -o $@

bin/tests: ./tests/tests.cc ./src/driver.cc ./src/utilities.cc ./src/illini_book.cc ./includes/illini_book.hpp ./includes/utilities.hpp ./includes/node.hpp ./includes/circular-linked-list.hpp
	$(CXX) $(CXXFLAGS) ./tests/tests.cc ./src/utilities.cc ./src/illini_book.cc ./src/circular-linked-list.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* 