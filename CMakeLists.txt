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
# SFML
# ----------------------------------------------------------
set(SFML_ROOT "/opt/homebrew/Cellar/sfml/3.0.1")
include_directories(${SFML_ROOT}/include)

# ----------------------------------------------------------
# Fichiers source du moteur (tous les .cpp dans src/, sans main.cpp)
# ----------------------------------------------------------
file(GLOB_RECURSE ENGINE_SRC "src/*.cpp")
list(FILTER ENGINE_SRC EXCLUDE REGEX "src/main.cpp")

add_library(engine STATIC ${ENGINE_SRC})

# Inclure tous les headers du moteur automatiquement
file(GLOB_RECURSE ENGINE_HEADERS "src/*.hpp" "src/*.h")
set(ENGINE_HEADER_DIRS "")
foreach(f ${ENGINE_HEADERS})
    get_filename_component(dir ${f} DIRECTORY)
    list(APPEND ENGINE_HEADER_DIRS ${dir})
endforeach()
list(REMOVE_DUPLICATES ENGINE_HEADER_DIRS)
target_include_directories(engine PUBLIC ${ENGINE_HEADER_DIRS})

# ----------------------------------------------------------
# Lier SFML
# ----------------------------------------------------------
target_link_libraries(engine
    ${SFML_ROOT}/lib/libsfml-graphics.dylib
    ${SFML_ROOT}/lib/libsfml-window.dylib
    ${SFML_ROOT}/lib/libsfml-system.dylib
)

# ----------------------------------------------------------
# Exécutable principal (jeu)
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
# Fichiers de tests
# ----------------------------------------------------------
file(GLOB_RECURSE TEST_SRC "tests/*.cpp")

# Créer l'exécutable des tests uniquement si des fichiers existent
if(TEST_SRC)
    add_executable(tests ${TEST_SRC})
    target_link_libraries(tests PRIVATE engine Catch2::Catch2WithMain)
    target_include_directories(tests PRIVATE
        ${ENGINE_HEADER_DIRS}
        ${catch2_SOURCE_DIR}/single_include
    )
    target_compile_options(tests PRIVATE -Wall -Wextra)
endif()
