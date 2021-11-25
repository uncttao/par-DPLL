#ifndef PAR_DPLL_DPLL_H
#define PAR_DPLL_DPLL_H

#include <unordered_set>
#include "utils.h"
#include "formula.h"

using namespace std;

enum StepResult {
    Sat, Unsat, Continue
};

StepResult dpll_step(Formula& formula) {
    if (formula.is_all_pure_literals()) {
        return Sat;
    }
    if (!formula.emptyClauses->empty()) {
        return Unsat;
    }
    auto unitClauses = *formula.unitClauses;
    for (auto& unitClause: unitClauses) {
        auto literal = *formula.literalsIn[unitClause].begin();
        formula.unit_propagation(literal);
    }
    auto pureLiterals = *formula.pureLiterals;
    for (auto& pureLiteral: pureLiterals) {
        formula.pure_literal_assign(pureLiteral);
    }
    return Continue;
}

#endif //PAR_DPLL_DPLL_H
