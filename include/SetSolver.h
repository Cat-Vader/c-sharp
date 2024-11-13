#ifndef SetSolver_h
#define SetSolver_h

#include <string>
#include <iostream>
#include <vector>
#include "SetSolverSquareSet.h"

using std::vector;
using std::string;

class SetSolver {
private:
    int boardSize = 9;
    vector<vector<SetSolverSquareSet>> board;

    // Helper: Find minimum value in a vector
    int findMin(const vector<int>& numbers) const {
        int min = numbers[0];
        for (size_t i = 1; i < numbers.size(); ++i) {
            if (numbers[i] < min) {
                min = numbers[i];
            }
        }
        return min;
    }

    // Helper: Find maximum value in a vector
    int findMax(const vector<int>& numbers) const {
        int max = numbers[0];
        for (size_t i = 1; i < numbers.size(); ++i) {
            if (numbers[i] > max) {
                max = numbers[i];
            }
        }
        return max;
    }

    // Helper: Count occurrences of a value in a vector
    int countOccurrences(const vector<int>& numbers, int value) const {
        int count = 0;
        for (size_t i = 0; i < numbers.size(); ++i) {
            if (numbers[i] == value) {
                ++count;
            }
        }
        return count;
    }

    // Check if the numbers form an uninterrupted set
    bool isSetUninterrupted(const vector<int>& numbers) const {
        if (numbers.empty()) return true;

        int min = findMin(numbers);
        int max = findMax(numbers);
        int expectedCount = max - min + 1;

        if (numbers.size() != static_cast<size_t>(expectedCount)) {
            return false;
        }

        for (int val = min; val <= max; ++val) {
            if (countOccurrences(numbers, val) != 1) {
                return false;
            }
        }
        return true;
    }

    // Apply initial constraints from hints and filled cells
    void applyInitialConstraints() {
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                int cellValue = board[row][col].getValue();

                if (cellValue < 0) { // Black square with a hint
                    int hint = -cellValue;
                    for (int i = 0; i < boardSize; ++i) {
                        if (board[row][i].isEmptyWhiteCell()) {
                            board[row][i].removeValue(hint);
                        }
                        if (board[i][col].isEmptyWhiteCell()) {
                            board[i][col].removeValue(hint);
                        }
                    }
                } else if (cellValue > 0 && cellValue != 99) { // Filled white square
                    for (int i = 0; i < boardSize; ++i) {
                        if (board[row][i].isEmptyWhiteCell()) {
                            board[row][i].removeValue(cellValue);
                        }
                        if (board[i][col].isEmptyWhiteCell()) {
                            board[i][col].removeValue(cellValue);
                        }
                    }
                }
            }
        }
    }

    // Solve the board using backtracking
    bool solveBoard() {
        int row = -1, col = -1;
        if (!findEmptyCell(row, col)) {
            return true; // Board is solved
        }

        vector<int> possibleValues = board[row][col].getPossibleValues();
        for (int num : possibleValues) {
            if (isValidPlacement(row, col, num)) {
                board[row][col].setValue(num);
                if (solveBoard()) {
                    return true;
                }
                board[row][col].setValue(99); // Backtrack
                board[row][col].setPossibleValues(possibleValues);
            }
        }

        return false;
    }

    // Find an empty cell (returns true if found)
    bool findEmptyCell(int& row, int& col) const {
        for (int r = 0; r < boardSize; ++r) {
            for (int c = 0; c < boardSize; ++c) {
                if (board[r][c].isEmptyWhiteCell() && !board[r][c].isSolved()) {
                    row = r;
                    col = c;
                    return true;
                }
            }
        }
        return false;
    }

    // Check if placing a number at (row, col) is valid
    bool isValidPlacement(int row, int col, int num) const {
        for (int i = 0; i < boardSize; ++i) {
            if (board[row][i].getValue() == num || board[i][col].getValue() == num) {
                return false;
            }
        }

        vector<int> rowCompartment = collectCompartmentNumbers(row, col, /*isRow=*/true, num);
        if (!isSetUninterrupted(rowCompartment)) {
            return false;
        }

        vector<int> colCompartment = collectCompartmentNumbers(row, col, /*isRow=*/false, num);
        if (!isSetUninterrupted(colCompartment)) {
            return false;
        }

        return true;
    }

    // Collect numbers in a compartment
    vector<int> collectCompartmentNumbers(int row, int col, bool isRow, int num) const {
        vector<int> compartmentNumbers;

        int start = isRow ? col : row;
        int end = start;

        while (start > 0 && board[isRow ? row : start - 1][isRow ? start - 1 : col].getValue() != 0) {
            --start;
        }

        while (end < boardSize - 1 && board[isRow ? row : end + 1][isRow ? end + 1 : col].getValue() != 0) {
            ++end;
        }

        for (int i = start; i <= end; ++i) {
            int val = board[isRow ? row : i][isRow ? i : col].getValue();
            if (val > 0 && val != 99) {
                compartmentNumbers.push_back(val);
            }
        }

        compartmentNumbers.push_back(num);
        return compartmentNumbers;
    }

public:
    // Populate the board from the skeleton board
    void populateBoard(const vector<string>& skeletonBoard) {
        board.resize(boardSize, vector<SetSolverSquareSet>(boardSize));

        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                char cell = skeletonBoard[row][col];
                if (cell == '*') {
                    board[row][col] = SetSolverSquareSet();
                } else if (cell == '0') {
                    board[row][col] = SetSolverSquareSet(0);
                } else if (cell == '-') {
                    int hint = -(skeletonBoard[row][++col] - '0');
                    board[row][col] = SetSolverSquareSet(hint);
                } else {
                    int value = cell - '0';
                    board[row][col] = SetSolverSquareSet(value);
                }
            }
        }
    }

    // Solve the board
    void solve() {
        applyInitialConstraints();
        solveBoard();
    }

    // Print the board
    void printBoard() const {
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                int val = board[row][col].getValue();
                if (val == 99) {
                    std::cout << "* ";
                } else if (val == 0) {
                    std::cout << "0 ";
                } else {
                    std::cout << val << " ";
                }
            }
            std::cout << "\n";
        }
        std::cout << "-------------------\n";
    }

    // Return the value of a cell
    int returnCellValue(int row, int col) const {
        return board[row][col].getValue();
    }
};

#endif /* SetSolver_h */
