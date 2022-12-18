#include "Sudoku.h"
#include "DataBase.h"
#include <thread> 
#include <unistd.h>
#include <chrono>    
#include <vector> 
#include <atomic>   

void generateSudokuAndInsertTask_use_ATOMIC(int x,DatabaseConnection DB,atomic<int> &successTask,atomic<int> &failTask);
void generateSudokuAndInsertTask_use_MUTEX(int x,DatabaseConnection DB, std::mutex &successTask_mutex, std::mutex &failTask_mutex, int &successTask, int &failTask);
void generateSudokuAndInsertTask_use_INT(int x,DatabaseConnection DB,vector<int> &successTask,vector<int> &failTask);
void multi_thread_sudoku_generator();