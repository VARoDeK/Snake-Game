CXX = g++
CXXFLAGS = -Wall -std=c++17
DEPS = snake.h
OBJ = snake.o

# Default goal
snake: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^	

# Header dependencies
$(OBJ): $(DEPS)

.PHONY: clean
clean :
	rm *.o snake
