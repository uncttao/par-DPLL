#ifndef PAR_DPLL_FORMULA_H
#define PAR_DPLL_FORMULA_H

#include <vector>
#include <cstdlib>

enum ClauseStatus {
    Present, Deleted
};

typedef struct Formula {
    int numClauses;
    int literalSize;

    Set* clausesOf;
    Set* literalsIn;

    ClauseStatus* clauseStatuses;

    Formula(int nClauses, int lSize) {
        numClauses = nClauses;
        literalSize = lSize;
        clausesOf = new Set[lSize * 2 + 1];
        literalsIn = new Set[nClauses];
        clauseStatuses = (ClauseStatus*) calloc(nClauses, sizeof(ClauseStatus));
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

    [[nodiscard]] vector<vector<int>>* produce() const {
        auto cnf = new vector<vector<int>>();
        for (auto c = 0; c < numClauses; c++) {
            if (clauseStatuses[c] == Deleted) {
                continue;
            }

            cnf->push_back(vector<int>());
            auto& cnfClause = cnf->back();
            for (auto& literal: literalsIn[c]) {
                cnfClause.push_back(cnf_literal(literal));
            }
            sort(cnfClause.begin(), cnfClause.end());
        }

        return cnf;
    }

    [[nodiscard]] vector<vector<int>>* produce2() const {
        auto _cnf = new vector<vector<int>>();
        _cnf->resize(numClauses);
        for (auto literal = 0; literal < literalSize * 2 + 1; literal++) {
            auto clausesOfLiteral = clausesOf[literal];
            for (auto clause: clausesOfLiteral) {
                _cnf->at(clause).push_back(cnf_literal(literal));
            }
        }

        auto cnf = new vector<vector<int>>();
        for (auto c = 0; c < numClauses; c++) {
            auto& cnfClause = _cnf->at(c);
            if (clauseStatuses[c] == Present) {
                cnf->push_back(cnfClause);
                sort(cnf->back().begin(), cnf->back().end());
            }
        }
        return cnf;
    }

    [[nodiscard]] int cnf_literal(int literal) const {
        return literal <= literalSize ? literal : -(literal - literalSize);
    }

} Formula;


#endif //PAR_DPLL_FORMULA_H
