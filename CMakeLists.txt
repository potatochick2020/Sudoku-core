cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the compiler to clang++
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

# Add the source files
add_executable(sudokugenerator main.cpp SudokuGenerator.cpp DataBase.cpp Sudoku.cpp ) 
add_executable(sudokugenerator_test test.cpp SudokuGenerator.cpp DataBase.cpp Sudoku.cpp ) 

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)
# Link the sqlite3 and benchmark library
target_link_libraries(sudokugenerator sqlite3 benchmark::benchmark GTest::gtest GTest::gtest_main)
target_link_libraries(sudokugenerator_test sqlite3 benchmark::benchmark GTest::gtest GTest::gtest_main)