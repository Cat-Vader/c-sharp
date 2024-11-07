#ifndef SetSolverSquareSet_h
#define SetSolverSquareSet_h

#include <vector>
#include <algorithm>

class SetSolverSquareSet
{
public:
    std::vector<int> set;

    SetSolverSquareSet() {
        set = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    }

    bool removeValue(int value) {
        auto it = std::find(set.begin(), set.end(), value);
        if (it != set.end()) {
            set.erase(it);
            return true;
        }
        return false;
    }

    bool contains(int value) const {
        return std::find(set.begin(), set.end(), value) != set.end();
    }

    bool isSolved() const {
        return set.size() == 1;
    }

    int getValue() const {
        return isSolved() ? set[0] : -1;
    }
};

#endif /* SetSolverSquareSet_h */
