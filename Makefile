# Define compiler
CC = g++
# Define flags
CFLAGS = -Wall -g

# Define the source files
SRC1 = TwoPipesTwoChildren.cpp
SRC2 = TwoPipesThreeChildren.cpp
SRC3 = DynPipe.cpp

# Define executable names based on source files
EXEC1 = $(SRC1:.cpp=)
EXEC2 = $(SRC2:.cpp=)
EXEC3 = $(SRC3:.cpp=)

# Default build target
all: build

# Build all executables
build: $(EXEC1) $(EXEC2) $(EXEC3)

# Build specific executables
$(EXEC1): $(SRC1)
	$(CC) $(CFLAGS) -o $(EXEC1) $(SRC1)

$(EXEC2): $(SRC2)
	$(CC) $(CFLAGS) -o $(EXEC2) $(SRC2)

$(EXEC3): $(SRC3)
	$(CC) $(CFLAGS) -o $(EXEC3) $(SRC3)

# Run targets for each specific executable
twopipes_twochildren: $(EXEC1)
	./$(EXEC1)

twopipes_threechildren: $(EXEC2)
	./$(EXEC2)

# Clean up all executables
clean:
	rm -f $(EXEC1) $(EXEC2) $(EXEC3)

# Phony targets to ensure proper command handling
.PHONY: all build twopipes_twochildren twopipes_threechildren clean
