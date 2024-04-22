# Define compiler
CC = g++
# Define flags
CFLAGS = -Wall -g

# Define the source files
SRC1 = TwoPipesTwoChildren.cpp

# Define executable names based on source files
EXEC1 = $(SRC1:.cpp=)

# All targets
all: build

# Build command
build: $(EXEC1)

# Build TwoPipesTwoChildren
$(EXEC1): $(SRC1)
	$(CC) $(CFLAGS) -o $(EXEC1) $(SRC1)

# Run command
run: build
	./$(EXEC1)

# Clean up
clean:
	rm -f $(EXEC1)

# Phony targets
.PHONY: all build run clean
