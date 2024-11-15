#ifndef SetSolver_h
#define SetSolver_h

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include "SetSolverSquareSet.h"

using std::vector;
using std::string;
using std::cout;
using std::set;

class SetSolver {
private:
    int boardSize = 9;
    vector<vector<SetSolverSquareSet>> board;

public:
    // Function declarations
    void PopulateBoard(vector<string> skeletonBoard);
    int ReturnValue(size_t row, size_t col);
    void Solve();
    void printBoard(); // Prints the board for debugging
};

#endif /* SetSolver_h */
