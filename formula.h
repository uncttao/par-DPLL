#ifndef PAR_DPLL_FORMULA_H
#define PAR_DPLL_FORMULA_H

#include <vector>
#include <cstdlib>
#include <cmath>

typedef struct Formula {
    int numClauses;
    int literalSize;

    vector<Set > clausesOf;
    vector<Set > literalsIn;

    Set activeLiterals;
    Set pureLiterals;

    Set deletedClauses;
    Set emptyClauses;
    Set unitClauses;

    vector<vector<int>>& the_cnf;

    explicit Formula(vector<vector<int>>& cnf) : the_cnf(cnf) {
        numClauses = cnf.size();
        literalSize = literal_size(cnf);

        clausesOf.resize(literalSize * 2 + 1);
        literalsIn.resize(numClauses);

        all_initial_literals();
        all_initial_pure_literals();
        all_initial_unit_clauses();
        all_initial_empty_clauses();

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

    Set* from_cnf_literals(Set& cnfLiterals) const {
        Set* sCopy = new Set();
        for (auto& item: cnfLiterals) {
            sCopy->insert(from_cnf_literal(item));
        }
        return sCopy;
    }

    void all_initial_unit_clauses() {
        for (auto c = 0; c < numClauses; c++) {
            auto clauseVec = the_cnf[c];
            if (clauseVec.size() == 1) {
                unitClauses.insert(c);
            }
        }
    };

    void all_initial_empty_clauses() {
        for (auto c = 0; c < numClauses; c++) {
            auto clauseVec = the_cnf[c];
            if (clauseVec.empty()) {
                emptyClauses.insert(c);
            }
        }
    }

    void all_initial_literals() {
        for (auto& clauseVec: the_cnf) {
            for (auto& cnfLiteral: clauseVec) {
                if (cnfLiteral == 0) {
                    throw invalid_argument("CNF literal cannot be 0. Abort!");
                }
                activeLiterals.insert(from_cnf_literal(cnfLiteral));
            }
        }
    }

    void all_initial_pure_literals() {
        Set positives;
        Set negatives;
        for (auto& clauseVec: the_cnf) {
            for (auto& cnfLiteral: clauseVec) {
                if (cnfLiteral == 0) {
                    throw invalid_argument("CNF literal cannot be 0. Abort!");
                }
                if (cnfLiteral > 0) {
                    positives.insert(cnfLiteral);
                } else {
                    negatives.insert(cnfLiteral);
                }
            }
        }
        auto purePos = set_diff(positives, *set_neg(negatives));
        auto pureNeg = set_diff(negatives, *set_neg(positives));
        pureLiterals = *from_cnf_literals(*set_add(*purePos, *pureNeg));
    }

    [[nodiscard]] vector<vector<int>>* produce() const {
        auto cnf = new vector<vector<int>>();
        for (auto c = 0; c < numClauses; c++) {
            if (deletedClauses.contains(c)) {
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
            if (deletedClauses.contains(c)) {
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

    void unit_propagation(int u) {
        // remove every clause containing "u"
        auto clausesOfU = clausesOf[u];   // need to make a copy first
        for (auto& clauseOfU: clausesOfU) {
            delete_clause(clauseOfU);
        }

        // remove every "~u" from every clause
        auto nu = neg_literal(u);

        auto clausesOfNu = clausesOf[nu];   // need to make a copy first
        for (auto& clauseOfNu: clausesOfNu) {
            delete_literal_from(nu, clauseOfNu);
        }
    }

    [[nodiscard]] int neg_literal(int u) const {
        return u <= literalSize ? u + literalSize : u - literalSize;
    }

    void on_literal_change(int literal) {
        // maintain pureLiterals
        int nLiteral = neg_literal(literal);

        if (clausesOf[literal].empty()) {
            if (clausesOf[nLiteral].empty()) {
                pureLiterals.erase(literal);
                pureLiterals.erase(nLiteral);
            } else {
                pureLiterals.insert(nLiteral);
            }
        } else {
            if (clausesOf[nLiteral].empty()) {
                pureLiterals.insert(literal);
            } else {
                pureLiterals.erase(literal);
                pureLiterals.erase(nLiteral);
            }
        }

        // maintain activeLiterals
        if (clausesOf[literal].empty()) {
            activeLiterals.erase(literal);
        } else {
            activeLiterals.insert(literal);
        }
    }

    void delete_clause(int clause) {
        deletedClauses.insert(clause);
        unitClauses.erase(clause);
        emptyClauses.erase(clause);

        // remove all literals from clause
        for (auto& literal: literalsIn[clause]) {
            clausesOf[literal].erase(clause);
            on_literal_change(literal);
        }

        // clear the clause
        literalsIn[clause].clear();
    }

    void delete_literal_from(int literal, int clause) {
        literalsIn[clause].erase(literal);
        clausesOf[literal].erase(clause);
        on_literal_change(literal);

        // report any unit clause
        if (literalsIn[clause].size() == 1) {
            unitClauses.insert(clause);
            return;
        }
        // report any empty clause
        if (literalsIn[clause].empty()) {
            emptyClauses.insert(clause);
            unitClauses.erase(clause);
        }
    }

    void add_unit_clause(int literal) {
        auto newClause = numClauses++;
        literalsIn.resize(numClauses);
        literalsIn[newClause].insert(literal);
        clausesOf[literal].insert(newClause);

        unitClauses.insert(newClause);

        on_literal_change(literal);
    }

    void pure_literal_assign(int literal) {
        auto clauses = clausesOf[literal];
        for (auto& clause: clauses) {
            delete_clause(clause);
        }
    }

    [[nodiscard]] bool is_all_pure_literals() const {
        return pureLiterals.size() >= activeLiterals.size();
    }

} Formula;


#endif //PAR_DPLL_FORMULA_H
