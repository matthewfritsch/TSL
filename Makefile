# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
BIN = tsl_translator
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Targets
all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BIN) $(OBJS)

debug: $(BIN)
	./$(BIN) -d test.tsl

test: $(BIN)
	./$(BIN) test.tsl

build: $(BIN)
