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
    auto expected1 = vector<vector<int>>{
            vector<int>(), vector<int>(), vector<int>{0, 2}/*2*/, vector<int>{0}/*3*/, vector<int>{1}/*4*/,
            vector<int>{0, 2}/*-1*/, vector<int>{1}/*-2*/, vector<int>{1}/*-3*/, vector<int>{2}/*-4*/
    };
    for (auto literal = 0; literal < expected1.size(); literal++) {
        assert(equal(expected1[literal].begin(), expected1[literal].end(), clausesOf1[literal].bag().begin()));
    }

    vector<vector<int>> cnf2{vector<int>{-4, -2, 3}, vector<int>{-2, 1, 3}, vector<int>{-1, 2, 4}};
    auto formula2 = Formula(cnf2);
    auto clausesOf2 = formula2.clausesOf;
    auto expected2 = vector<vector<int>>{
            vector<int>(), vector<int>{1}/*1*/, vector<int>{2}/*2*/, vector<int>{0, 1}/*3*/, vector<int>{2}/*4*/,
            vector<int>{2}/*-1*/, vector<int>{0, 1}/*-2*/, vector<int>()/*-3*/, vector<int>{0}/*-4*/
    };
    for (auto literal = 0; literal < expected2.size(); literal++) {
        assert(equal(expected2[literal].begin(), expected2[literal].end(), clausesOf2[literal].bag().begin()));
    }
}

