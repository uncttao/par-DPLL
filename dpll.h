#ifndef PAR_DPLL_DPLL_H
#define PAR_DPLL_DPLL_H

#include <unordered_set>

using namespace std;

bool dpll() {
    return false;
}

void unit_propagation(int n, int u, unordered_set<int>* clausesOf, unordered_set<int>* literalsIn) {
    // remove every clause containing "u"
    for (auto& clauseOfU: clausesOf[u]) {
        for (auto& literal: literalsIn[clauseOfU]) {
            clausesOf[literal].erase(clauseOfU);
        }
        literalsIn[clauseOfU].clear();
    }

    // remove every "~u" from every clause
    auto nu = u < n ? u + n : u - n;
    for (auto& clauseOfNu: clausesOf[nu]) {
        literalsIn[clauseOfNu].erase(nu);
    }
    clausesOf[nu].clear();
}

#endif //PAR_DPLL_DPLL_H
