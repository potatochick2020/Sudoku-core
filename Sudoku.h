#pragma once
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <stack>
#include <map>
#include "Board.h"

using namespace std;

class Sudoku : Board
{
private:

	bool GenerateSudoku(void);
public:
	Sudoku(int boardHeight = 9, int boardWidth = 9);

	// default argument only in decleration
	void initialize(int difficulty = 3);

	void setBoard(int, int, int);
	void setBoard(vector<vector<int>>);
	vector<vector<int>> getBoard(void);

	bool isCorrect(void);
	bool isComplete(void);
	bool isValid(void);
	bool isPlacable(int, int, int);

	int SudokuSolution(void);
	virtual void DrawBoard();
};
