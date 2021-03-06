#ifndef PAR_DPLL_DPLL_H
#define PAR_DPLL_DPLL_H

#include <unordered_set>
#include <iostream>

#if USE_CILK

#include <cilk/cilk.h>

#endif

#include "utils.h"
#include "formula.h"
#include "system.h"

using namespace std;

#if USE_CILK
bool exit_all;
#endif

enum StepResult {
    Sat, Unsat, Continue
};

bool branch_out(Formula& formula, int someLiteral, bool copy);

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
    formula.unitClauses.iterate([&formula](int unitClause) {
        auto& clauseLiterals = formula.literalsIn[unitClause];
        if (clauseLiterals.empty()) {   // possibly empty due to unit propagation
            return;
        }
        auto literal = clauseLiterals.first();
#if DEBUG_MODE
        cout << "unit propagate " << formula.cnf_literal(literal) << endl;
#endif
        formula.unit_propagation(literal);
    });
    formula.pureLiterals.iterate([&formula](int pureLiteral) {
#if DEBUG_MODE
        cout << "assign pure literal " << formula.cnf_literal(pureLiteral) << endl;
#endif
        formula.pure_literal_assign(pureLiteral);
    });
    return Continue;
}

bool dpll(Formula& formula) {
#if USE_CILK
    if (exit_all) {     // global parallel control
        return false;
    }
#endif

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
#if USE_CILK
        if (sat) {      // global parallel control
            exit_all = true;
        }
#endif
        return sat;
    }

    auto& activeLiterals = formula.activeLiterals;
    if (activeLiterals.empty()) {
#if DEBUG_MODE
        cout << "no more active literals. quit!" << endl;
#endif
        auto sat = formula.emptyClauses.empty();
#if USE_CILK
        if (sat) {      // global parallel control
            exit_all = true;
        }
#endif
        return sat;
    }

    auto someLiteral = activeLiterals.first();
#if DEBUG_MODE
    cout << "adding " << someLiteral << " (and negation) as unit clause" << endl;
#endif

#if USE_CILK
#if USE_CUTOFF
    if (formula.activeLiterals.size() <= CUTOFF) {
        return branch_out(formula, someLiteral, true) || branch_out(formula, formula.neg_literal(someLiteral), false);
    } else {
#endif
        auto formula2 = formula;
        auto left = cilk_spawn
        branch_out(formula2, someLiteral, false);
        auto right = branch_out(formula, formula.neg_literal(someLiteral), false);
        cilk_sync;
        return left || right;
#if USE_CUTOFF
    }
#endif
#else
    // first branch copies formula
    return branch_out(formula, someLiteral, true) || branch_out(formula, formula.neg_literal(someLiteral), false);
#endif
}

bool branch_out(Formula& formula, int someLiteral, bool copy) {
    if (copy) {
        auto formula2 = formula;
        formula2.add_unit_clause(someLiteral);
        return dpll(formula2);
    } else {
        formula.add_unit_clause(someLiteral);
        return dpll(formula);
    }
}

#endif //PAR_DPLL_DPLL_H
