#ifndef PAR_DPLL_FORMULA_H
#define PAR_DPLL_FORMULA_H

#include <vector>

typedef struct Formula {
    int numClauses;
    int literalSize;

    Set* clausesOf;
    Set* literalsIn;

    Formula(int nClauses, int lSize) {
        numClauses = nClauses;
        literalSize = lSize;
        clausesOf = new Set[lSize * 2 + 1];
        literalsIn = new Set[nClauses];
    }

    static int literal_size(vector<vector<int>>& cnf) {
        Set literals;
        for (auto& clauseVec: cnf) {
            for (auto& literal: clauseVec) {
                literals.insert(literal < 0 ? -literal : literal);
            }
        }
        return literals.size();
    }

    static Formula* convert(vector<vector<int>>& cnf) {
        auto numClauses = cnf.size();
        auto literalSize = literal_size(cnf);

        auto f = new Formula(numClauses, literalSize);

        for (auto clause = 0; clause < numClauses; clause++) {
            for (auto& cnfLiteral: cnf[clause]) {
                if (cnfLiteral == 0) {
                    throw invalid_argument("CNF literal cannot be 0. Abort!");
                }
                auto literal = cnfLiteral < 0 ? (-cnfLiteral + literalSize) : cnfLiteral;
                f->literalsIn[clause].insert(literal);
                f->clausesOf[literal].insert(clause);
            }
        }

        return f;
    }

    vector<vector<int>>* produce() const {
        auto cnf = new vector<vector<int>>();
        for (auto c = 0; c < numClauses; c++) {
            cnf->push_back(vector<int>());
            auto& cnfClause = cnf->at(c);
            for (auto& literal: literalsIn[c]) {
                cnfClause.push_back(cnf_literal(literal));
            }
            sort(cnfClause.begin(), cnfClause.end());
        }

        return cnf;
    }

    vector<vector<int>>* produce2() const {
        auto cnf = new vector<vector<int>>();
        cnf->resize(numClauses);
        for (auto literal = 0; literal < literalSize * 2 + 1; literal++) {
            auto clausesOfLiteral = clausesOf[literal];
            for (auto clause: clausesOfLiteral) {
                cnf->at(clause).push_back(cnf_literal(literal));
            }
        }

        for (auto c = 0; c < numClauses; c++) {
            auto& cnfClause = cnf->at(c);
            sort(cnfClause.begin(), cnfClause.end());
        }
        return cnf;
    }

    int cnf_literal(int literal) const { return literal <= literalSize ? literal : -(literal - literalSize); }

} Formula;


#endif //PAR_DPLL_FORMULA_H
