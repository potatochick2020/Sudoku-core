#include "Board.h"
#include <iostream>
#include <sstream>  
Board::Board(int boardHeight, int boardWidth) {
	this->boardHeight = boardHeight;
	this->boardWidth = boardWidth;
	this->board = vector<vector<int>>(this->boardHeight, vector<int>(this->boardWidth, 0));
}

void Board::setBoard(vector<vector<int>> newBoard) {
	this->board = newBoard;
}

vector<vector<int>> Board::getBoard(void)
{
	return this->board;
};

string Board::getFlattenBoard(void)
{
	string s = ""; 
	std::stringstream ss;
	for (auto rowdata : this->board){ 
		for (auto coldata : rowdata){
			ss<<coldata; 
		}  
	} 
	ss >> s;
	return s;
};