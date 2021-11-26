#ifndef PAR_DPLL_DPLL_H
#define PAR_DPLL_DPLL_H

#include <unordered_set>
#include <iostream>
#include "utils.h"
#include "formula.h"
#include "system.h"

using namespace std;

enum StepResult {
    Sat, Unsat, Continue
};

StepResult dpll_step(Formula& formula) {
    if (formula.is_all_pure_literals()) {
#if DEBUG_MODE
        cout << "sat by all pure literals!" << endl;
#endif
        return Sat;
    }
    if (!formula.emptyClauses.empty()) {
#if DEBUG_MODE
        cout << "unsat by empty clause(s)!" << endl;
#endif
        return Unsat;
    }
    auto unitClauses = formula.unitClauses;
    for (auto& unitClause: unitClauses) {
        auto& clauseLiterals = formula.literalsIn[unitClause];
        if (clauseLiterals.empty()) {
            continue;
        }
        auto literal = *clauseLiterals.begin();
#if DEBUG_MODE
        cout << "unit propagate " << formula.cnf_literal(literal) << endl;
#endif
        formula.unit_propagation(literal);
    }
    auto pureLiterals = formula.pureLiterals;
    for (auto& pureLiteral: pureLiterals) {
#if DEBUG_MODE
        cout << "assign pure literal " << formula.cnf_literal(pureLiteral) << endl;
#endif
        formula.pure_literal_assign(pureLiteral);
    }
    return Continue;
}

bool dpll(Formula& formula) {
#if DEBUG_MODE
    cout << "start of dpll" << endl;
    print_cnf(*formula.produce());
#endif
    auto stepResult = dpll_step(formula);
#if DEBUG_MODE
    cout << "after dpll step. result: " << stepResult << endl;
    print_cnf(*formula.produce());
#endif

    if (stepResult != Continue) {
        return stepResult == Sat;
    }

    auto& activeLiterals = formula.activeLiterals;
    if (activeLiterals.empty()) {
#if DEBUG_MODE
        cout << "no more active literals. quit!" << endl;
#endif
        return formula.emptyClauses.empty();
    }

    auto someLiteral = *activeLiterals.begin();
#if DEBUG_MODE
    cout << "adding " << someLiteral << " (and negation) as unit clause" << endl;
#endif

    auto leftFormula = formula;     // make a copy
    leftFormula.add_unit_clause(someLiteral);
    auto leftSat = dpll(leftFormula);
    if (leftSat) {
        return true;
    } else {
        auto rightFormula = formula;    // make a copy
        rightFormula.add_unit_clause(rightFormula.neg_literal(someLiteral));
        return dpll(rightFormula);
    }
}

#endif //PAR_DPLL_DPLL_H
