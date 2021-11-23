CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -Werror=return-type  -Werror=uninitialized


OBJECTS = test.o

main: $(OBJECTS) main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

test.o: test.hpp test.cpp


.PHONY : clean
clean:
	rm $(OBJECTS) main

