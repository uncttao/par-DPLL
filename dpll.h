#ifndef PAR_DPLL_DPLL_H
#define PAR_DPLL_DPLL_H

#include <unordered_set>
#include "utils.h"
#include "formula.h"

using namespace std;

bool dpll() {
    return false;
}

void unit_propagation(Formula& formula, int u) {
    auto clausesOf = formula.clausesOf;
    auto literalsIn = formula.literalsIn;

    // remove every clause containing "u"
    for (auto& clauseOfU: clausesOf[u]) {
        formula.clauseStatuses[clauseOfU] = Deleted;
    }

    // remove every "~u" from every clause
    auto n = formula.literalSize;
    auto nu = u < n ? u + n : u - n;
    for (auto& clauseOfNu: clausesOf[nu]) {
        literalsIn[clauseOfNu].erase(nu);
    }
    clausesOf[nu].clear();
}

#endif //PAR_DPLL_DPLL_H
