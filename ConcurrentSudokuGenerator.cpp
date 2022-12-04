#include "Sudoku.h"
#include "DataBase.h"
int main()
{
    //generate a sudoku
    Sudoku sudoku;
	sudoku.initialize();
	sudoku.drawBoard();
    //check board;
    auto b = sudoku.getBoard();
    cout<<" Suduku exprected ";
    for (int i = 0 ; i< 9;i++){
        for (int j = 0; j < 9 ;j++){
            cout<<b[i][j];
        }
    }
    cout<<endl;
    //flatten it 
    string to_insert = sudoku.getFlattenBoard();
    cout<<"to_insert :"<<to_insert<<endl;
    //insert into sql  
    const char* dir = R"(./Database/SudokuDatabase.db)";
 
	createDB(dir);
	createTable(dir); 
	insertData(dir,"INSERT INTO Sudoku (SudokuValue) Values ('"+to_insert+"');"); // uncomment the deleteData above to avoid duplicates
	selectData(dir);

	return 0;
    
}

