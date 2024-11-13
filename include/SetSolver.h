#ifndef SetSolver_h
#define SetSolver_h

#include <string>
#include <iostream>
#include <vector>
#include "SetSolverSquareSet.h"

using std::vector;
using std::string;

// Helper function to split strings by a delimiter without using <sstream>
vector<string> splitString(const string& str, char delimiter = ' ') {
    vector<string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != string::npos) {
        if (end != start) { // Avoid adding empty strings
            tokens.push_back(str.substr(start, end - start));
        }
        start = end + 1;
        end = str.find(delimiter, start);
    }

    if (start < str.length()) { // Add the last token
        tokens.push_back(str.substr(start));
    }

    return tokens;
}

class SetSolver
{
private:
    int boardSize = 9;
    vector<vector<SetSolverSquareSet>> board;

public:

    void PopulateBoard(vector<string> skeletonBoard)
    {
        if (skeletonBoard.size() != boardSize) {
            std::cerr << "Error: The board must have exactly " << boardSize << " rows.\n";
            return;
        }

        // Initialize the board
        board.assign(boardSize, vector<SetSolverSquareSet>(boardSize));

        for (int row = 0; row < boardSize; ++row) {
            string rowString = skeletonBoard[row];
            vector<string> cells = splitString(rowString);

            if (cells.size() != boardSize) {
                std::cerr << "Error: Row " << row << " does not have " << boardSize << " cells.\n";
                return;
            }

            for (int col = 0; col < boardSize; ++col) {
                string cell = cells[col];

                if (cell == "0") {
                    // Empty black square
                    board[row][col].cellValue = 0; // Using 0 to represent empty black square
                    board[row][col].set.clear();   // No possible values
                }
                else if (cell == "*") {
                    // Empty white square
                    board[row][col] = SetSolverSquareSet(); // Initializes with all possible values
                }
                else if (cell[0] == '-') {
                    // Black square with a hint (negative number)
                    int hint = std::stoi(cell);
                    board[row][col].setValue(hint); // Stores the hint value (negative)
                    board[row][col].set.clear();    // No possible values
                }
                else {
                    // Filled white square
                    int value = std::stoi(cell);
                    board[row][col].setValue(value); // Sets the fixed value
                }
            }
        }
    }

    int ReturnValue(size_t row, size_t col)
    {
        if (row >= boardSize || col >= boardSize) {
            return -1; // Out of bounds
        }

        return board[row][col].getValue();
    }

    void Solve()
    {
        initializePossibleValues();

        bool changesMade;
        do {
            changesMade = applyConstraints();
        } while (changesMade);

        if (!isBoardSolved()) {
            if (backtrackSolve()) {
                std::cout << "Solution Found:\n";
                printBoard();
            }
            else {
                std::cout << "No valid solution exists.\n";
            }
        }
        else {
            std::cout << "Board Solved!\n";
        }
    }

private:

    void initializePossibleValues()
    {
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                int cellValue = board[row][col].getValue();
                if (cellValue == -99) {
                    // Empty white square; possible values already initialized in constructor
                    // No action needed
                }
                else if (cellValue == 0 || cellValue < -1) {
                    // Empty black square or black square with a hint; no possible values
                    board[row][col].set.clear();
                }
                else if (cellValue > 0) {
                    // Filled white square; possible values set to the fixed value
                    board[row][col].setPossibleValues({ cellValue });
                }
            }
        }
    }

    bool applyConstraints()
    {
        bool changesMade = false;

        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                int cellValue = board[row][col].getValue();
                if (cellValue < 0 && cellValue != -99) {
                    // Hint cell (black square with a hint)
                    int hint = -cellValue;
                    // Remove the hint value from possible values in the same row and column
                    for (int i = 0; i < boardSize; ++i) {
                        if (i != col && board[row][i].removePossibleValue(hint)) {
                            changesMade = true;
                        }
                        if (i != row && board[i][col].removePossibleValue(hint)) {
                            changesMade = true;
                        }
                    }
                }
                else if (cellValue > 0) {
                    // Filled white square
                    int value = cellValue;
                    // Remove the value from possible values in the same row and column
                    for (int i = 0; i < boardSize; ++i) {
                        if (i != col && board[row][i].removePossibleValue(value)) {
                            changesMade = true;
                        }
                        if (i != row && board[i][col].removePossibleValue(value)) {
                            changesMade = true;
                        }
                    }
                }
            }
        }

        // Assign cells with only one possible value
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                if (board[row][col].isEmptyWhiteCell()) {
                    if (board[row][col].isSolved()) {
                        int value = board[row][col].getOnlyPossibleValue();
                        board[row][col].setValue(value);
                        changesMade = true;
                    }
                }
            }
        }

        return changesMade;
    }

    bool isBoardSolved() const
    {
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                if (board[row][col].isEmptyWhiteCell()) {
                    return false;
                }
            }
        }
        return true;
    }

    bool backtrackSolve()
    {
        int minPossibilities = 10; // More than the maximum possible
        int row = -1, col = -1;

        // Find the cell with the fewest possibilities
        for (int r = 0; r < boardSize; ++r) {
            for (int c = 0; c < boardSize; ++c) {
                if (board[r][c].isEmptyWhiteCell()) {
                    int possibilities = board[r][c].possibleValuesCount();
                    if (possibilities < minPossibilities) {
                        minPossibilities = possibilities;
                        row = r;
                        col = c;
                    }
                }
            }
        }

        // If no cells are left to fill, the board is solved
        if (row == -1 && col == -1) return true;

        // Attempt each possible value for the chosen cell
        auto currentPossibilities = board[row][col].getPossibleValues();
        for (int value : currentPossibilities) {
            // Make a copy of the board
            vector<vector<SetSolverSquareSet>> boardCopy = board;

            // Assign the value
            board[row][col].setValue(value);
            board[row][col].setPossibleValues({ value });

            // Apply constraints
            if (applyConstraints()) {
                if (backtrackSolve()) {
                    return true;
                }
            }

            // Revert changes
            board = boardCopy;
        }

        return false; // No valid solution found
    }

    void printBoard() const
    {
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                std::cout << board[row][col].getValue() << " ";
            }
            std::cout << "\n";
        }
        std::cout << "-------------------\n";
    }
};

#endif /* SetSolver_h */

