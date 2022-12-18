# Sudoku
A C++ library for generating, validating, solving, checking, etc Sudoku puzzle. 

# Installation 

```
clang++ -std="c++20" -o Multi-thread-SudokuGenerator Multi-thread-SudokuGenerator.cpp DataBase.cpp Sudoku.cpp Board.cpp -l sqlite3

clang++ -std="c++20" -o Single-thread-SudokuGenerator Single-thread-SudokuGenerator.cpp DataBase.cpp Sudoku.cpp Board.cpp -l sqlite3

clang++ -std="c++20" -o main main.cpp Multi-thread-SudokuGenerator.cpp Single-thread-SudokuGenerator.cpp DataBase.cpp Sudoku.cpp Board.cpp -l sqlite3
```

# To Do

finish threadsafe sql queue
put this in private of database connection

write test  
https://github.com/CS144/sponge/blob/lab1-startercode/CMakeLists.txt
https://cmake.org/cmake/help/book/mastering-cmake/chapter/Testing%20With%20CMake%20and%20CTest.html

# Doing this in concurrency 
# Special thanks

Speical thanks to めぐ in Leetcode Warrior community to provide help in fixing a bug when designing the algorithm of *SudokuSolution()* which return the number of unique solution that a sudoku board has.



