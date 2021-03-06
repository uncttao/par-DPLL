#ifndef PAR_DPLL_ALL_H
#define PAR_DPLL_ALL_H

#include "unit-propagation.h"
#include "formula-test.h"
#include "dpll-test.h"
#include "intset-test.h"

void test_all() {
    test_intset();
    test_formula();
    test_unit_propagation();
    test_dpll();
}

#endif //PAR_DPLL_ALL_H
