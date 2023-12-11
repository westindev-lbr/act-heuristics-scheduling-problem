CXX= g++
CXXFLAGS= -Wall -Wextra -Wpedantic -std=c++17
LEAK= -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address -fsanitize=undefined

PROG=heuristik
VERSION= 0.1

SRC= $(wildcard *.cpp)
HSRC = *.hpp
OBJ= $(SRC:.cpp=.o)


all: $(PROG)

dev: 
	$(CXX) $(CXXFLAGS) $(LEAK) -g $(SRC)

$(PROG): $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp $(HSRC)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	@rm -f *.o *.out $(PROG)
