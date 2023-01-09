# Sudoku
A C++ library for generating, validating, solving, checking, etc Sudoku puzzle. 

# Installation 
Build the project: 
```
mkdir build
cd build
cmake ..
make
//run the generator brenchmark
./sudokugenerator
//run the test
sudokugenerator_test
```

Rebuild the project
```
cd build
make clean
make
```


# Algorithm to generate a sudoku 
This algorithm is referenced and further improved from [101 computing](https://www.101computing.net/sudoku-generator-algorithm/), which the original implementation does not guarantee the sudoku had only 1 unique solution.

**bool Sudoku::GenerateSudoku()**  
generate a sudoku board with all number filled. The board will be a completed board without any blank to filled.
```cpp
bool Sudoku::GenerateSudoku()
{
	vector<int> numbers(9);

	while (isComplete() == false)
	{
		for (int row = 0; row < 9; row++)
		{

			for (int col = 0; col < 9; col++)
			{

				if (board[row][col] == 0)
				{
					// fills out the numbers vector with numbers from 1 -> numbers.size()
					iota(begin(numbers), end(numbers), 1);
					SHUFFLE(numbers);
					for (int number : numbers)
					{
						if (isPlacable(row, col, number)) // if it is valid to place a number at the location.
						{ 
							board[row][col] = number;
							if (Sudoku::GenerateSudoku())
                             //recursion function to call itself and place further number
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
```
**int Sudoku::SudokuSolution()**
return the number of unique solution that this sudoku board has as an int. 

```cpp
int Sudoku::SudokuSolution()
{
	int ans = 0;
	vector<int> numbers(9);

	// fills out the numbers vector with numbers from 1 -> numbers.size()
	iota(begin(numbers), end(numbers), 1);
	for (int row = 0; row < 9; row++)
	{

		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] == 0)
			{
				for (int number : numbers)
				{
					if (isPlacable(row, col, number)) // if it is valid to place a number at the location.
					{
						board[row][col] = number;

						if (isCorrect())
							ans++;
						else
                            //recursion function to call itself and place further number
							ans += Sudoku::SudokuSolution();

						board[row][col] = 0;
					}
				}
                //return number of solutions that this sudoku has
				return ans;
			}
		}
	}
	return 0;
}
```
**void Sudoku::initialize(int difficulty)** 

```cpp
void Sudoku::initialize(int difficulty)
{
	GenerateSudoku();
	vector<int> rowsCandidates = CANDIDATE_ARRAY;
	SHUFFLE(rowsCandidates);
	vector<int> colsCandidates = CANDIDATE_ARRAY;
	SHUFFLE(colsCandidates);
	pair<pair<int, int>, int> backup = {{rowsCandidates[0], colsCandidates[0]}, board[rowsCandidates[0]][colsCandidates[0]]};
    //backup store the value of the next attemp 
	board[rowsCandidates[0]][colsCandidates[0]] = 0;

	int attempt = 0;
    // with the more higher difficulty, the algorithm will try to get away more number from the board (if the board has less number provided, it is more difficult)
	while (attempt < difficulty)
	{
		rowsCandidates = CANDIDATE_ARRAY;
		SHUFFLE(rowsCandidates);

		colsCandidates = CANDIDATE_ARRAY;
		SHUFFLE(colsCandidates);

		backup = {{rowsCandidates[0], colsCandidates[0]}, board[rowsCandidates[0]][colsCandidates[0]]};
		board[rowsCandidates[0]][colsCandidates[0]] = 0;
		if (SudokuSolution() > 1)
		{
			board[backup.first.first][backup.first.second] = backup.second;
			attempt++;
		}
	}
};
```

# Object-Oriented PRogramming
There are 2 Class throughout the project

## **Sudoku** class

## **Sudoku-generator** class
Can choose between multi-thread, single-thread in sudoku generation

Can choose between using atomic , using mutex and lock , using vector<int> and sum it to calculate total fail and success insertion during multi-thread mode


# Special thanks

Speical thanks to めぐ in Leetcode Warrior community to provide help in fixing a bug when designing the algorithm of *SudokuSolution()* which return the number of unique solution that a sudoku board has.



