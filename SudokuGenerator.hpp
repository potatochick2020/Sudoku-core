

#include "Sudoku.hpp" 
#include "DataBase.hpp"
#include <thread> 
#include <unistd.h>
#include <chrono>    
#include <vector> 
#include <atomic> 

//4 function for benchmarking and compare
void single_thread_sudoku_generator();
void multi_thread_sudoku_generator_using_ATOMIC();
void multi_thread_sudoku_generator_using_MUTEX();
void multi_thread_sudoku_generator_using_INT();


void generateSudokuAndInsertTask_use_ATOMIC( DatabaseConnection DB,atomic<int> &successTask,atomic<int> &failTask, int number_of_sudoku);
void generateSudokuAndInsertTask_use_MUTEX( DatabaseConnection DB, std::mutex &successTask_mutex, std::mutex &failTask_mutex, int &successTask, int &failTask, int number_of_sudoku);
void generateSudokuAndInsertTask_use_INT(int x,DatabaseConnection DB,vector<int> &successTask,vector<int> &failTask, int number_of_sudoku);

Class SudokuGenerator {  
    virtual void generate();
}

Class SudokuGenerator_SingleThread : SudokuGenerator { 
    void generate() override;
}

Class SudokuGenerator_SingleThread : SudokuGenerator { 
    void generate() override;
}

Class SudokuGenerator_SingleThread : SudokuGenerator { 
    void generate() override;
}

Class SudokuGenerator_SingleThread : SudokuGenerator { 
    void generate() override;
}