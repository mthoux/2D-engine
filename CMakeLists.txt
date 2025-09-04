# ==========================================================
# 2D Engine CMakeLists.txt (Mac/Homebrew SFML 3.0+)
# ==========================================================

cmake_minimum_required(VERSION 3.16)
project(2DEngine)

# ----------------------------------------------------------
# C++17
# ----------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------------------------------
# Include directories
# ----------------------------------------------------------
include_directories(src)
include_directories("/opt/homebrew/Cellar/sfml/3.0.1/include")

# ----------------------------------------------------------
# Lister tous les fichiers cpp du moteur (sans main.cpp)
# ----------------------------------------------------------
file(GLOB_RECURSE ENGINE_SRC
    "src/*.cpp"
)
list(FILTER ENGINE_SRC EXCLUDE REGEX "src/main.cpp")  # exclut le main du jeu

# ----------------------------------------------------------
# Créer une librairie statique pour le moteur
# ----------------------------------------------------------
add_library(engine STATIC ${ENGINE_SRC})
target_include_directories(engine PUBLIC src)

# Lier SFML à la librairie moteur
target_link_libraries(engine
    "/opt/homebrew/Cellar/sfml/3.0.1/lib/libsfml-graphics.dylib"
    "/opt/homebrew/Cellar/sfml/3.0.1/lib/libsfml-window.dylib"
    "/opt/homebrew/Cellar/sfml/3.0.1/lib/libsfml-system.dylib"
)

# ----------------------------------------------------------
# Créer l'exécutable principal (jeu)
# ----------------------------------------------------------
add_executable(game src/main.cpp)
target_link_libraries(game PRIVATE engine)
target_compile_options(game PRIVATE -Wall -Wextra)

# ==========================================================
# Partie Catch2 pour les tests
# ==========================================================
include(FetchContent)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.0
)

FetchContent_MakeAvailable(catch2)

# ----------------------------------------------------------
# Lister tous les fichiers cpp dans tests/
# ----------------------------------------------------------
file(GLOB_RECURSE TEST_SRC
    "tests/*.cpp"
)

# ----------------------------------------------------------
# Créer l'exécutable des tests (Catch2)
# ----------------------------------------------------------
add_executable(tests ${TEST_SRC})
target_link_libraries(tests PRIVATE engine Catch2::Catch2WithMain)

# Inclure les headers
target_include_directories(tests PRIVATE src)
target_include_directories(tests PRIVATE ${catch2_SOURCE_DIR}/single_include)

# Warnings pour tests
target_compile_options(tests PRIVATE -Wall -Wextra)
