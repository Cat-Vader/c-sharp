// SetSolverSquareSet.h
#ifndef SETSOLVERSQUARESET_H
#define SETSOLVERSQUARESET_H

#include <vector>
#include <algorithm>

class SetSolverSquareSet {
private:
    int value; // Current value of the cell
    int rowHint; // Row hint for black cells
    int colHint; // Column hint for black cells
    std::vector<int> possibleValues; // Possible values for the cell

public:
    // Constructors
    SetSolverSquareSet() 
        : value(99), rowHint(0), colHint(0), possibleValues{1,2,3,4,5,6,7,8,9} {} // Empty white cell

    SetSolverSquareSet(int val) 
        : value(val), rowHint(0), colHint(0), possibleValues{} { // Filled cell or black cell
        if (val > 0 && val < 100) { // Pre-filled white cell
            possibleValues.clear();
            possibleValues.push_back(val);
        }
    }

    // Setters for hints
    void setRowHint(int hint) { rowHint = hint; }
    void setColHint(int hint) { colHint = hint; }

    // Getters for hints
    int getRowHint() const { return rowHint; }
    int getColHint() const { return colHint; }

    // Getters
    int getValue() const { return value; }
    std::vector<int> getPossibleValues() const { return possibleValues; }

    // Setters
    void setValue(int val) { 
        value = val; 
        if (val > 0 && val < 100) {
            possibleValues.clear();
            possibleValues.push_back(val);
        }
    }

    void setPossibleValues(const std::vector<int>& vals) { possibleValues = vals; }

    // Utility Methods
    bool isEmptyWhiteCell() const { return value == 99; }
    bool isSolved() const { return !isEmptyWhiteCell() && value > 0 && value < 100; }

    void removeValue(int val) {
        if (isEmptyWhiteCell()) { // Only modify possibleValues if the cell is empty
            possibleValues.erase(std::remove(possibleValues.begin(), possibleValues.end(), val), possibleValues.end());
        }
    }
};

#endif /* SETSOLVERSQUARESET_H */
