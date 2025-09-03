# ==========================================================
# 2D Engine Makefile
# ==========================================================

# Name of the binary
TARGET = build/game

# Compiler and options
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Isrc -I/opt/homebrew/Cellar/sfml/3.0.1/include

# SFML libraries
LDFLAGS = -L/opt/homebrew/Cellar/sfml/3.0.1/lib -lsfml-graphics -lsfml-window -lsfml-system

# Source files (recursive)
SRC_MAIN = src/main.cpp
SRC_MODEL = $(shell find src/Engine/Model -name "*.cpp")
SRC_VIEW = $(shell find src/Engine/View -name "*.cpp")
SRC_CONTROLLER = $(shell find src/Engine/Controller -name "*.cpp")
SRC_UTILS = $(shell find src/Utils -name "*.cpp")

SRC = $(SRC_MAIN) $(SRC_MODEL) $(SRC_VIEW) $(SRC_CONTROLLER) $(SRC_UTILS)

# Object files
OBJ = $(patsubst src/%.cpp,build/%.o,$(SRC))

# ==========================================================
# Default rule
# ==========================================================
all: $(TARGET)

# ==========================================================
# Linking
# ==========================================================
$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

# ==========================================================
# Generic compilation rule
# ==========================================================
build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ==========================================================
# Clean build files
# ==========================================================
clean:
	rm -rf build

# ==========================================================
# Phony targets
# ==========================================================
.PHONY: all clean
