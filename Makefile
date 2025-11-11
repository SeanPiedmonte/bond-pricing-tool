.PHONY: all clean test build

CXX = g++
CXXFLAGS = -std=c++23 -Wall 

SOURCES := main.cpp core_calc.cpp Money.cpp
OBJECTS := $(SOURCES:.cpp=.o)

clean:
	rm -f main $(OBJECTS)

all: main

main: $(OBJECTS) 
	$(CXX) $(CFLAGS) -o main $(OBJECTS)
