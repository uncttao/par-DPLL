#ifndef PAR_DPLL_UNIT_PROPAGATION_H
#define PAR_DPLL_UNIT_PROPAGATION_H

#include <vector>
#include "../utils.h"
#include "../formula.h"
#include "dpll.h"
#include <cassert>

using namespace std;

void test_unit_propagation1() {
    vector<vector<int>> cnf{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    auto f = Formula::convert(cnf);
    unit_propagation(*f, 6/*-2*/);
    vector<vector<int>> expected{vector<int>{-1, 3}, vector<int>{}, vector<int>{-4, -1}};
    assert(equal(expected.begin(), expected.end(), f->produce()->begin()));
    assert(equal(expected.begin(), expected.end(), f->produce2()->begin()));
}

void test_unit_propagation2() {
    vector<vector<int>> cnf{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    auto f = Formula::convert(cnf);
    unit_propagation(*f, 2);
    vector<vector<int>> expected{vector<int>{}, vector<int>{-3, 4}, vector<int>{}};
    assert(equal(expected.begin(), expected.end(), f->produce()->begin()));
    assert(equal(expected.begin(), expected.end(), f->produce2()->begin()));
}

void test_unit_propagation3() {
    vector<vector<int>> cnf{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    auto f = Formula::convert(cnf);
    unit_propagation(*f, 8/*-4*/);
    vector<vector<int>> expected{vector<int>{-1, 2, 3}, vector<int>{-3, -2}, vector<int>{}};
    assert(equal(expected.begin(), expected.end(), f->produce()->begin()));
    assert(equal(expected.begin(), expected.end(), f->produce2()->begin()));
}

void test_unit_propagation4() {
    vector<vector<int>> cnf{vector<int>{-4, -2, 3}, vector<int>{-2, 1, 3}, vector<int>{-1, 2, 4}};
    auto f = Formula::convert(cnf);
    unit_propagation(*f, 3);
    vector<vector<int>> expected{vector<int>{}, vector<int>{}, vector<int>{-1, 2, 4}};
    assert(equal(expected.begin(), expected.end(), f->produce()->begin()));
    assert(equal(expected.begin(), expected.end(), f->produce2()->begin()));
}

void test_unit_propagation5() {
    vector<vector<int>> cnf{vector<int>{-4, -2, 3}, vector<int>{-2, 1, 3}, vector<int>{-1, 2, 4}};
    auto f = Formula::convert(cnf);
    unit_propagation(*f, 6/*-2*/);
    vector<vector<int>> expected{vector<int>{}, vector<int>{}, vector<int>{-1, 4}};
    assert(equal(expected.begin(), expected.end(), f->produce()->begin()));
    assert(equal(expected.begin(), expected.end(), f->produce2()->begin()));
}

void test_unit_propagation() {
    test_unit_propagation1();
    test_unit_propagation2();
    test_unit_propagation3();
    test_unit_propagation4();
    test_unit_propagation5();
}

#endif //PAR_DPLL_UNIT_PROPAGATION_H
