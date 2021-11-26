#ifndef PAR_DPLL_PARSER_H
#define PAR_DPLL_PARSER_H

#include <iostream>

using namespace std;

// credits: https://github.com/sukrutrao/SAT-Solver-DPLL
vector<vector<int>>* parse_cnf(istream& input) {
    char c;   // store first character
    string s; // dummy string

    int literal_count;
    int clause_count;

    while (true) {
        input >> c;
        if (c == 'c') // if comment
        {
            getline(input, s); // ignore
        } else             // else, if would be a p
        {
            input >> s; // this would be cnf
            break;
        }
    }
    input >> literal_count;
    input >> clause_count;

    auto cnf = new vector<vector<int>>();
    cnf->resize(clause_count);

    int literal; // store the incoming literal value
    // iterate over the clauses
    for (int i = 0; i < clause_count; i++) {
        while (true) // while the ith clause gets more literals
        {
            input >> literal;
            if (literal != 0) {
                (*cnf)[i].push_back(literal); // store it in the form 2n
            } else {
                break; // read 0, so move to next clause
            }
        }
    }

    return cnf;
}

#endif //PAR_DPLL_PARSER_H
