CXX = g++
CXXFLAGS = -Wall -std=c++17 -lncurses
DEPS = snake.h
OBJ = functions.o class_snake.o main.o

# Default goal
snake: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^
	rm *.o

# Header dependencies
$(OBJ): $(DEPS)

.PHONY: clean
clean :
	rm -f *.o snake
