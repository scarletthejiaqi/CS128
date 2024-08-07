CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -pedantic -fsanitize=address,null -fno-omit-frame-pointer $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/dna_strand.cc ./includes/dna_strand.hpp
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/dna_strand.cc -o $@

bin/tests: ./tests/tests.cc ./src/dna_strand.cc ./includes/dna_strand.hpp
	$(CXX) $(CXXFLAGS) ./tests/tests.cc ./src/dna_strand.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf ./bin/*
