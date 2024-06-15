CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 

SOURCES = $(wildcard *.cpp)
OBJECTS = $(filter-out Test.o Demo.o, $(SOURCES:.cpp=.o))
DEPS = $(SOURCES:.cpp=.d)

# Targets
all: demo test

demo: Demo.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind: demo
	valgrind --leak-check=full ./demo

# Clean
clean:
	rm -f $(OBJECTS) $(DEPS) demo test

.PHONY: all valgrind clean
