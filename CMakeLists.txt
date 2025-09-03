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
# Créer l'exécutable principal
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
# Créer l'exécutable des tests
# ----------------------------------------------------------
# Liste tous les fichiers cpp dans tests/
file(GLOB_RECURSE TEST_SRC
    "tests/*.cpp"
)

# Crée l'exécutable tests avec tous les fichiers trouvés
add_executable(tests ${TEST_SRC})

# Lier Catch2
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

# Include directories
target_include_directories(tests PRIVATE src)  # tes headers
target_include_directories(tests PRIVATE ${catch2_SOURCE_DIR}/single_include)  # Catch2
