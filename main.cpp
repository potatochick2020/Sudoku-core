#include "Sudoku.h"
#include "Cli.h"

int main(int argc, char *argv[])
{
    if (argc > 1) {
        vector<string> args(argv + 1, argv + argc);
        return run_cli(args);
    }
	Sudoku sudoku;
	sudoku.initialize();
	sudoku.drawBoard();
}

