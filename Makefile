# Name of the binary
TARGET = build/game

# Compiler and options
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I/opt/homebrew/Cellar/sfml/3.0.1/include

# SFML libraries
LDFLAGS = -L/opt/homebrew/Cellar/sfml/3.0.1/lib -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRC_MAIN = src/main.cpp
SRC_MODEL = $(wildcard src/Engine/Model/*.cpp)
SRC_VIEW = $(wildcard src/Engine/View/*.cpp)
SRC_CONTROLLER = $(wildcard src/Engine/Controller/*.cpp)
SRC_UTILS = $(wildcard src/Utils/*.cpp)
SRC = $(SRC_MAIN) $(SRC_MODEL) $(SRC_VIEW) $(SRC_CONTROLLER) $(SRC_UTILS)

# Object files
OBJ = $(patsubst src/%.cpp,build/%.o,$(SRC))

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Generic compilation
build/%.o: src/%.cpp
	@mkdir -p $(dir $@)   # Create directories in build/ if needed
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf build
