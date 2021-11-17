#ifndef PAR_DPLL_UTILS_H
#define PAR_DPLL_UTILS_H

#include <unordered_set>
#include <vector>
#include <iostream>

using namespace std;

#define Set unordered_set<int>
#define set(...) unordered_set<int>({__VA_ARGS__})

Set* set_diff(Set& s1, Set& s2) {
    Set* s1Copy = new Set(s1);
    for (auto& s2Item: s2) {
        s1Copy->erase(s2Item);
    }
    return s1Copy;
}

Set* set_add(Set& s1, Set& s2) {
    Set* s1Copy = new Set(s1);
    for (auto& s2Item: s2) {
        s1Copy->insert(s2Item);
    }
    return s1Copy;
}

Set* set_neg(Set& s) {
    Set* sCopy = new Set();
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
