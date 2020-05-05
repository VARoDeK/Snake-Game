CXX = g++
CXXFLAGS = -Wall -std=c++17
LDFLAGS = -lncurses
DEPS = snake.h
OBJ = functions.o class_snake.o menu.o main.o

# Default goal
snake: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Header dependencies
$(OBJ): $(DEPS)

.PHONY: clean
clean :
	rm -f *.o snake
