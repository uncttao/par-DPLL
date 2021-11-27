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
        cout << dpll(formula) << endl;
#if TIMING
        auto t1 = clock();
        auto ms = (t1 - t0) * 1000 / CLOCKS_PER_SEC;
        cout << "Took time " << (int) ms << "." << endl;
#endif

        fb.close();
    }

#endif

    return 0;
}
