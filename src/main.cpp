#include <iostream>
#include <memory>
#include "SetSolver.h"

using std::cout;
using std::unique_ptr;
using std::cout;
using std::cerr;
using std::unique_ptr;

// Function to run the test case
int runTestCase() {
    int retval = 0;

    unique_ptr<SetSolver> board(new SetSolver());

    // Define the puzzle with empty cells as 0 or *
    vector<string> skeletonBoard{
        "0 0 6 7 0 -3 1 2 0",
        "6 7 5 8 4 0 2 3 0",
        "7 8 0 0 3 4 -5 1 2",
        "8 9 0 5 2 6 7 4 3",
        "5 0 1 2 0 7 6 -9 4",
        "4 1 2 3 6 5 0 8 7",
        "3 2 -8 4 5 0 0 7 6",
        "-2 3 4 0 7 9 8 6 5",
        "0 4 3 -6 0 8 9 0 -1"
    };

    // Populate the board
    if (!board->PopulateBoard(skeletonBoard)) {
        cerr << "Failed to populate the board. Please check the skeletonBoard format.\n";
        return 1;
    }

    // Solve the puzzle
    board->Solve();

    // Define the expected solution
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

    // Compare the solver's output with the expected answer
    for (size_t row = 0; row < 9; ++row)
    {
        for (size_t col = 0; col < 9; ++col)
        {
            if ((board->ReturnValue(row, col)) != (skeletonAnswer[row][col]))
            {
                cout << "Test Case Failed: when checking row: " << row << " col: " << col << "\n";
                retval++;
            }
        }
    }

    // Optionally, print the solved board
    cout << "-------------------\n";
    cout << "Solved Board:\n";
    for (size_t row = 0; row < 9; ++row) {
        for (size_t col = 0; col < 9; ++col) {
            cout << board->ReturnValue(row, col) << " ";
        }
        cout << "\n";
    }
    cout << "-------------------\n";

    return retval;
}

int main()
{
    int retval = 0;

    // Run the test case
    retval += runTestCase();

    if (retval == 0) {
        cout << "All test cases passed successfully.\n";
    } else {
        cout << "Number of failed test cases: " << retval << "\n";
    }

    return retval;
}
