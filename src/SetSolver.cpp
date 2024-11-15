#include "SetSolver.h"

void SetSolver::PopulateBoard(vector<string> skeletonBoard) {
    board.resize(boardSize, vector<SetSolverSquareSet>(boardSize));
    

    for (size_t row = 0; row < boardSize; ++row) {
        for (size_t col = 0; col < boardSize; ++col) {
            char cell = skeletonBoard[row][col];

            if (cell == '0') {
                board[row][col] = SetSolverSquareSet(0); // Empty black square
            } else if (cell == '*') {
                board[row][col] = SetSolverSquareSet(99); // Empty white square
            } else if (cell == '-') {
                if (col + 1 < boardSize) {
                    board[row][col] = SetSolverSquareSet(-(skeletonBoard[row][col + 1] - '0')); // Black square with number
                    ++col;
                }
            } else {
                board[row][col] = SetSolverSquareSet(cell - '0'); // White square with number
            }
            // Debugging output
            std::cout << "Populated Row: " << row << ", Col: " << col << ", Value: " << board[row][col].getValue() << std::endl;
        }
    }
    
}


int SetSolver::ReturnValue(size_t row, size_t col) {
    return board[row][col].getValue();
}

void SetSolver::Solve() {
    bool progress = true;
    int iteration = 0;

    while (progress) {
        progress = false;
        iteration++;
        std::cout << "Solve iteration: " << iteration << std::endl;

        for (size_t row = 0; row < boardSize; ++row) {
            for (size_t col = 0; col < boardSize; ++col) {
                std::cout << "Processing Row: " << row << ", Col: " << col << std::endl;

                if (board[row][col].isEmptyWhiteCell()) {
                    auto possibleValues = board[row][col].getPossibleValues();

                    std::cout << "Possible values for Row: " << row
                              << ", Col: " << col << " -> ";
                    for (int v : possibleValues) {
                        std::cout << v << " ";
                    }
                    std::cout << std::endl;

                    std::set<int> possibilities(possibleValues.begin(), possibleValues.end());

                    // Eliminate numbers in the same row
                    for (size_t c = 0; c < boardSize; ++c) {
                        possibilities.erase(board[row][c].getValue());
                    }

                    // Eliminate numbers in the same column
                    for (size_t r = 0; r < boardSize; ++r) {
                        possibilities.erase(board[r][col].getValue());
                    }

                    // Assign value if only one possibility remains
                    if (possibilities.size() == 1) {
                        int value = *possibilities.begin();
                        std::cout << "Assigning value " << value << " to Row: " << row
                                  << ", Col: " << col << std::endl;
                        board[row][col].setValue(value);
                        progress = true;
                    } else {
                        std::vector<int> updatedValues(possibilities.begin(), possibilities.end());
                        board[row][col].setPossibleValues(updatedValues);
                    }
                }
            }
        }
    }
}



void SetSolver::printBoard() {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell.getValue() == 99) {
                cout << "* ";
            } else {
                cout << cell.getValue() << " ";
            }
        }
        cout << "\n";
    }
}
