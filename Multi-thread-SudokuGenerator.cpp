#include "Sudoku.h"
#include "DataBase.h"
#include <thread> 
#include <unistd.h>
#include <chrono>    
#include <vector>   

void generateSudokuAndInsertTask(int x,DatabaseConnection DB){
    for (int i = 0; i<25;i++){ 
        Sudoku sudoku;
        sudoku.initialize(); 
        string to_insert = sudoku.getFlattenBoard();
        cout<<" Thread "<<x<<" : ";
        DB.insertData("INSERT INTO Sudoku (SudokuValue) Values ('"+to_insert+"');"); // uncomment the deleteData above to avoid duplicates
    }
}

int main()
{
    //connect to database
    const char* dir = R"(./Database/SudokuDatabase.db)";
    auto DB = DatabaseConnection(dir);
    DB.createTableIfNotExist();
    sleep(5);
    //Start time counting 
    auto t1 = std::chrono::high_resolution_clock::now();

    std::cout << "\x1b[32m Start helpers... \x1b[0m" << std::endl; 

    //create vector to hold thread
    vector<std::thread> threadList; 
 
    //create thread and push to vector
    //generate and insert 125 sudoku each thread, 125 * 4 = 500 sudoku in total
    for (int i = 0;i<4;i++){
        threadList.push_back(std::thread(generateSudokuAndInsertTask,i,DB));
    }   

    for (auto& th : threadList) {
        th.join();
    } 

    std::cout << "\x1b[32m All helpers to finish... \x1b[0m" << std::endl; 

    //End time counting 
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;

    //print used time
    std::cout << "\x1b[32m Used Time:" << ms_double.count() << "ms \x1b[0m \n";

    //disconnect database
    DB.~DatabaseConnection();

	return 0;
}

