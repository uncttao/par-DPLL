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
    if (!formula.emptyClauses.empty()) {
        return Unsat;
    }
    auto unitClauses = formula.unitClauses;
    for (auto& unitClause: unitClauses) {
        auto& clauseLiterals = formula.literalsIn[unitClause];
        if (clauseLiterals.empty()) {
            continue;
        }
        auto literal = *clauseLiterals.begin();
        formula.unit_propagation(literal);
    }
    auto pureLiterals = formula.pureLiterals;
    for (auto& pureLiteral: pureLiterals) {
        formula.pure_literal_assign(pureLiteral);
    }
    return Continue;
}

bool dpll(Formula& formula) {
    auto stepResult = dpll_step(formula);
    if (stepResult != Continue) {
        return stepResult == Sat;
    }

    auto& activeLiterals = formula.activeLiterals;
    if (activeLiterals.empty()) {
        return false;
    }
    auto someLiteral = *activeLiterals.begin();
    auto leftFormula = formula;
    leftFormula.add_unit_clause(someLiteral);
    auto rightFormula = formula;
    rightFormula.add_unit_clause(rightFormula.neg_literal(someLiteral));
    return dpll(leftFormula) || dpll(rightFormula);
}

#endif //PAR_DPLL_DPLL_H
