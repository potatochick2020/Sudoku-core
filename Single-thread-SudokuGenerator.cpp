#include "Single-thread-SudokuGenerator.h"

void single_thread_sudoku_generator()
{  
    std::cout<<"Single Thread Generator"<<std::endl;
    //connect to database
    const char* dir = R"(./Database/SudokuDatabase.db)";
    auto DB = DatabaseConnection(dir);
    DB.createTableIfNotExist(); 

    //Start time counting 
    auto t1 = std::chrono::high_resolution_clock::now();
    int successTask = 0;
    int failTask = 0;
    //generate and insert 100 sudoku
    for (int i = 0; i<90;i++){
        // generate a sudoku
         Sudoku sudoku;
        sudoku.initialize(); 
        string to_insert = sudoku.getFlattenBoard();
        // cout<<" Thread "<<x<<" : ";
        DB.insertData("INSERT INTO Sudoku (SudokuValue) Values ('"+to_insert+"');")==0?successTask++:failTask++; // uncomment the deleteData above to avoid duplicates
    }

    //End time counting 
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;

    //print used time
  std::cout << "\x1b[32m Used Time:" << ms_double.count() << "ms to complete "<<successTask<<" Success insertion and "<<failTask<<" Fail insertion \x1b[0m \n";

    //disconnect database
    DB.closeConnection();
    
}

