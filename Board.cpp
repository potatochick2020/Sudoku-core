#include "Board.h"
Board::Board(int boardHeight, int boardWidth) {
	this->boardHeight = boardHeight;
	this->boardWidth = boardWidth;
	this->board = vector<vector<int>>(this->boardHeight, vector<int>(this->boardWidth, 0));
}

void Board::setBoard(vector<vector<int>> newBoard) {
	board = newBoard;
}

vector<vector<int>> Board::getBoard(void)
{
	return board;
};