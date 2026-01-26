# =========================
# Compilers
# =========================
CXX_LINUX := g++
CXX_WIN   := x86_64-w64-mingw32-g++

# =========================
# Flags
# =========================
CXXFLAGS := -Wall -Wextra -std=c++20 -O2

# =========================
# SDL (Linux)
# =========================
SDL_LINUX := $(shell pkg-config --cflags --libs sdl2 SDL2_ttf)

# =========================
# SDL (Windows - MinGW)
# =========================
SDL_WIN_INC := -Iexternal/SDL2/include
SDL_WIN_LIB := -Lexternal/SDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf


SDL_WIN_DLLS := \
	external/SDL2/bin/SDL2.dll \
	external/SDL2/bin/SDL2_ttf.dll

# =========================
# Directories
# =========================
SRCDIR := src
OBJDIR := build
BINDIR := bin

OBJ_LINUX := $(OBJDIR)/linux
OBJ_WIN   := $(OBJDIR)/windows

# =========================
# Files
# =========================
SRCS := $(wildcard $(SRCDIR)/*.cpp)

OBJS_LINUX := $(SRCS:$(SRCDIR)/%.cpp=$(OBJ_LINUX)/%.o)
OBJS_WIN   := $(SRCS:$(SRCDIR)/%.cpp=$(OBJ_WIN)/%.o)

TARGET_LNX := $(BINDIR)/Word_Flu
TARGET_WIN := $(BINDIR)/Word_Flu.exe

# =========================
# Default
# =========================
.PHONY: all linux windows clean
all: linux windows
	@echo "Success"

# =========================
# Linux build
# =========================
linux: $(TARGET_LNX)

$(TARGET_LNX): $(OBJS_LINUX)
	@mkdir -p $(BINDIR)
	$(CXX_LINUX) $^ $(SDL_LINUX) -o $@

$(OBJ_LINUX)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJ_LINUX)
	$(CXX_LINUX) $(CXXFLAGS) -c $< -o $@

# =========================
# Windows build
# =========================
windows: $(TARGET_WIN)

$(TARGET_WIN): $(OBJS_WIN)
	@mkdir -p $(BINDIR)
	$(CXX_WIN) $^ $(SDL_WIN_LIB) -o $@
	@cp $(SDL_WIN_DLLS) $(BINDIR)

$(OBJ_WIN)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJ_WIN)
	$(CXX_WIN) $(CXXFLAGS) $(SDL_WIN_INC) -c $< -o $@

# =========================
# Clean
# =========================
clean:
	rm -rf $(OBJDIR) $(BINDIR)

