#ifndef PAR_DPLL_ALL_H
#define PAR_DPLL_ALL_H

#include "unit-propagation.h"
#include "formula-test.h"
#include "unit-propagation.h"

void test_all() {
    test_formula();
    test_unit_propagation();
}

#endif //PAR_DPLL_ALL_H
