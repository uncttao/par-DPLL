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

void test_pure_literals() {
    vector<vector<int>> cnf1{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    auto expected1 = vector<int>{-1};
    auto pureLiterals1 = Formula::all_pure_literals(cnf1);
    assert(equal(pureLiterals1->begin(), pureLiterals1->end(), expected1.begin()));

    vector<vector<int>> cnf2{vector<int>{-4, -2, 3}, vector<int>{-2, 1, 3}, vector<int>{-1, 2, 4}};
    auto expected2 = vector<int>{3};
    auto pureLiterals2 = Formula::all_pure_literals(cnf2);
    assert(equal(pureLiterals2->begin(), pureLiterals2->end(), expected2.begin()));
}

void test_formula() {
    test_formula_convert_and_produce();
    test_formula_convert_and_produce2();
    test_formula_convert();
    test_pure_literals();
}

#endif //PAR_DPLL_FORMULA_TEST_H
