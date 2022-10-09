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
        void set_board(vector<vector<int>>);
        //bool is_complete(void); // check whether a board had been completed, completed if there is no '0' in board
        bool is_correct(void);  // check a board is correct
        bool is_complete(void);  // check a board is correct
        bool is_valid(void);  // check a board is correct
        bool is_placeable(int,int,int);
       
};

bool Sudoku::is_valid() {
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

bool Sudoku::is_complete()
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

bool Sudoku::is_correct(void)
{ 
    return is_valid() && is_complete();
}

vector<vector<int>> Sudoku::get_board(void)
{
    return Board;
};

bool Sudoku::is_placeable(int row, int col, int value)
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
    while (is_complete() == false)
    {
        for (int row = 0; row < 9; row++)
        {

            for (int col = 0; col < 9; col++)
            {

                if (Board[row][col] == 0)
                {
                    vector<int> candidates = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                    std::shuffle(candidates.begin(), candidates.end(), std::mt19937{std::random_device{}()});
                    for (int value : candidates)
                    {
                        if (is_placeable(row, col, value))
                        {
                            // if (true){
                            Board[row][col] = value;
                            if (Sudoku::generate_sudoku())
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
                vector<int> candidates = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                for (int value : candidates)
                { 
                    if (is_placeable(row, col, value))
                    {
                        Board[row][col] = value; 
                        
                        if (is_correct()){ 
                            ans++;
                        } else {
                            ans += Sudoku::sudoku_solution();
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
    vector<int> row_candidates = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    std::shuffle(row_candidates.begin(), row_candidates.end(), std::mt19937{std::random_device{}()});
    vector<int> col_candidates = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    std::shuffle(col_candidates.begin(), col_candidates.end(), std::mt19937{std::random_device{}()});
    pair<pair<int,int>,int> backup = {{row_candidates[0],col_candidates[0]},Board[row_candidates[0]][col_candidates[0]]};
    Board[row_candidates[0]][col_candidates[0]] = 0;
    
    int attempt = 0;
    while (attempt<difficulty){
        
        vector<int> row_candidates = {1, 2, 3, 4, 5, 6, 7, 8, 0};
        std::shuffle(row_candidates.begin(), row_candidates.end(), std::mt19937{std::random_device{}()});
        vector<int> col_candidates = {1, 2, 3, 4, 5, 6, 7, 8, 0};
        std::shuffle(col_candidates.begin(), col_candidates.end(), std::mt19937{std::random_device{}()});
        backup = {{row_candidates[0],col_candidates[0]},Board[row_candidates[0]][col_candidates[0]]};
        Board[row_candidates[0]][col_candidates[0]] = 0;
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

    vector<vector<int>>grid = sudoku.get_board();
    int N=grid.size();
    for (int row = 0; row < N; row++){
      for (int col = 0; col < N; col++){
         if(col == 3 || col == 6)
            cout << " | ";
         cout << grid[row][col] <<" ";
      }
      if(row == 2 || row == 5){
         cout << endl;
         for(int i = 0; i<N; i++)
            cout << "---";
      }
      cout << endl;
   }
    
}
