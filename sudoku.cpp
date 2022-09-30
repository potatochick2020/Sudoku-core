#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

using namespace std;

 
static bool generateSudoku(vector<vector<int>> &Board);

class Sudoku
{
    private:
        vector<vector<int>> Board = vector<vector<int>>(9, vector<int>(9, 0));
        vector<vector<int>> BoardAns = vector<vector<int>>(9, vector<int>(9, 0));

    public:
        void initialize(int);
        vector<vector<int>> getBoard(void);
        void setBoard(int, int, int);
        void setBoard(vector<vector<int>>);
        bool isComplete(void);
        bool isCorrect(void);
};

bool Sudoku::isComplete(void)
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

bool valid(int i, int j, vector<vector<int>> Board, int value)
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

void Sudoku::initialize(int difficulty = 3)
{
    generateSudoku(Board);
};

bool generateSudoku(vector<vector<int>> &Board)
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
                        if (valid(row, col, Board, number))
                        {
                            // if (true){
                            Board[row][col] = number;
                            if (generateSudoku(Board))
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

//return number of solution of the sudoku
// int solveSudoku(vector<vector<int>> &Board)
// {
//     vector<vector<vector<int>>> Candidates (9, vector<vector<int>>(9, vector<int> (9,1)));
//     vector<vector<int>> solutionList;
//     vector<int> solution;
//     for (int row = 0; row < 9; row++)
//     {
//         for (int col = 0; col < 9; col++)
//         {
//             if (Board[row][col] != 0)
//             {
//                 int val = Board[row][col];
//                 for (int i = 0; i< 9;i++){
//                     Candidates[row][i][val] = 0;
//                     Candidates[i][col][val] = 0;      
//                     Candidates[(row / 3) * 3 + (i / 3)][(col / 3) * 3 + (i % 3)][val] = 0;
//                 }
//             }
//         }
//     }



//     while (checkBoard(Board) == false)
//     {
//         for (int row = 0; row < 9; row++)
//         {

//             for (int col = 0; col < 9; col++)
//             {

//                 if (Board[row][col] == 0)
//                 {
//                     for (int number = 1 ; number <= 9 ; number++ )
//                     {
//                         if (valid(row, col, Board, number))
//                         {
//                             // if (true){
//                             solution.push_back(number);
//                             Board[row][col] = number;
//                             if (solveSudoku(Board))
//                                 return true;
//                             Board[row][col] = 0;
//                             solution.pop_back();
//                         }
//                     }
//                     return false;
//                 }
//             }
//         }
//     }
    
//     return solutionList.size();
// }

int main()
{
    Sudoku soduku;
    soduku.initialize();
    soduku.initialize(1);
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