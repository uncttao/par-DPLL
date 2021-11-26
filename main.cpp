#include <iostream>
#include <fstream>
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
        cout << dpll(formula) << endl;

        fb.close();
    }

#endif

    return 0;
}
