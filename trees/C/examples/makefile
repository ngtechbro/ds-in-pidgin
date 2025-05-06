# Makefile for bst_phonebook

# Compiler
CC = gcc

# Output binary name
TARGET = bst_phonebook

# Source files
SRC = bst_phonebook.c \
      ../impl/binary-tree/binary_tree.c \
      ../impl/binary_tree_traversal.c \
      includes/linenoise.c

# Include directories
INCLUDES = -I../impl/binary-tree -I../impl -Iincludes

# Compiler flags
CFLAGS = -Wall -Wextra -g $(INCLUDES)

# Default rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)

# Clean up
clean:
	rm -f $(TARGET)
