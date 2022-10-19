#include "Cli.h"
#include "Sudoku.h"

int run_cli(vector<string> args) {
    Sudoku sudoku;
    for (int i = 0; i < (int)args.size(); i++) {
        if (args[i] == "-i" || args[i] == "--initialize") {
            sudoku.initialize();
        } else if (args[i] == "-s" || args[i] == "--setBoard") {
            i++;
            if (i >= (int)args.size()) {
                return 1;
            }
            vector<vector<int>> board = vector<vector<int>>(9, vector<int>(9, 0));
            // Where the next will be added
            int pos = 0;
            for (char c : args[i]) {
                if ('0' <= c && c <= '9') {
                    // Convert to int
                    board[(int)pos/9][pos%9] = c - '0';
                    pos += 1;
                }
            }
            sudoku.setBoard(board);
        } else if (args[i] == "-c" || args[i] == "--isCorrect") {
            return sudoku.isCorrect();
        } else if (args[i] == "-C" || args[i] == "--isComplete") {
            return sudoku.isComplete();
        } else if (args[i] == "-v" || args[i] == "--isValid") {
            return sudoku.isValid();
        } else if (args[i] == "-p" || args[i] == "--print") {
            sudoku.drawBoard();
        } else if (args[i] == "-h" || args[i] == "--help") {
            cout << "Help: \n" <<
                    "  --initialize  -i      Initializes the board\n" <<
                    "  --setBoard    -s      Sets the board\n" <<
                    "  --isCorrect   -c      Returns if the board is correct\n" <<
                    "  --isComplete  -C      Returns if the board is complete\n" <<
                    "  --isValid     -v      Returns if the board is vaild\n" <<
                    "  --print       -p      Prints the board" <<
                    "  --help        -h      Prints this" << endl;
            return 0;
        } else {
            cout << "Unknown arg: " << args[i] << endl;
            return 1;
        }
    }
    return 0;
}
