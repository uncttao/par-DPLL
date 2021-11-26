#ifndef PAR_DPLL_UTILS_H
#define PAR_DPLL_UTILS_H

#include <unordered_set>
#include <vector>
#include <iostream>
#include "intset.h"

using namespace std;

#define Set IntSet

unordered_set<int>* set_diff(unordered_set<int>& s1, unordered_set<int>& s2) {
    auto* s1Copy = new unordered_set<int>(s1);
    for (auto& s2Item: s2) {
        s1Copy->erase(s2Item);
    }
    return s1Copy;
}

unordered_set<int>* set_add(unordered_set<int>& s1, unordered_set<int>& s2) {
    auto* s1Copy = new unordered_set<int>(s1);
    for (auto& s2Item: s2) {
        s1Copy->insert(s2Item);
    }
    return s1Copy;
}

unordered_set<int>* set_neg(unordered_set<int>& s) {
    auto* sCopy = new unordered_set<int>();
    for (auto& item: s) {
        sCopy->insert(-item);
    }
    return sCopy;
}

void print_cnf(vector<vector<int>>& cnf) {
    for (auto& cnfClause: cnf) {
        for (auto& cnfLiteral: cnfClause) {
            cout << cnfLiteral << " ";
        }
        cout << ", ";
    }
    cout << endl;
}

#endif //PAR_DPLL_UTILS_H
