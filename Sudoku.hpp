#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <stack>
#include <map>
#include <numeric>
 

#define SHUFFLE(x) shuffle(x.begin(), x.end(), mt19937{ random_device{}() });
#define CANDIDATE_ARRAY { 1, 2, 3, 4, 5, 6, 7, 8, 0 }

using namespace std;

class Sudoku  
{
private:
	bool GenerateSudoku(void);
	std::vector<std::vector<int>> board;
public: 
	Sudoku(){
		initialize();
	};
	void initialize(int difficulty = 3); 
	void drawBoard();
	bool isCorrect(void);
	bool isComplete(void);
	bool isValid(void);
	bool isPlacable(int, int, int);
	int SudokuSolution(void);
	const std::vector<std::vector<int>>& getBoard();
	const std::string& getFlattenBoard();

	//set board with a complete board
	void setBoard(const std::vector<std::vector<int>>& newBoard);

	//set board with only one cell
	void setBoard(int, int, int); 
};

