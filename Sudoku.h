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
#include <numeric>
#include "Board.h"

#define SHUFFLE(x) shuffle(x.begin(), x.end(), mt19937{ random_device{}() });
#define CANDIDATE_ARRAY { 1, 2, 3, 4, 5, 6, 7, 8, 0 }

using namespace std;

class Sudoku : public Board
{
private:

	bool GenerateSudoku(void);
public:
	Sudoku(int boardHeight = 9, int boardWidth = 9);

	// default argument only in decleration
	void initialize(int difficulty = 3);

	//overloading for a Board::setBoard
	void setBoard(int, int, int);
	void setBoard(vector<vector<int>>);
	virtual void drawBoard();

	bool isCorrect(void);
	bool isComplete(void);
	bool isValid(void);
	bool isPlacable(int, int, int);

	int SudokuSolution(void);
};
