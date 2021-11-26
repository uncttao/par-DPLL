#include <iostream>
#include "tests/all.h"
#include "parser.h"
#include "system.h"

using namespace std;

int main() {
#if TEST_MODE
    test_all();
#else
    auto formula = Formula(*parse_cnf(cin));
    cout << dpll(formula) << endl;
#endif

    return 0;
}
