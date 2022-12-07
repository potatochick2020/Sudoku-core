#include "Sudoku.h"
#include "DataBase.h"
#include <thread> 
#include <unistd.h>
void generateSudokuAndInsertTask(int x){
    while (true){
        // generate a sudoku
        Sudoku sudoku;
        sudoku.initialize();
        // sudoku.drawBoard();
        //check board;
        // auto b = sudoku.getBoard();
        
        // for (int i = 0 ; i< 9;i++){
        //     for (int j = 0; j < 9 ;j++){
        //         cout<<b[i][j];
        //     }
        // }
        // cout<<endl;

        //flatten it 
        string to_insert = sudoku.getFlattenBoard();
        cout<<"Insert in Thread "<<x<<" : "<<to_insert<<endl;
        //insert into sql  
        const char* dir = R"(./Database/SudokuDatabase.db)";
    
        // createDB(dir);
        // createTable(dir); 
        insertData(dir,"INSERT INTO Sudoku (SudokuValue) Values ('"+to_insert+"');"); // uncomment the deleteData above to avoid duplicates
        // selectData(dir);
    
    }

}
int main()
{
    vector<std::thread> vectorOfThreads;
    std::cout << "starting first helper...\n";
    std::thread th1(generateSudokuAndInsertTask,1);
    std::thread th2(generateSudokuAndInsertTask,2);
    std::thread th3(generateSudokuAndInsertTask,3);
    std::thread th4(generateSudokuAndInsertTask,4);  
  
 
    std::cout << "waiting for helpers to finish..." << std::endl;
    th1.join();
    std::cout << "help1!\n";
    th2.join();
    th3.join();
    th4.join();
    std::cout << "help2!\n";
    std::cout << "done!\n";
	return 0;
    
}

