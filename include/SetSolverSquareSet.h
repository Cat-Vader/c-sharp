#ifndef SetSolverSquareSet_h
#define SetSolverSquareSet_h

// Do not add any additional class.
#include <vector>

class SetSolverSquareSet
{
public:
    std::vector<int> set;
    int cellValue; // Represents the value of the cell

    SetSolverSquareSet() {
        // Default constructor for an empty white cell with all possible values
        set.push_back(1);
        set.push_back(2);
        set.push_back(3);
        set.push_back(4);
        set.push_back(5);
        set.push_back(6);
        set.push_back(7);
        set.push_back(8);
        set.push_back(9);
        cellValue = -99; // Using -99 to represent an empty white cell
    }

    // Set the value of the cell and update possible values accordingly
    void setValue(int value) {
        cellValue = value;
        set.clear();
        set.push_back(value);
    }

    // Get the current value of the cell
    int getValue() const {
        return cellValue;
    }

    // Remove a possible value from the set; returns true if a value was removed
    bool removePossibleValue(int value) {
        for (size_t i = 0; i < set.size(); ++i) {
            if (set[i] == value) {
                set.erase(set.begin() + i);
                return true;
            }
        }
        return false;
    }

    // Check if the cell is solved (only one possible value)
    bool isSolved() const {
        return set.size() == 1;
    }

    // Check if the cell is an empty white cell (unsolved)
    bool isEmptyWhiteCell() const {
        return cellValue == -99;
    }

    // Get the number of possible values for the cell
    int possibleValuesCount() const {
        return set.size();
    }

    // Get the only possible value if the cell is solved
    int getOnlyPossibleValue() const {
        return isSolved() ? set[0] : -1;
    }

    // Get all possible values for the cell
    std::vector<int> getPossibleValues() const {
        return set;
    }

    // Set possible values for the cell
    void setPossibleValues(const std::vector<int>& values) {
        set = values;
    }
};

#endif /* SetSolverSquareSet_h */

