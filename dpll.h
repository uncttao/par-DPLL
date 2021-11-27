#ifndef PAR_DPLL_DPLL_H
#define PAR_DPLL_DPLL_H

#include <unordered_set>
#include <iostream>
#include <cilk/cilk.h>
#include "utils.h"
#include "formula.h"
#include "system.h"

using namespace std;

bool exit_all;

enum StepResult {
    Sat, Unsat, Continue
};

bool branch_out(Formula formula, int someLiteral);

StepResult dpll_step(Formula& formula) {
    if (formula.is_consistent()) {
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
    for (auto& unitClause: formula.unitClauses.bag()) {
        auto& clauseLiterals = formula.literalsIn[unitClause];
        if (clauseLiterals.empty()) {   // possibly empty due to unit propagation
            continue;
        }
        auto literal = clauseLiterals.first();
#if DEBUG_MODE
        cout << "unit propagate " << formula.cnf_literal(literal) << endl;
#endif
        formula.unit_propagation(literal);
    }
    for (auto& pureLiteral: formula.pureLiterals.bag()) {
#if DEBUG_MODE
        cout << "assign pure literal " << formula.cnf_literal(pureLiteral) << endl;
#endif
        formula.pure_literal_assign(pureLiteral);
    }
    return Continue;
}

bool dpll(Formula& formula) {
    if (exit_all) {     // global parallel control
        return false;
    }

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
        auto sat = stepResult == Sat;
        if (sat) {      // global parallel control
            exit_all = true;
        }
        return sat;
    }

    auto& activeLiterals = formula.activeLiterals;
    if (activeLiterals.empty()) {
#if DEBUG_MODE
        cout << "no more active literals. quit!" << endl;
#endif
        auto sat = formula.emptyClauses.empty();
        if (sat) {      // global parallel control
            exit_all = true;
        }
        return sat;
    }

    auto someLiteral = activeLiterals.first();
#if DEBUG_MODE
    cout << "adding " << someLiteral << " (and negation) as unit clause" << endl;
#endif

    bool left = cilk_spawn
    branch_out(formula, someLiteral);                        // arg copies formula
    bool right = branch_out(formula, formula.neg_literal(someLiteral));     // arg copies formula
    cilk_sync;
    return left || right;
}

bool branch_out(Formula formula, int someLiteral) {
    formula.add_unit_clause(someLiteral);
    return dpll(formula);
}

#endif //PAR_DPLL_DPLL_H
