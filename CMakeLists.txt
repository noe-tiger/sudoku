project(sudoku)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-std=c++17 -fPIC")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(
  "${CMAKE_SOURCE_DIR}/inc"
)

file(
  GLOB_RECURSE
  sources_sudoku
  src/main.cpp
  src/window.cpp
  src/game.cpp
  src/board.cpp
)

add_executable(sudoku ${sources_sudoku})
target_link_libraries(sudoku ${CONAN_LIBS})
