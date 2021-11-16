#ifndef PAR_DPLL_FORMULA_TEST_H
#define PAR_DPLL_FORMULA_TEST_H

#include <vector>
#include <cassert>
#include "../utils.h"
#include "../formula.h"

using namespace std;

void test_formula_convert_and_produce() {
    vector<vector<int>> cnf1{vector<int>{-1, 2, 3}, vector<int>{-3, -2, 4}, vector<int>{-4, -1, 2}};
    auto cnf1r = Formula::convert(cnf1)->produce();
    assert(equal(cnf1.begin(), cnf1.end(), cnf1r->begin()));

    vector<vector<int>> cnf2{vector<int>{-4, -2, 3}, vector<int>{-2, 1, 3}, vector<int>{-1, 2, 4}};
    auto cnf2r = Formula::convert(cnf2)->produce();
    assert(equal(cnf2.begin(), cnf2.end(), cnf2r->begin()));
}

#endif //PAR_DPLL_FORMULA_TEST_H
