#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <map>

// candidates should be data stucture of    map<pair<int,int>,vector<int>>


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

void Sudoku::initialize(int difficulty = 3)
{
    SolveSudoku(Board);
    while (difficulty>0){

    }
};

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

bool SolveSudokuFindNumberOfAnswer(vector<vector<int>> &Board ,map<pair<int,int>,vector<int>> CandidatesList, vector<pair<int,int>> &EmptyCellsList ,int &ans, int &count)
{
    // for (auto Candidates : CandidatesList){
    //     count ++ ;
    //     int row = Candidates.first.first;
    //     int col = Candidates.first.second;
    //     visited.push({row,col});
    //     for (auto Candidate : Candidates.second){
    //         Board[row][col] = Candidate;
    //         SolveSudokuFindNumberOfAnswer()
    //     }
    // }
    while (isComplete(Board) == false)
    {
        for (int row = 0; row < 9; row++)
        {

            for (int col = 0; col < 9; col++)
            {
                 
                if (Board[row][col] == 0)
                { 
                    
                    for (int number : CandidatesList[{row,col}])
                    {
                        if (isPlacable(row, col, Board, number))
                        {
                            Board[row][col] = number;
                            if (isComplete(Board)){ 
                                if (isCorrect(Board)) ans++;
                                //Board[row][col] = 0; 
                                // for (int i = 0;i<count;i++){
                                //     auto ele = EmptyCellsList[EmptyCellsList.size()-1-i];
                                //     Board[ele.first][ele.second] = 0;
                                // }

                                
                            } 
                            SolveSudokuFindNumberOfAnswer();
                            Board[row][col] = number;
                        }
                    } 
                }
                
            }
                
        }
    }
    return ans;
}

//return number of solution of the sudoku
int SudokuSolution(vector<vector<int>> Board)
{
    vector<vector<vector<int>>> Candidates (9, vector<vector<int>>(9, vector<int> (9,1)));
    vector<vector<int>> solutionList;
    set<vector<vector<int>>> solution;
    int ans;
    stack<pair<int,int>> vistied;
    //find all candidates of each cell;
    vector<pair<int,int>>  EmptyCellsList

    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (Board[row][col] != 0)
            {
                for(int counter = 0;counter<9;counter++)
                    Candidates[row][col][counter] = 0;
                int val = Board[row][col];
                for (int i = 0; i< 9;i++){
                    Candidates[row][i][val] = 0;
                    Candidates[i][col][val] = 0;      
                    Candidates[(row / 3) * 3 + (i / 3)][(col / 3) * 3 + (i % 3)][val] = 0;
                }
            }  else {
                EmptyCellsList.push_back({row,col});
            }
        }
    }

    map<pair<int,int>,vector<int>> CandidatesList;

    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (Board[row][col] != 0)
            {
                vector<int> cans;

                for(int i = 0;i<9;i++){
                    if (Candidates[row][col][i] == 1) cans.push_back(i);
                }
                    
                 CandidatesList[{row,col}] = cans;
            } 
        }
    }
    vector<vector<int>> temp;

 label:

    while (isComplete(temp) == false)
    //if it is not fill in 
    {
        for (int row = 0; row < 9; row++)
        {
            for (int col = 0; col < 9; col++)
            {

                if (Board[row][col] == 0)
                {
                    for (auto number : Candidates[row][col])
                    {
                        //if filled
                        
                        if (isPlacable(row, col, Board, number))
                        {
                            // if (true){ 
                            Board[row][col] = number;
                            if (isComplete(Board)){
                                if (SolveSudoku(Board)) 
                                ans++;
                                Board[row][col] = 0; 
                            } 
                            
                           
                        } 
                        //if not filled
                    goto label;
                    } 
                }
            }
        }
    }
    
    return ans;
}

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

 