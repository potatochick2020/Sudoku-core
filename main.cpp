#include "Sudoku.h" 
#include "Mode.h"
#include "Multi-thread-SudokuGenerator.h"
#include "Single-thread-SudokuGenerator.h"
int main()
{
	#ifdef MULTI_THREAD 
		multi_thread_sudoku_generator();
	#elif defined(SINGLE_THREAD)
		single_thread_sudoku_generator();
	#endif 
}

