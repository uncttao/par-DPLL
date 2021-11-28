#include <iostream>
#include <fstream>
#include <ctime>
#include "tests/all.h"
#include "parser.h"
#include "system.h"

using namespace std;

int main(int argc, char* argv[]) {
#if TEST_MODE
    test_all();
#else
    filebuf fb;
    if (fb.open(argv[1], ios::in)) {
        istream file(&fb);

        auto formula = Formula(*parse_cnf(file));

#if TIMING
        auto t0 = clock();
#endif
        auto sat = dpll(formula);
#if SHOW_RESULT
        cout << sat << endl;
#endif
#if TIMING
        auto t1 = clock();
        auto ms = (t1 - t0) * 1000 / CLOCKS_PER_SEC;
        cout << ms << endl;
#endif

        fb.close();
    }

#endif

    return 0;
}
