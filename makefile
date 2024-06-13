# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 

# Source and object files
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPS = $(SOURCES:.cpp=.d)

# Executable
EXEC = game

# Targets
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Valgrind check
valgrind: $(EXEC)
	valgrind --leak-check=full ./$(EXEC)

# Clean
clean:
	rm -f $(OBJECTS) $(DEPS) $(EXEC)

.PHONY: all valgrind clean
