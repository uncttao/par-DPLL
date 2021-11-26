#include "tests/all.h"
#include "parser.h"
#include "utils.h"
#include "system.h"

int main() {
#if RUN_TEST
    test_all();
#endif

    auto formula = Formula(*parse_cnf());
    cout << dpll(formula) << endl;

    return 0;
}
