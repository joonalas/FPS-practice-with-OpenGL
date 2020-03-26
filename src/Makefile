COMPILER_FLAGS := -std=c++17
LINKER_FLAGS := -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
SEARCH_FLAGS := -I/usr/include/GLFW/ -I./

EXEC := ./gltest

COMPILER := g++

SRC := $(shell find ./ -type f -name *.cpp)
OBJS := $(SRC:.cpp=.o)

$(EXEC) : $(OBJS)
	$(COMPILER) $(OBJS) $(LINKER_FLAGS) -o $(EXEC)

./%.o : ./%.cpp
	$(COMPILER) $(COMPILER_FLAGS) $(SEARCH_FLAGS) -c $< -o $@

run: $(EXEC)
	$(EXEC)

clean:
	rm -f $(EXEC) $(OBJS)