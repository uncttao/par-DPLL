#ifndef PAR_DPLL_FORMULA_TEST_H
#define PAR_DPLL_FORMULA_TEST_H

#include <vector>
#include <cassert>
#include "../utils.h"
#include "../formula.h"

using namespace std;

void test_formula_convert_and_produce() {
    vector<vector<int>> cnf1{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    auto cnf1r = Formula(cnf1).produce();
    assert(equal(cnf1.begin(), cnf1.end(), cnf1r->begin()));

    vector<vector<int>> cnf2{vector<int>{-4, -2, 3}, vector<int>{-2, 1, 3}, vector<int>{-1, 2, 4}};
    auto cnf2r = Formula(cnf2).produce();
    assert(equal(cnf2.begin(), cnf2.end(), cnf2r->begin()));
}

void test_formula_convert_and_produce2() {
    vector<vector<int>> cnf1{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    auto cnf1r = Formula(cnf1).produce2();
    assert(equal(cnf1.begin(), cnf1.end(), cnf1r->begin()));

    vector<vector<int>> cnf2{vector<int>{-4, -2, 3}, vector<int>{-2, 1, 3}, vector<int>{-1, 2, 4}};
    auto cnf2r = Formula(cnf2).produce2();
    assert(equal(cnf2.begin(), cnf2.end(), cnf2r->begin()));
}

void test_formula_convert() {
    vector<vector<int>> cnf1{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    auto formula1 = Formula(cnf1);
    auto clausesOf1 = formula1.clausesOf;
    auto expected1 = vector<Set >{
            set(), set(), set(0, 2)/*2*/, set(0)/*3*/, set(1)/*4*/,
            set(0, 2)/*-1*/, set(1)/*-2*/, set(1)/*-3*/, set(2)/*-4*/
    };
    for (auto literal = 0; literal < expected1.size(); literal++) {
        assert(expected1[literal] == clausesOf1[literal]);
    }

    vector<vector<int>> cnf2{vector<int>{-4, -2, 3}, vector<int>{-2, 1, 3}, vector<int>{-1, 2, 4}};
    auto formula2 = Formula(cnf2);
    auto clausesOf2 = formula2.clausesOf;
    auto expected2 = vector<Set >{
            set(), set(1)/*1*/, set(2)/*2*/, set(0, 1)/*3*/, set(2)/*4*/,
            set(2)/*-1*/, set(0, 1)/*-2*/, set()/*-3*/, set(0)/*-4*/
    };
    for (auto literal = 0; literal < expected2.size(); literal++) {
        assert(expected2[literal] == clausesOf2[literal]);
    }
}

void test_empty_clause1() {
    vector<vector<int>> cnf{vector<int>{-1, 2, 3}, vector<int>{-2}, vector<int>{-4, -1, 2}};
    auto f = Formula(cnf);
    f.unit_propagation(2);
    Set expected{1};
    assert(equal(f.emptyClauses->begin(), f.emptyClauses->end(), expected.begin()));
}

void test_empty_clause2() {
    vector<vector<int>> cnf{vector<int>{-1, 2, 3}, vector<int>{-4, -1, 2}, vector<int>{-2}};
    auto f = Formula(cnf);
    f.unit_propagation(2);
    Set expected{2};
    assert(equal(f.emptyClauses->begin(), f.emptyClauses->end(), expected.begin()));
}

void test_unit_clauses1() {
    vector<vector<int>> cnf{vector<int>{-1, 2, 3}, vector<int>{-2}, vector<int>{-4, -1, 2}, vector<int>{1}};
    auto f = Formula(cnf);
    assert(equal(f.unitClauses->begin(), f.unitClauses->end(), ((Set) {1, 3}).begin()));
}

void test_unit_clauses2() {
    vector<vector<int>> cnf{vector<int>{-1, 2, 3}, vector<int>{-2}, vector<int>{-4, -1, 2}, vector<int>{1}};
    auto f = Formula(cnf);
    f.unit_propagation(1);
    assert(equal(f.unitClauses->begin(), f.unitClauses->end(), ((Set) {1}).begin()));
}

void test_unit_clauses3() {
    vector<vector<int>> cnf{vector<int>{-1, 2, 3}, vector<int>{-2}, vector<int>{-4, -1, 2}, vector<int>{1}};
    auto f = Formula(cnf);
    f.unit_propagation(5/*-1*/);
    assert(equal(f.unitClauses->begin(), f.unitClauses->end(), ((Set) {1}).begin()));
}

void test_formula() {
    test_formula_convert_and_produce();
    test_formula_convert_and_produce2();
    test_formula_convert();
    test_empty_clause1();
    test_empty_clause2();
    test_unit_clauses1();
    test_unit_clauses2();
    test_unit_clauses3();
}

#endif //PAR_DPLL_FORMULA_TEST_H
