#include "tests/all.h"
#include "parser.h"
#include "utils.h"
#include "system.h"

int main() {
#if RUN_TEST
    test_all();
#endif
    auto cnf = parse_cnf();
    print_cnf(*cnf);

    return 0;
}
