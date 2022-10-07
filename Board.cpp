#include "Board.h"
Board::Board(int boardHeight, int boardWidth) {
	this->boardHeight = boardHeight;
	this->boardWidth = boardWidth;
	this->board = vector<vector<int>>(this->boardHeight, vector<int>(this->boardWidth, 0));
}