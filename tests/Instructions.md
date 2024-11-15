### Documentation for SetSolver Program

#### Compilation Instructions

1. Ensure all source files (`main.cpp`, `SetSolver.h`, `SetSolverSquareSet.h`, `setSolverTest.cpp`) are in the same directory.
2. Use the following command to compile the main program:
   ```bash
   g++ -std=c++11 -o SetSolverProgram main.cpp
   ```
   This command compiles `main.cpp` along with its dependencies and outputs an executable named `SetSolverProgram`.
3. To run the main program, use:
   ```bash
   ./SetSolverProgram
   ```

For the test files, compile and run `setSolverTest.cpp` separately:
   ```bash
   g++ -std=c++11 -o SetSolverTest setSolverTest.cpp
   ./SetSolverTest
   ```

#### Code Overview

1. **SetSolver Class**:  
   - This class manages a board filled with cells, which can be empty or contain numeric values.
   - It uses a helper function to split string values, populate the board from a skeleton input, and apply logical constraints to solve the puzzle.

2. **SetSolverSquareSet Class**:
   - This class represents possible values for each cell on the board.
   - It provides functions to remove possible values, check for specific values, and determine if a cell has a single solution.

3. **main.cpp**:
   - Contains test cases for `PopulateBoard()` and `Solve()`, verifying that the board is correctly initialized and that constraints are applied.

4. **setSolverTest.cpp**:
   - Unit tests for `SetSolverSquareSet`, including tests for initialization, removing values, checking for values, and determining if a cell has been solved. 

