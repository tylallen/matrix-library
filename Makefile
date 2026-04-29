# --- Compiler Settings ---

CXX      := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -Wpedantic -O3 -I./include -I./tests

# --- Files ---

TARGET   := test_library
DEMO_TARGET := gof_demo

SRC      := tests/catch_amalgamated.cpp tests/test_matrix.cpp
DEMO_SRC := tests/gof.cpp

# --- Rules ---

all: $(TARGET)

$(TARGET): $(SRC)
		$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

$(DEMO_TARGET): $(DEMO_SRC)
		$(CXX) $(CXXFLAGS) $(DEMO_SRC) -o $(DEMO_TARGET)

test: all
		./$(TARGET)

clean:
		rm -f $(TARGET) $(DEMO_TARGET) *.o

.PHONY: all test clean