cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the compiler to clang++
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

# Add the source files
add_executable(sudokugenerator main.cpp Multi-thread-SudokuGenerator.cpp Single-thread-SudokuGenerator.cpp DataBase.cpp Sudoku.cpp Board.cpp)

# Link the sqlite3 library
target_link_libraries(sudokugenerator sqlite3)