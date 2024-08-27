CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash

all:		bin/solution

bin/solution:	lib_info.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f bin/solution

test:	bin/solution
	@echo Testing output...
	./bin/solution Music.txt

short:  bin/solution
	@echo Testing output...
	./bin/solution Small.txt