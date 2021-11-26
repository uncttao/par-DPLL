#ifndef PAR_DPLL_PARSER_H
#define PAR_DPLL_PARSER_H

#include <iostream>

// credits: https://github.com/sukrutrao/SAT-Solver-DPLL
vector<vector<int>>* parse_cnf() {
    char c;   // store first character
    string s; // dummy string

    int literal_count;
    int clause_count;

    while (true) {
        cin >> c;
        if (c == 'c') // if comment
        {
            getline(cin, s); // ignore
        } else             // else, if would be a p
        {
            cin >> s; // this would be cnf
            break;
        }
    }
    cin >> literal_count;
    cin >> clause_count;

    auto cnf = new vector<vector<int>>();
    cnf->resize(clause_count);

    int literal; // store the incoming literal value
    // iterate over the clauses
    for (int i = 0; i < clause_count; i++) {
        while (true) // while the ith clause gets more literals
        {
            cin >> literal;
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
