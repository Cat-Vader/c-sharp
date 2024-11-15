#include <memory>
#include "../include/SetSolver.h"

#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::unique_ptr;
using std::vector;

int main() {
    int retval = 0;

    // Create a unique pointer to SetSolver
    unique_ptr<SetSolver> board(new SetSolver());

    // Define the skeleton board
    vector<std::string> skeletonBoard{
        "00**0-31*0",
        "*****0**0",
        "7*003*-5**",
        "**05**7**",
        "*0**0*6-9*",
        "4***650**",
        "*2-8**00**",
        "-23*0*****",
        "043-608*0-1"
    };

    // Populate the board and solve it
    board->PopulateBoard(skeletonBoard);
    board->Solve();

    // Expected result for verification
    vector<vector<int>> skeletonAnswer{
        {0, 0, 6, 7, 0, -3, 1, 2, 0},
        {6, 7, 5, 8, 4, 0, 2, 3, 0},
        {7, 8, 0, 0, 3, 4, -5, 1, 2},
        {8, 9, 0, 5, 2, 6, 7, 4, 3},
        {5, 0, 1, 2, 0, 7, 6, -9, 4},
        {4, 1, 2, 3, 6, 5, 0, 8, 7},
        {3, 2, -8, 4, 5, 0, 0, 7, 6},
        {-2, 3, 4, 0, 7, 9, 8, 6, 5},
        {0, 4, 3, -6, 0, 8, 9, 0, -1}
    };

    // Compare solved board with the expected result
    for (size_t row = 0; row < 9; ++row) {
        for (size_t col = 0; col < 9; ++col) {
            if ((board->ReturnValue(row, col)) != (skeletonAnswer[row][col])) {
                cout << "Failed: when checking row: " << row << " col: " << col << "\n";
                retval++;
            }
        }
    }

    // Print the solved board
    std::cout << "Solved Board:" << std::endl;
    for (size_t row = 0; row < 9; ++row) {
        for (size_t col = 0; col < 9; ++col) {
            std::cout << board->ReturnValue(row, col) << " ";
        }
        std::cout << std::endl;
    }

    return retval;
}
