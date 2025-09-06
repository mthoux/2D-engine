#include "MapGenerator.hpp"
#include <cstdlib>
#include <ctime>

std::vector<std::vector<int>> generateMap(int width, int height) {
    std::vector<std::vector<int>> map(height, std::vector<int>(width, 0));

    // Initialiser le générateur de nombres aléatoires
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            map[y][x] = std::rand() % 3;  // valeurs 0, 1, 2
        }
    }

    return map;
}