# ==========================================================
# 2D Engine CMakeLists.txt (Mac/Homebrew SFML 3.0+)
# ==========================================================

cmake_minimum_required(VERSION 3.16)
project(2DEngine)

# ----------------------------------------------------------
# Utiliser C++17
# ----------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------------------------------
# Inclure les dossiers de headers
# ----------------------------------------------------------
include_directories(src)
include_directories("/opt/homebrew/Cellar/sfml/3.0.1/include")

# ----------------------------------------------------------
# Lister tous les fichiers cpp du moteur
# ----------------------------------------------------------
file(GLOB_RECURSE SRC
    "src/*.cpp"
)

# ----------------------------------------------------------
# Créer l'exécutable
# ----------------------------------------------------------
add_executable(game ${SRC})

# ----------------------------------------------------------
# Lier les bibliothèques SFML directement
# ----------------------------------------------------------
target_link_libraries(game
    "/opt/homebrew/Cellar/sfml/3.0.1/lib/libsfml-graphics.dylib"
    "/opt/homebrew/Cellar/sfml/3.0.1/lib/libsfml-window.dylib"
    "/opt/homebrew/Cellar/sfml/3.0.1/lib/libsfml-system.dylib"
)

# ----------------------------------------------------------
# Options supplémentaires (warnings)
# ----------------------------------------------------------
target_compile_options(game PRIVATE -Wall -Wextra)
