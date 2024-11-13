#include <iostream>
#include <vector>
#include "SetSolver.h"

int main() {
    // Define a sample skeleton board
    std::vector<std::string> skeletonBoard = {
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

    // Initialize the SetSolver
    SetSolver solver;
    solver.populateBoard(skeletonBoard);

    // Print the initial board state
    std::cout << "Initial Board:" << std::endl;
    solver.printBoard();

    // Solve the puzzle
    solver.solve();

    // Print the solved board
    std::cout << "\nSolved Board:" << std::endl;
    solver.printBoard();

    return 0;
}
