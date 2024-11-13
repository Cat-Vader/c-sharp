#ifndef SetSolverSquareSet_h
#define SetSolverSquareSet_h

#include <vector>
// No additional headers are included as per assignment constraints

class SetSolverSquareSet
{
public:
    std::vector<int> set;  // Possible values for the cell
    int cellValue;         // Current value of the cell

    // Constructor for empty white squares
    SetSolverSquareSet() {
        cellValue = 99;  // 99 denotes an empty white square
        // Initialize set with values 1-9
        for (int i = 1; i <= 9; ++i) {
            set.push_back(i);
        }
    }

    // Constructor for squares with a specific value
    SetSolverSquareSet(int value) {
        cellValue = value;
        if (value == 0 || value < 0) {
            // Empty black square or black square with a hint
            set.clear();  // No possible values
        } else {
            // Filled white square
            set.push_back(value);  // Only one possible value
        }
    }

    // Removes a value from possible values; returns true if removed
    bool removeValue(int value) {
        for (size_t i = 0; i < set.size(); ++i) {
            if (set[i] == value) {
                set.erase(set.begin() + i);
                return true;
            }
        }
        return false;
    }

    // Checks if the cell contains a specific value in possible values
    bool contains(int value) const {
        for (size_t i = 0; i < set.size(); ++i) {
            if (set[i] == value) {
                return true;
            }
        }
        return false;
    }

    // Checks if the cell is solved (only one possible value)
    bool isSolved() const {
        return set.size() == 1;
    }

    // Gets the current value of the cell
    int getValue() const {
    if (isSolved()) {
        return set[0]; // Return the only possible value
    }
    return cellValue; // Otherwise, return the default value
}


    // Sets the value of the cell
    void setValue(int value) {
        cellValue = value;
        set.clear();
        if (value > 0) {
            set.push_back(value);
        }
    }

    // Sets possible values explicitly
    void setPossibleValues(const std::vector<int>& values) {
        set = values;
    }

    // Gets possible values
    std::vector<int> getPossibleValues() const {
        return set;
    }

    // Checks if the cell is an empty white square
    bool isEmptyWhiteCell() const {
        return cellValue == 99;
    }

    // Gets the only possible value (when the cell is solved)
    int getOnlyPossibleValue() const {
        if (isSolved()) {
            return set[0];
        }
        return -1;
    }

    // Gets the count of possible values
    int possibleValuesCount() const {
        return set.size();
    }
};

#endif /* SetSolverSquareSet_h */
