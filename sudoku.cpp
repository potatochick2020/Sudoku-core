#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <stack>
#include <map>

 


using namespace std;

//static bool checkBoard(vector<vector<int>> Board);
static bool generateSudoku(vector<vector<int>> &Board);

class Sudoku
{
    private:
        vector<vector<int>> Board = vector<vector<int>>(9, vector<int>(9, 0)); 
        bool GenerateSudoku(void);
        

    public:
        void initialize(int);
        int SudokuSolution(void);
        vector<vector<int>> getBoard(void);
        void setBoard(int, int, int);
        void setBoard(vector<vector<int>>);
        //bool isComplete(void); // check whether a board had been completed, completed if there is no '0' in board
        bool isCorrect(void);  // check a board is correct
        bool isComplete(void);  // check a board is correct
        bool isValid(void);  // check a board is correct
        bool isPlacable(int,int,int);
       
};

bool Sudoku::isValid() {
    unordered_set<int> set;
    int tar = 0;
    //check horizontal
    for (int i = 0;i<9;i++){
        set.clear();
        for (int j=0;j<9;j++){
            if (Board[i][j]!=tar && set.find(Board[i][j])!=set.end()){
                return false;
            } else {
                set.insert(Board[i][j]);
            }
        }
    }
    //check vertical
    for (int i = 0;i<9;i++){
        set.clear();
        for (int j=0;j<9;j++){
            if (Board[j][i]!=tar && set.find(Board[j][i])!=set.end()){
                return false;
            } else {
                set.insert(Board[j][i]);
            }
        }
    }
    //check 3x3 box
    for (int i = 0;i<3;i++){
        for (int j=0;j<3;j++){
            set.clear();
            for (int k=0;k<3;k++){
                for (int l=0;l<3;l++){
                    if (Board[i*3+k][j*3+l]!=tar && set.find(Board[i*3+k][j*3+l])!=set.end()){
                        return false;
                    } else {
                        set.insert(Board[i*3+k][j*3+l]);
                    }
                    
                }
                
            }
            
        }
    }

    return true;    
}

bool Sudoku::isComplete()
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (Board[row][col] == 0)
                return false;
        }
    }
    return true;
}

bool Sudoku::isCorrect(void)
{ 
    return isValid() && isComplete();
}

vector<vector<int>> Sudoku::getBoard(void)
{
    return Board;
};

bool Sudoku::isPlacable(int i, int j, int value)
{
    for (int idx = 0; idx < 9; idx++)
    {

        if (Board[i][idx] == value)
            return false;
        if (Board[idx][j] == value)
            return false;
        if (Board[(i / 3) * 3 + (idx / 3)][(j / 3) * 3 + (idx % 3)] == value)
            return false;
    }
    return true;
}

void Sudoku::setBoard(vector<vector<int>> newBoard){
    Board = newBoard;
}

void Sudoku::setBoard(int row, int col, int value){
    Board[row][col] = value;
}

bool Sudoku::GenerateSudoku()
{
    while (isComplete() == false)
    {
        for (int row = 0; row < 9; row++)
        {

            for (int col = 0; col < 9; col++)
            {

                if (Board[row][col] == 0)
                {
                    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                    std::shuffle(numbers.begin(), numbers.end(), std::mt19937{std::random_device{}()});
                    for (int number : numbers)
                    {
                        if (isPlacable(row, col, number))
                        {
                            // if (true){
                            Board[row][col] = number;
                            if (Sudoku::GenerateSudoku())
                                return true;
                            Board[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
    }
    return true;
}

int Sudoku::SudokuSolution()
{
    int ans = 0;
    for (int row = 0; row < 9; row++)
    {
 
        for (int col = 0; col < 9; col++)
        {
 
            if (Board[row][col] == 0)
            {
                vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                for (int number : numbers)
                { 
                    if (isPlacable(row, col, number))
                    {
                        Board[row][col] = number; 
                        
                        if (isCorrect()){ 
                            ans++;
                        } else {
                            ans += Sudoku::SudokuSolution();
                        }
                        Board[row][col] = 0;
                        
                    }
                } 
                return ans;
            } 
           
        }
    } 
   return 0;
}

void Sudoku::initialize(int difficulty = 3)
{
    GenerateSudoku(); 
    vector<int> rowsCandidates = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    std::shuffle(rowsCandidates.begin(), rowsCandidates.end(), std::mt19937{std::random_device{}()});
    vector<int> colsCandidates = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    std::shuffle(colsCandidates.begin(), colsCandidates.end(), std::mt19937{std::random_device{}()});
    pair<pair<int,int>,int> backup = {{rowsCandidates[0],colsCandidates[0]},Board[rowsCandidates[0]][colsCandidates[0]]};
    Board[rowsCandidates[0]][colsCandidates[0]] = 0;
    
    int attempt = 0;
    while (attempt<difficulty){
        
        vector<int> rowsCandidates = {1, 2, 3, 4, 5, 6, 7, 8, 0};
        std::shuffle(rowsCandidates.begin(), rowsCandidates.end(), std::mt19937{std::random_device{}()});
        vector<int> colsCandidates = {1, 2, 3, 4, 5, 6, 7, 8, 0};
        std::shuffle(colsCandidates.begin(), colsCandidates.end(), std::mt19937{std::random_device{}()});
        backup = {{rowsCandidates[0],colsCandidates[0]},Board[rowsCandidates[0]][colsCandidates[0]]};
        Board[rowsCandidates[0]][colsCandidates[0]] = 0;
        if (SudokuSolution() > 1){
            Board[backup.first.first][backup.first.second] = backup.second;
            attempt++;
        }
    }
};
int main()
{
    Sudoku sudoku;
    sudoku.initialize(); 

    for (auto row : sudoku.getBoard())
    {
        for (auto val : row)
        {
            cout << val << " | ";
        }
        cout << endl
             << "--------------------------------" << endl;
    } 
    
    
}

 