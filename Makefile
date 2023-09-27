###############################################################################
# File management. This is where the source, header, and object files are defined

# Source files
srcfiles := $(wildcard *.cpp) $(wildcard src/*.cpp)

# Object files directory
objdir := build

# Object files (generated in the build directory)
objects := $(patsubst %.cpp, $(objdir)/%.o, $(srcfiles))

################################################################################

# Compiler selection based on platform
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
    CC = g++
    target := arq
endif
ifeq ($(UNAME), Darwin) # macOS
    CC = clang++
    target := arq
endif
ifeq ($(OS),Windows_NT) # Windows
    CC = g++
    target := arq.exe
endif

# Flags for compiler
CC_FLAGS = -I./include -g

# Command used at clean target
RM = rm -rf

target := arq.exe

# Compilation and linking
all: $(target)

# Production rules: how to make the target - depends on library configuration
$(target): $(objects)
	@echo "Linking $@..."
	$(CC) $(objects) -o $@

# Rule to compile source files into object files in the build directory
$(objdir)/%.o: %.cpp
	@mkdir -p $(@D)  # Create the directory if it doesn't exist
	@echo "Compiling C $<..."
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	$(RM) $(objdir) $(target)

.PHONY: all clean