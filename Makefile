# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -Wall -Wextra -std=c++20

# SDL flags
SDL_FLAGS := $(shell pkg-config --cflags --libs sdl2 SDL2_image SDL2_ttf)

# Directories
SRCDIR := src
OBJDIR := build
BINDIR := bin

# Source & object files
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Output executable
TARGET := $(BINDIR)/Word_Flu

# Default target
all: $(TARGET)
	echo "Success!"

# Link step
$(TARGET): $(OBJS)
	mkdir -p $(BINDIR)
	$(CXX) $(OBJS) $(SDL_FLAGS) -o $@

# Compile step
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run
run: all
	./$(TARGET)

# Clean
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)
