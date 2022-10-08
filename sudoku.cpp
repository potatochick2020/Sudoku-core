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
static bool generate_sudoku(vector<vector<int>> &Board);

class Sudoku
{
    private:
        vector<vector<int>> Board = vector<vector<int>>(9, vector<int>(9, 0)); 
        bool generate_sudoku(void);
        

    public:
        void initialize(int);
        int sudoku_solution(void);
        vector<vector<int>> get_board(void);
        void set_board(int, int, int);
        void SetBoard(vector<vector<int>>);
        //bool isComplete(void); // check whether a board had been completed, completed if there is no '0' in board
        bool IsCorrect(void);  // check a board is correct
        bool IsComplete(void);  // check a board is correct
        bool IsValid(void);  // check a board is correct
        bool IsPlacable(int,int,int);
       
};

bool Sudoku::IsValid() {
    unordered_set<int> store_values;
    int target = 0;
    //check horizontal
    for (int row = 0; row < 9; row++){
        store_values.clear();
        for (int col = 0;  col < 9; col++){
            if (Board[row][col]!=target && store_values.find(Board[row][col])!=store_values.end()){
                return false;
            } else {
                store_values.insert(Board[row][col]);
            }
        }
    }
    //check vertical
    for (int row = 0; row < 9 ; row++){
        store_values.clear();
        for (int col = 0;  col < 9; col++){
            if (Board[col][row]!=target && store_values.find(Board[col][row])!=store_values.end()){
                return false;
            } else {
                store_values.insert(Board[col][row]);
            }
        }
    }
    //check 3x3 box
    for (int row = 0; row < 3; row++){
        for (int col = 0; col < 3; col++){
            store_values.clear();
            for (int row_start =0; row_start<3 ; row_start++){
                for (int col_start=0; col_start<3; col_start++){
                    if (Board[row*3+row_start][col*3+col_start]!=target && store_values.find(Board[row*3+row_start][col*3+col_start])!=store_values.end()){
                        return false;
                    } else {
                        store_values.insert(Board[row*3+row_start][col*3+col_start]);
                    }        
                }
            } 
        }
    }
    return true;    
}

bool Sudoku::IsComplete()
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

bool Sudoku::IsCorrect(void)
{ 
    return IsValid() && IsComplete();
}

vector<vector<int>> Sudoku::get_board(void)
{
    return Board;
};

bool Sudoku::IsPlacable(int row, int col, int value)
{
    for (int index = 0; index < 9; index++)
    {
        if (Board[row][index] == value)
            return false;
        if (Board[index][col] == value)
            return false;
        if (Board[(row / 3) * 3 + (index / 3)][(col / 3) * 3 + (index % 3)] == value)
            return false;
    }
    return true;
}

void Sudoku::set_board(vector<vector<int>> newBoard){
    Board = newBoard;
}

void Sudoku::set_board(int row, int col, int value){
    Board[row][col] = value;
}

bool Sudoku::generate_sudoku()
{
    while (IsComplete() == false)
    {
        for (int row = 0; row < 9; row++)
        {

            for (int col = 0; col < 9; col++)
            {

                if (Board[row][col] == 0)
                {
                    vector<int> possible_values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                    std::shuffle(possible_values.begin(), possible_values.end(), std::mt19937{std::random_device{}()});
                    for (int value : possible_values)
                    {
                        if (IsPlacable(row, col, value))
                        {
                            // if (true){
                            Board[row][col] = value;
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

int Sudoku::sudoku_solution()
{
    int ans = 0;
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (Board[row][col] == 0)
            {
                vector<int> possible_values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                for (int value : possible_values)
                { 
                    if (IsPlacable(row, col, value))
                    {
                        Board[row][col] = value; 
                        
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
    generate_sudoku(); 
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
        if (sudoku_solution() > 1){
            Board[backup.first.first][backup.first.second] = backup.second;
            attempt++;
        }
    }
};

int main()
{
    Sudoku sudoku;
    sudoku.initialize(); 

    for (auto row : sudoku.get_board())
    {
        for (auto val : row)
        {
            cout << val << " | ";
        }
        cout << endl
             << "--------------------------------" << endl;
    } 
} 
