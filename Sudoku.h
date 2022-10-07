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

using namespace std;

class Sudoku
{
private:
	vector<vector<int>> board = vector<vector<int>>(9, vector<int>(9, 0));
	bool GenerateSudoku(void);
public:
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
};
