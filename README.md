# Sudoku
A C++ library for generating, validating, solving, checking, etc Sudoku puzzle. 

# Installation 
Build the project: 
```
mkdir build
cd build
cmake ..
make
./sudokugenerator
```

Rebuild the project
```
cd build
make clean
make
```

# Option

Can choose between multi-thread, single-thread in sudoku generation

Can choose between using atomic , using mutex and lock , using vector<int> and sum it to calculate total fail and success insertion during multi-thread mode

In `Mode.h`
 ```cpp
 
//choose 1 among 3 of it 
#define _use_ATOMIC 
#define _use_MUTEX
#define _use_INT

// Choose 1 among 2 of it 

//Single Thread
#define SINGLE_THREAD
//Multi thread
#define MULTI_THREAD
#ifdef MULTI_THREAD 
    #define NUMBER_OF_THREADS 6
#endif

 ```
# Special thanks

Speical thanks to めぐ in Leetcode Warrior community to provide help in fixing a bug when designing the algorithm of *SudokuSolution()* which return the number of unique solution that a sudoku board has.



