#ifndef PAR_DPLL_FORMULA_H
#define PAR_DPLL_FORMULA_H

#include <vector>
#include <cstdlib>
#include <cmath>

typedef struct Formula {
    int numClauses;
    int literalSize;

    Set* clausesOf;
    Set* literalsIn;

    Set* deletedClauses;

    Set* emptyClauses;
    Set* unitClauses;

    vector<vector<int>>& the_cnf;

    explicit Formula(vector<vector<int>>& cnf) : the_cnf(cnf) {
        numClauses = cnf.size();
        literalSize = literal_size(cnf);

        clausesOf = new Set[literalSize * 2 + 1];
        literalsIn = new Set[numClauses];
        deletedClauses = new Set[numClauses];
        emptyClauses = new Set[numClauses];

        unitClauses = all_initial_unit_clauses();

        for (auto clause = 0; clause < numClauses; clause++) {
            for (auto& cnfLiteral: cnf[clause]) {
                if (cnfLiteral == 0) {
                    throw invalid_argument("CNF from_cnf_literal cannot be 0. Abort!");
                }
                auto literal = from_cnf_literal(cnfLiteral);
                literalsIn[clause].insert(literal);
                clausesOf[literal].insert(clause);
            }
        }
    }

    static int literal_size(vector<vector<int>>& cnf) {
        Set literals;
        for (auto& clauseVec: cnf) {
            for (auto& cnfLiteral: clauseVec) {
                literals.insert(abs(cnfLiteral));
            }
        }
        return literals.size();
    }

    Set* all_initial_unit_clauses() {
        auto allUnitClauses = new Set();
        for (auto c = 0; c < numClauses; c++) {
            auto clauseVec = the_cnf[c];
            if (clauseVec.size() == 1) {
                allUnitClauses->insert(c);
            }
        }
        return allUnitClauses;
    };

    [[nodiscard]] vector<vector<int>>* produce() const {
        auto cnf = new vector<vector<int>>();
        for (auto c = 0; c < numClauses; c++) {
            if (deletedClauses->contains(c)) {
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
            if (deletedClauses->contains(c)) {
                continue;
            }

            cnf->push_back(cnfClause);
            sort(cnf->back().begin(), cnf->back().end());
        }
        return cnf;
    }

    [[nodiscard]] int cnf_literal(int literal) const {
        return literal <= literalSize ? literal : -(literal - literalSize);
    }

    [[nodiscard]] int from_cnf_literal(int cnfLiteral) const {
        return cnfLiteral < 0 ? (-cnfLiteral + literalSize) : cnfLiteral;
    }

    void unit_propagation(int u) const {
        // remove every clause containing "u"
        for (auto& clauseOfU: clausesOf[u]) {
            deletedClauses->insert(clauseOfU);
            unitClauses->erase(clauseOfU);
        }

        // remove every "~u" from every clause
        auto nu = u < literalSize ? u + literalSize : u - literalSize;

        for (auto& clauseOfNu: clausesOf[nu]) {
            delete_literal_from(nu, clauseOfNu);
        }
        clausesOf[nu].clear();
    }

    void delete_literal_from(int literal, int clause) const {
        if (deletedClauses->contains(clause)) {
            return;
        }

        literalsIn[clause].erase(literal);

        // report any empty clause
        if (literalsIn[clause].empty()) {
            emptyClauses->insert(clause);
            unitClauses->erase(clause);
        }
        // report any unit clause
        if (literalsIn[clause].size() == 1) {
            unitClauses->insert(clause);
        }
    }

    [[nodiscard]] int num_of_active_clauses() const {
        return numClauses - deletedClauses->size();
    }

} Formula;


#endif //PAR_DPLL_FORMULA_H
