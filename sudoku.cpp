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
        vector<vector<int>> BoardAns = vector<vector<int>>(9, vector<int>(9, 0));
        vector<vector<int>> BoardOriginal = vector<vector<int>>(9, vector<int>(9, 0));
    public:
        void initialize(int);
        vector<vector<int>> getBoard(void);
        void setBoard(int, int, int);
        void setBoard(vector<vector<int>>);
        //bool isComplete(void); // check whether a board had been completed, completed if there is no '0' in board
        bool isCorrect(void);  // check a board is correct
       
};
 bool isValid(vector<vector<int>>& board) {
    unordered_set<int> set;
    int tar = 0;
    //check horizontal
    for (int i = 0;i<9;i++){
        set.clear();
        for (int j=0;j<9;j++){
            if (board[i][j]!=tar && set.find(board[i][j])!=set.end()){
                return false;
            } else {
                set.insert(board[i][j]);
            }
        }
    }
    //check vertical
    for (int i = 0;i<9;i++){
        set.clear();
        for (int j=0;j<9;j++){
            if (board[j][i]!=tar && set.find(board[j][i])!=set.end()){
                return false;
            } else {
                set.insert(board[j][i]);
            }
        }
    }
    //check 3x3 box
    for (int i = 0;i<3;i++){
        for (int j=0;j<3;j++){
            set.clear();
            for (int k=0;k<3;k++){
                for (int l=0;l<3;l++){
                    if (board[i*3+k][j*3+l]!=tar && set.find(board[i*3+k][j*3+l])!=set.end()){
                        return false;
                    } else {
                        set.insert(board[i*3+k][j*3+l]);
                    }
                    
                }
                
            }
            
        }
    }

    return true;    
}

bool isComplete(vector<vector<int>> Board)
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
    return Board == BoardAns;
}

vector<vector<int>> Sudoku::getBoard(void)
{
    return Board;
};

bool isPlacable(int i, int j, vector<vector<int>> Board, int value)
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



bool SolveSudoku(vector<vector<int>> &Board)
{
    while (isComplete(Board) == false)
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
                        if (isPlacable(row, col, Board, number))
                        {
                            // if (true){
                            Board[row][col] = number;
                            if (SolveSudoku(Board))
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

int SudokuSolution(vector<vector<int>> &Board, int &ans )
{
     
    for (int row = 0; row < 9; row++)
    {
 
        for (int col = 0; col < 9; col++)
        {
 
            if (Board[row][col] == 0)
            {
                vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                for (int number : numbers)
                { 
                    if (isPlacable(row, col, Board, number))
                    {
                        Board[row][col] = number; 
                        
                        if (isComplete(Board) && isValid(Board)){
                            cout<<"this is complete and correct"<<row<<" "<<col<<" "<<number<<endl;
                            ans++;
                        } else {
                            SudokuSolution(Board,ans);
                        }
                        Board[row][col] = 0;
                        
                    }
                }
            }
        }
    } 
    return ans;
}

// set<vector<vector<int>>> SudokuSolution(vector<vector<int>> &Board, set<vector<vector<int>>> &ans )
// {
     
//     for (int row = 0; row < 9; row++)
//     {

//         for (int col = 0; col < 9; col++)
//         {

//             if (Board[row][col] == 0)
//             {
//                 vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//                 for (int number : numbers)
//                 { 
//                     if (isPlacable(row, col, Board, number))
//                     {
//                         Board[row][col] = number; 
//                         cout<<"Place "<<row<<" "<<col<<" "<<number<<endl;
//                         if (isComplete(Board)){
//                             cout<<"Complete and Valid: Row"<<row<<" | Col "<<col<<" |Value"<<number<<endl;
//                             ans.insert(Board);
//                         } else {
//                             SudokuSolution(Board,ans);
//                         }
//                         Board[row][col] = 0;
//                         cout<<"Remove "<<row<<" "<<col<<" "<<number<<endl;
                        
//                     }
//                 }
//             }
//         }
//     } 
//     return ans;
// }

void Sudoku::initialize(int difficulty = 3)
{
    SolveSudoku(Board); 
    
};
int main()
{
    Sudoku soduku;
    soduku.initialize(1); 
    vector<vector<int>>temp =  soduku.getBoard();
    // set<vector<vector<int>>> ans ;
    int ans = 0;
    cout<<"empty row 1 | col 1 | value "<<temp[1][1]<<endl;
    temp[1][1] = 0;
    cout<<"empty row 1 | col 2 | value "<<temp[1][2]<<endl;
    temp[1][2] = 0;
    cout<<"empty row 1 | col 3 | value "<<temp[1][3]<<endl;
    temp[1][3] = 0;
    SudokuSolution(temp,ans);
    
    // temp[3] = {0,0,0,0,0,0,0,0,0};
    // temp[4] = {0,0,0,0,0,0,0,0,0};
    // temp[5] = {0,0,0,0,0,0,0,0,0};
    // SudokuSolution(temp,ans);
    // cout<<"ans:"<<ans.size()<<endl;
    cout<<"ans:"<<ans<<endl;
    for (auto x : soduku.getBoard())
    {
        for (auto y : x)
        {
            cout << y << " | ";
        }
        cout << endl
             << "--------------------------------" << endl;
    }
}

 