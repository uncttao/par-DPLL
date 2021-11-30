#include <iostream>
#include <fstream>
#include <ctime>
#include "tests/all.h"
#include "parser.h"
#include "system.h"
#include "timing.h"

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
        timespec start{}, finish{}, delta{};
        clock_gettime(CLOCK_REALTIME, &start);
#endif
        auto sat = dpll(formula);
#if SHOW_RESULT
        cout << sat << endl;
#endif
#if TIMING
        clock_gettime(CLOCK_REALTIME, &finish);
        sub_timespec(start, finish, &delta);
        printf("%d.%.9ld\n", (int) delta.tv_sec, delta.tv_nsec);
#endif

        fb.close();
    }

#endif

    return 0;
}
