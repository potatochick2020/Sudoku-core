

#include "Sudoku.hpp" 
#include "DataBase.hpp"
#include <thread> 
#include <unistd.h>
#include <chrono>    
#include <vector> 
#include <atomic> 

//4 function for benchmarking and compare 
void generateSudokuAndInsertTask_use_ATOMIC( DatabaseConnection DB,atomic<int> &successTask,atomic<int> &failTask, int number_of_sudoku);
void generateSudokuAndInsertTask_use_MUTEX( DatabaseConnection DB, std::mutex &successTask_mutex, std::mutex &failTask_mutex, int &successTask, int &failTask, int number_of_sudoku);
void generateSudokuAndInsertTask_use_INT(int x,DatabaseConnection DB,vector<int> &successTask,vector<int> &failTask, int number_of_sudoku);

class SudokuGenerator {  
    protected: // protected is accessible by derived class
        DatabaseConnection DB;
    public:
        virtual void generate() = 0; //pure virtual function that need to be implemented in derived class
        virtual void getSuccessTask() = 0;
        virtual void getFailTask() = 0;
};

//template of successTask and failTask should be use
class SudokuGenerator_SingleThread : SudokuGenerator { 
    private:
        int successTask;
        int failTask;
    public: 
        void generate() override;
        void getSuccessTask() override;
        void getFailTask() override;
};

class SudokuGenerator_MultiThread_ATOMIC : SudokuGenerator { 
    private:
        atomic<int>  successTask;
        atomic<int>  failTask;
    public:
        void generate() override;
        void getSuccessTask() override;
        void getFailTask()override;
};

class SudokuGenerator_MultiThread_MUTEX : SudokuGenerator { 
    private:
        int successTask;
        int failTask;
    public:
        void generate() override;
        void getSuccessTask() override;
        void getFailTask() override;
};

class SudokuGenerator_MultiThread_INT : SudokuGenerator { 
    private:
        int successTask;
        int failTask;
    public:
        void generate() override;
        void getSuccessTask() override;
        void getFailTask() override;
};

