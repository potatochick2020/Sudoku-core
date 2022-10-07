#include "Sudoku.h"

bool Sudoku::isValid() {
	unordered_set<int> set;
	int tar = 0;
	//check horizontal
	for (int i = 0; i < 9; i++) {
		set.clear();
		for (int j = 0; j < 9; j++) {
			if (board[i][j] != tar && set.find(board[i][j]) != set.end()) {
				return false;
			}
			else {
				set.insert(board[i][j]);
			}
		}
	}
	//check vertical
	for (int i = 0; i < 9; i++) {
		set.clear();
		for (int j = 0; j < 9; j++) {
			if (board[j][i] != tar && set.find(board[j][i]) != set.end()) {
				return false;
			}
			else {
				set.insert(board[j][i]);
			}
		}
	}
	//check 3x3 box
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			set.clear();
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					if (board[i * 3 + k][j * 3 + l] != tar && set.find(board[i * 3 + k][j * 3 + l]) != set.end()) {
						return false;
					}
					else {
						set.insert(board[i * 3 + k][j * 3 + l]);
					}

				}

			}

		}
	}

	return true;
}

bool Sudoku::isComplete()
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] == 0)
				return false;
		}
	}
	return true;
}

bool Sudoku::isCorrect(void)
{
	return isValid() && isComplete();
}

vector<vector<int>> Sudoku::getBoard(void)
{
	return board;
};

bool Sudoku::isPlacable(int i, int j, int value)
{
	for (int idx = 0; idx < 9; idx++)
	{

		if (board[i][idx] == value)
			return false;
		if (board[idx][j] == value)
			return false;
		if (board[(i / 3) * 3 + (idx / 3)][(j / 3) * 3 + (idx % 3)] == value)
			return false;
	}
	return true;
}

void Sudoku::setBoard(vector<vector<int>> newBoard) {
	board = newBoard;
}

void Sudoku::setBoard(int row, int col, int value) {
	board[row][col] = value;
}

bool Sudoku::GenerateSudoku()
{
	while (isComplete() == false)
	{
		for (int row = 0; row < 9; row++)
		{

			for (int col = 0; col < 9; col++)
			{

				if (board[row][col] == 0)
				{
					vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
					shuffle(numbers.begin(), numbers.end(), mt19937{ random_device{}() });
					for (int number : numbers)
					{
						if (isPlacable(row, col, number))
						{
							// if (true){
							board[row][col] = number;
							if (Sudoku::GenerateSudoku())
								return true;
							board[row][col] = 0;
						}
					}
					return false;
				}
			}
		}
	}
	return true;
}

int Sudoku::SudokuSolution()
{
	int ans = 0;
	vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (int row = 0; row < 9; row++)
	{

		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] == 0)
			{
				for (int number : numbers)
				{
					if (isPlacable(row, col, number))
					{
						board[row][col] = number;

						if (isCorrect())
							ans++;
						else
							ans += Sudoku::SudokuSolution();

						board[row][col] = 0;

					}
				}
				return ans;
			}

		}
	}
	return 0;
}

void Sudoku::initialize(int difficulty)
{
	GenerateSudoku();
	vector<int> rowsCandidates = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
	shuffle(rowsCandidates.begin(), rowsCandidates.end(), mt19937{ random_device{}() });
	vector<int> colsCandidates = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
	shuffle(colsCandidates.begin(), colsCandidates.end(), mt19937{ random_device{}() });
	pair<pair<int, int>, int> backup = { {rowsCandidates[0],colsCandidates[0]},board[rowsCandidates[0]][colsCandidates[0]] };
	board[rowsCandidates[0]][colsCandidates[0]] = 0;

	int attempt = 0;
	while (attempt < difficulty) {

		vector<int> rowsCandidates = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
		shuffle(rowsCandidates.begin(), rowsCandidates.end(), mt19937{ random_device{}() });
		vector<int> colsCandidates = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
		shuffle(colsCandidates.begin(), colsCandidates.end(), mt19937{ random_device{}() });
		backup = { {rowsCandidates[0],colsCandidates[0]},board[rowsCandidates[0]][colsCandidates[0]] };
		board[rowsCandidates[0]][colsCandidates[0]] = 0;
		if (SudokuSolution() > 1) {
			board[backup.first.first][backup.first.second] = backup.second;
			attempt++;
		}
	}
};