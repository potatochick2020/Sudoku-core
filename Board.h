#pragma once
#include <vector>
using namespace std;

// Abstract Class since it has an abstract function
class Board
{
protected:
	vector<vector<int>> board;
	int boardWidth, boardHeight;

	Board(int, int);
	// Abstaract function that must be defined by children
	virtual void drawBoard() = 0;

public:
	vector<vector<int>> getBoard();
	void setBoard(vector<vector<int>> newBoard);
};

