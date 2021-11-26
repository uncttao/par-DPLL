#include "tests/all.h"
#include "parser.h"
#include "utils.h"
#include "system.h"

int main() {
#if TEST_MODE
    test_all();
#else
    auto formula = Formula(*parse_cnf());
    cout << dpll(formula) << endl;
#endif

    return 0;
}
