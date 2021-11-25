#ifndef PAR_DPLL_DPLL_TEST_H
#define PAR_DPLL_DPLL_TEST_H

#include <cassert>
#include "../dpll.h"

using namespace std;

void test_dpll_step1() {
    vector<vector<int>> cnf{vector<int>{-1, -2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 3}, vector<int>{2}};
    auto f = Formula(cnf);
    auto result = dpll_step(f);

    vector<vector<int>> expected{vector<int>{-3, 4}};
    assert(equal(expected.begin(), expected.end(), f.produce()->begin()));
    assert(equal(expected.begin(), expected.end(), f.produce2()->begin()));

    assert(result == Continue);
}

void test_dpll_step2() {
    vector<vector<int>> cnf{vector<int>{-4, -2, 3}, vector<int>{-2, -1, 3}, vector<int>{-1, 2, 4}, vector<int>{-3}};
    auto f = Formula(cnf);
    auto result = dpll_step(f);

    vector<vector<int>> expected{vector<int>{-4, -2}};
    assert(equal(expected.begin(), expected.end(), f.produce()->begin()));
    assert(equal(expected.begin(), expected.end(), f.produce2()->begin()));

    assert(result == Continue);
}

void test_dpll_step3() {
    vector<vector<int>> cnf{vector<int>{}, vector<int>{-2, -1, 3}, vector<int>{-1, 2, 4}, vector<int>{-3}};
    auto f = Formula(cnf);
    auto result = dpll_step(f);
    assert(result == Unsat);
}

void test_dpll_step4() {
    vector<vector<int>> cnf{vector<int>{-2, -1}, vector<int>{-2, -1, 3}, vector<int>{-1, 3, 4}};
    auto f = Formula(cnf);
    auto result = dpll_step(f);
    assert(result == Sat);
}

void test_dpll() {
    test_dpll_step1();
    test_dpll_step2();
    test_dpll_step3();
    test_dpll_step4();
}

#endif //PAR_DPLL_DPLL_TEST_H