void test_initial_pure_literals() {
    vector<vector<int>> cnf1{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    auto f1 = Formula(cnf1);
    auto& pureLiterals1 = f1.pureLiterals.bag();
    assert(equal(pureLiterals1.begin(), pureLiterals1.end(), (vector<int>{5/*-1*/}).begin()));

    vector<vector<int>> cnf2{vector<int>{-4, -2, 3}, vector<int>{-2, 1, 3}, vector<int>{-1, 2, 4}};
    auto f2 = Formula(cnf2);
    auto& pureLiterals2 = f2.pureLiterals.bag();
    assert(equal(pureLiterals2.begin(), pureLiterals2.end(), (vector<int>{3}).begin()));
}

void test_empty_clause1() {
    vector<vector<int>> cnf{vector<int>{-1, 2, 3}, vector<int>{-2}, vector<int>{-4, -1, 2}};
    auto f = Formula(cnf);
    f.unit_propagation(2);
    auto& emptyClauses = f.emptyClauses.bag();
    assert(equal(emptyClauses.begin(), emptyClauses.end(), ((vector<int>) {1}).begin()));
}

void test_empty_clause2() {
    vector<vector<int>> cnf{vector<int>{-1, 2, 3}, vector<int>{-4, -1, 2}, vector<int>{-2}};
    auto f = Formula(cnf);
    f.unit_propagation(2);
    auto& emptyClauses = f.emptyClauses.bag();
    assert(equal(emptyClauses.begin(), emptyClauses.end(), ((vector<int>) {2}).begin()));
}

void test_unit_clauses1() {
    vector<vector<int>> cnf{vector<int>{-1, 2, 3}, vector<int>{-2}, vector<int>{-4, -1, 2}, vector<int>{1}};
    auto f = Formula(cnf);
    auto& unitClauses = f.unitClauses.bag();
    assert(equal(unitClauses.begin(), unitClauses.end(), (vector<int>{1, 3}).begin()));
}

void test_unit_clauses2() {
    vector<vector<int>> cnf{vector<int>{-1, 2, 3}, vector<int>{-2}, vector<int>{-4, -1, 2}, vector<int>{1}};
    auto f = Formula(cnf);
    f.unit_propagation(1);
    auto& unitClauses = f.unitClauses.bag();
    assert(equal(unitClauses.begin(), unitClauses.end(), (vector<int>{1}).begin()));
}

void test_unit_clauses3() {
    vector<vector<int>> cnf{vector<int>{-1, 2, 3}, vector<int>{-2}, vector<int>{-4, -1, 2}, vector<int>{1}};
    auto f = Formula(cnf);
    f.unit_propagation(5/*-1*/);
    auto& unitClauses = f.unitClauses.bag();
    assert(equal(unitClauses.begin(), unitClauses.end(), (vector<int>{1}).begin()));
}

void test_pure_literal_maintenance1() {
    vector<vector<int>> cnf1{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    auto f1 = Formula(cnf1);
    auto pures = f1.pureLiterals.bag();
    assert(equal(pures.begin(), pures.end(), (vector<int>{5/*-1*/}).begin()));
    f1.delete_clause(1);
    pures = f1.pureLiterals.bag();
    assert(equal(pures.begin(), pures.end(), (vector<int>{2, 3, 5/*-1*/, 8/*-4*/}).begin()));
}

void test_pure_literal_maintenance2() {
    vector<vector<int>> cnf1{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    auto f1 = Formula(cnf1);
    f1.delete_literal_from(8/*-4*/, 2);
    auto pures = f1.pureLiterals.bag();
    assert(equal(pures.begin(), pures.end(), (vector<int>{4, 5/*-1*/}).begin()));
}

void test_all_initial_literals() {
    vector<vector<int>> cnf1{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    auto f1 = Formula(cnf1);
    auto activeLiterals1 = f1.activeLiterals.bag();
    assert(equal(activeLiterals1.begin(), activeLiterals1.end(),
                 (vector<int>{2, 3, 4, 5/*-1*/, 6/*-2*/, 7/*-3*/, 8/*-4*/}).begin()));

    vector<vector<int>> cnf2{vector<int>{-4, -2, 3}, vector<int>{-2, 1, 3}, vector<int>{-1, 2, 4}};
    auto f2 = Formula(cnf2);
    auto activeLiterals2 = f2.activeLiterals.bag();
    assert(equal(activeLiterals2.begin(), activeLiterals2.end(),
                 (vector<int>{1, 2, 3, 4, 5/*-1*/, 6/*-2*/, 8/*-4*/}).begin()));
}

void test_all_literals_maintenance() {
    vector<vector<int>> cnf1{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    auto f1 = Formula(cnf1);
    f1.delete_literal_from(7/*-3*/, 1);
    auto activeLiterals1 = f1.activeLiterals.bag();
    assert(equal(activeLiterals1.begin(), activeLiterals1.end(),
                 (vector<int>{2, 3, 4, 5/*-1*/, 6/*-2*/, 8/*-4*/}).begin()));

    f1.delete_clause(2);
    activeLiterals1 = f1.activeLiterals.bag();
    assert(equal(activeLiterals1.begin(), activeLiterals1.end(),
                 (vector<int>{2, 3, 4, 5/*-1*/, 6/*-2*/}).begin()));

    f1.delete_literal_from(4, 1);
    activeLiterals1 = f1.activeLiterals.bag();
    assert(equal(activeLiterals1.begin(), activeLiterals1.end(),
                 (vector<int>{2, 3, 5/*-1*/, 6/*-2*/}).begin()));

    f1.delete_clause(0);
    activeLiterals1 = f1.activeLiterals.bag();
    assert(equal(activeLiterals1.begin(), activeLiterals1.end(),
                 (vector<int>{6/*-2*/}).begin()));
}

void test_is_all_pure_literals() {
    vector<vector<int>> cnf1{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    auto f1 = Formula(cnf1);
    assert(!f1.is_consistent());
    f1.delete_literal_from(2, 0);
    assert(!f1.is_consistent());
    f1.delete_literal_from(2, 2);
    assert(!f1.is_consistent());
    f1.delete_literal_from(3, 0);
    assert(!f1.is_consistent());
    f1.delete_literal_from(4, 1);
    assert(f1.is_consistent());
}

void test_add_unit_clause() {
    vector<vector<int>> cnf{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    auto f = Formula(cnf);
    f.add_unit_clause(3);
    vector<vector<int>> expected{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}, vector<int>{3}};
    assert(equal(expected.begin(), expected.end(), f.produce()->begin()));
    assert(equal(expected.begin(), expected.end(), f.produce2()->begin()));
    auto& unitClauses = f.unitClauses.bag();
    assert(equal(unitClauses.begin(), unitClauses.end(), (vector<int>{3}).begin()));

    f.add_unit_clause(5/*-1*/);
    vector<vector<int>> expected2{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}, vector<int>{3},
                                  vector<int>{-1}};
    assert(equal(expected2.begin(), expected2.end(), f.produce()->begin()));
    assert(equal(expected2.begin(), expected2.end(), f.produce2()->begin()));
    unitClauses = f.unitClauses.bag();
    assert(equal(unitClauses.begin(), unitClauses.end(), (vector<int>{3, 4}).begin()));

    auto& pureLiterals = f.pureLiterals.bag();
    assert(equal(pureLiterals.begin(), pureLiterals.end(), (vector<int>{5/*-1*/}).begin()));
    f.add_unit_clause(1);
    pureLiterals = f.pureLiterals.bag();
    assert(equal(pureLiterals.begin(), pureLiterals.end(), (vector<int>{}).begin()));
}

void test_pure_literal_assign1() {
    vector<vector<int>> cnf{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    vector<vector<int>> cnf2{vector<int>{-4, -2, 3}, vector<int>{-2, 1, 3}, vector<int>{-1, 2, 4}};
    auto f = Formula(cnf);
    f.pure_literal_assign(5/*-1*/);
    vector<vector<int>> expected{vector<int>{-3, -2, 4}};
    assert(equal(expected.begin(), expected.end(), f.produce()->begin()));
    assert(equal(expected.begin(), expected.end(), f.produce2()->begin()));
}

void test_pure_literal_assign2() {
    vector<vector<int>> cnf{vector<int>{-4, -2, 3}, vector<int>{-2, 1, 3}, vector<int>{-1, 2, 4}};
    auto f = Formula(cnf);
    f.pure_literal_assign(3);
    vector<vector<int>> expected{vector<int>{-1, 2, 4}};
    assert(equal(expected.begin(), expected.end(), f.produce()->begin()));
    assert(equal(expected.begin(), expected.end(), f.produce2()->begin()));
}

void test_formula() {
    test_formula_convert_and_produce();
    test_formula_convert_and_produce2();
    test_formula_convert();
    test_initial_pure_literals();
    test_empty_clause1();
    test_empty_clause2();
    test_unit_clauses1();
    test_unit_clauses2();
    test_unit_clauses3();
    test_pure_literal_maintenance1();
    test_pure_literal_maintenance2();
    test_all_initial_literals();
    test_all_literals_maintenance();
    test_is_all_pure_literals();
    test_add_unit_clause();
    test_pure_literal_assign1();
    test_pure_literal_assign2();
}

#endif //PAR_DPLL_FORMULA_TEST_H
