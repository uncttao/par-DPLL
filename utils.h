#ifndef PAR_DPLL_UTILS_H
#define PAR_DPLL_UTILS_H

#include <unordered_set>
#include <vector>
#include <iostream>

using namespace std;

#define Set unordered_set<int>
#define set(...) unordered_set<int>({__VA_ARGS__})

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
