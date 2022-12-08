#include "Sudoku.h"
#include "DataBase.h"
#include <thread> 
#include <unistd.h>
#include <chrono>    

int main()
{  
    //connect to database
    const char* dir = R"(./Database/SudokuDatabase.db)";
    DatabaseConnection::DatabaseConnection(dir)

    //Start time counting 
    auto t1 = std::chrono::high_resolution_clock::now();

    //generate and insert 500 sudoku
    for (int i = 0; i<500;i++){
        // generate a sudoku
        Sudoku sudoku.initialize(); 
        string to_insert = sudoku.getFlattenBoard();
        cout<<"\x1b[32m  Insert in main Thread : \x1b[0m"<<to_insert<<endl; 
        DatabaseConnection::insertData(dir,"INSERT INTO Sudoku (SudokuValue) Values ('"+to_insert+"');"); // uncomment the deleteData above to avoid duplicates
    }

    //End time counting 
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;

    //print used time
    std::cout << "\x1b[32m Used Time:" << ms_double.count() << "ms \x1b[0m \n";

    //disconnect database
    DatabaseConnection::~DatabaseConnection() 
	return 0;
    
}

