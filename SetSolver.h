#ifndef SetSolver_h
#define SetSolver_h

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "SetSolverSquareSet.h"

using std::vector;
using std::string;

// Helper function to split strings by a delimiter
std::vector<std::string> splitString(const std::string& str, char delimiter = ' ') {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

class SetSolver
{
private:
    int boardRows;
    int boardCols;
    vector<vector<SetSolverSquareSet>> possibleValues;
    vector<vector<int>> board;

public:
    bool PopulateBoard(const vector<string>& skeletonBoard) {
        boardRows = skeletonBoard.size();
        if (boardRows != 9) {
            std::cerr << "Error: The board must have exactly 9 rows.\n";
            return false;
        }

        boardCols = splitString(skeletonBoard[0]).size();
        if (boardCols != 9) {
            std::cerr << "Error: Each row must have exactly 9 cells.\n";
            return false;
        }

        // Initialize board and possibleValues
        board.assign(boardRows, vector<int>(boardCols, 0));
        possibleValues.assign(boardRows, vector<SetSolverSquareSet>(boardCols));

        for (int row = 0; row < boardRows; ++row) {
            std::string rowString = skeletonBoard[row];
            std::vector<std::string> cells = splitString(rowString);

            std::cout << "Processing Row " << row << ": " << rowString << "\n";
            std::cout << "Number of cells: " << cells.size() << "\n";

            if (cells.size() != boardCols) {
                std::cerr << "Error: Row " << row << " does not have " << boardCols << " cells.\n";
                return false;
            }

            for (int col = 0; col < boardCols; ++col) {
                std::string cell = cells[col];

                if (cell == "0") {
                    board[row][col] = 0; // Empty black square
                }
                else if (cell == "*") {
                    board[row][col] = 99; // Empty white square
                }
                else if (cell[0] == '-') {
                    // Handle negative numbers for black squares with hints
                    board[row][col] = std::stoi(cell); // Convert to a negative number
                }
                else {
                    // Handle positive numbers for filled white squares
                    board[row][col] = std::stoi(cell);
                }

                // Debug output for each cell
                std::cout << "board[" << row << "][" << col << "] = " << board[row][col] << std::endl;
            }
        }
        return true;
    }

    int ReturnValue(size_t row, size_t col) const {
        if (row >= boardRows || col >= boardCols) return -1; // Out of bounds
        int cellValue = board[row][col];
        if (cellValue == 0) return 0;       // Empty black square
        if (cellValue == 99) return 99;     // Empty white square
        return cellValue;                   // Filled white square or black square with a number
    }

    void Solve() {
        initializePossibleValues();

        bool changesMade;
        do {
            changesMade = applyConstraints();
            std::cout << "After applyConstraints:\n";
            printBoard();
        } while (changesMade);

        if (!isBoardSolved()) {
            std::cout << "Starting backtrackSolve...\n";
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

    // Printing the Board for debugging
    void printBoard() const {
        for (int row = 0; row < boardRows; ++row) {
            for (int col = 0; col < boardCols; ++col) {
                std::cout << board[row][col] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "-------------------\n";
    }

private:
    void initializePossibleValues() {
        for (int row = 0; row < boardRows; ++row) {
            for (int col = 0; col < boardCols; ++col) {
                if (board[row][col] == 99) {
                    possibleValues[row][col] = SetSolverSquareSet(); // Initialize all values (1-9)
                }
                else if (board[row][col] > 0) {
                    possibleValues[row][col].set = { board[row][col] }; // Fixed value for filled squares
                }
            }
        }
    }

    bool applyConstraints() {
        bool changesMade = false;

        for (int row = 0; row < boardRows; ++row) {
            for (int col = 0; col < boardCols; ++col) {
                if (board[row][col] < 0) { // Hint cell
                    int hint = -board[row][col];
                    for (int i = 0; i < boardCols; ++i) {
                        if (i != col) {
                            if (possibleValues[row][i].removeValue(hint)) changesMade = true;
                        }
                    }
                    for (int i = 0; i < boardRows; ++i) {
                        if (i != row) {
                            if (possibleValues[i][col].removeValue(hint)) changesMade = true;
                        }
                    }
                }
                else if (board[row][col] > 0) { // Filled white square
                    int value = board[row][col];
                    for (int i = 0; i < boardCols; ++i) {
                        if (i != col) {
                            if (possibleValues[row][i].removeValue(value)) changesMade = true;
                        }
                    }
                    for (int i = 0; i < boardRows; ++i) {
                        if (i != row) {
                            if (possibleValues[i][col].removeValue(value)) changesMade = true;
                        }
                    }
                }
            }
        }

        // Assign cells with only one possible value
        for (int row = 0; row < boardRows; ++row) {
            for (int col = 0; col < boardCols; ++col) {
                if (board[row][col] == 99) { // Empty white cell
                    if (possibleValues[row][col].isSolved()) {
                        board[row][col] = possibleValues[row][col].getValue();
                        changesMade = true;
                    }
                }
            }
        }

        // Debug: Print possible values after constraints
        for (int row = 0; row < boardRows; ++row) {
            for (int col = 0; col < boardCols; ++col) {
                if (board[row][col] == 99) { // Only print for empty white cells
                    std::cout << "Possible values for cell (" << row << ", " << col << "): ";
                    for (int val : possibleValues[row][col].set) {
                        std::cout << val << " ";
                    }
                    std::cout << "\n";
                }
            }
        }
        std::cout << "-------------------\n";

        return changesMade;
    }

    bool isBoardSolved() const {
        for (int row = 0; row < boardRows; ++row) {
            for (int col = 0; col < boardCols; ++col) {
                if (board[row][col] == 99) return false; // Unsolved white cell
            }
        }
        return true;
    }

    bool backtrackSolve() {
        int minPossibilities = 10; // Assumes values are 1-9; 10 is an impossible maximum.
        int row = -1, col = -1;

        // Find the cell with the fewest possibilities
        for (int r = 0; r < boardRows; ++r) {
            for (int c = 0; c < boardCols; ++c) {
                if (board[r][c] == 99) { // Empty cell
                    int possibilities = possibleValues[r][c].set.size();
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
        auto currentPossibilities = possibleValues[row][col].set;
        for (int value : currentPossibilities) {
            // Make copies of board and possibleValues
            vector<vector<int>> boardCopy = board;
            vector<vector<SetSolverSquareSet>> possibleValuesCopy = possibleValues;

            // Assign the value
            board[row][col] = value;
            possibleValues[row][col].set = { value };

            // Apply constraints
            if (applyConstraints()) {
                if (backtrackSolve()) {
                    return true;
                }
            }

            // Revert changes
            board = boardCopy;
            possibleValues = possibleValuesCopy;
        }

        return false; // No valid solution found for this configuration
    }
};

#endif /* SetSolver_h */
