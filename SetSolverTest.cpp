#include <iostream>
#include "SetSolverSquareSet.h"

void testConstructor() {
    SetSolverSquareSet square;
    std::cout << "Testing constructor... ";
    if (square.set == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}) {
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed\n";
    }
}

void testRemoveValue() {
    SetSolverSquareSet square;
    std::cout << "Testing removeValue... ";
    square.removeValue(5);
    if (!square.contains(5)) {
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed\n";
    }
}

void testContains() {
    SetSolverSquareSet square;
    std::cout << "Testing contains... ";
    if (square.contains(3) && !square.contains(10)) {
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed\n";
    }
}

void testIsSolved() {
    SetSolverSquareSet square;
    std::cout << "Testing isSolved... ";
    for (int i = 2; i <= 9; ++i) {
        square.removeValue(i);
    }
    if (square.isSolved()) {
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed\n";
    }
}

void testGetValue() {
    SetSolverSquareSet square;
    std::cout << "Testing getValue... ";
    for (int i = 2; i <= 9; ++i) {
        square.removeValue(i);
    }
    if (square.getValue() == 1) {
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed\n";
    }
}

int main() {
    testConstructor();
    testRemoveValue();
    testContains();
    testIsSolved();
    testGetValue();
    return 0;
}
