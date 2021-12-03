#ifndef PAR_DPLL_INTSET_H
#define PAR_DPLL_INTSET_H

#include <vector>
#include <cstdlib>
#include <functional>

using namespace std;

typedef struct IntSet {
    vector<bool> vec;
    int capacity;
    int s;

    IntSet() {
        capacity = 0;
        s = 0;
    }

    void resize(int n) {
        vec.resize(n);
    }

    void reserve(int n) {
        vec.reserve(n);
    }

    void insert(int v) {
        if (v + 1 > capacity) {
            vec.resize(v + 1);
            capacity = v + 1;
        }
        if (!vec[v]) {
            s++;
        }
        vec[v] = true;
    }

    void erase(int v) {
        if (v >= capacity) {
            return;
        }
        if (vec[v]) {
            s--;
        }
        vec[v] = false;
    }

    [[nodiscard]] bool contains(int v) const {
        if (v >= capacity) {
            return false;
        }
        return vec[v];
    }

    [[nodiscard]] int size() const {
        return s;
    }

    [[nodiscard]] bool empty() const {
        return s <= 0;
    }

    void clear() {
        for (auto i = 0; i < capacity; i++) {
            vec[i] = false;
        }
        s = 0;
    }

    [[nodiscard]] int first() const {
        for (auto i = 0; i < capacity; i++) {
            if (vec[i]) {
                return i;
            }
        }
        throw invalid_argument("trying to get first of empty IntSet!");
    }

    void iterate(function<void(int)> const& func) const {
        int b[s];
        auto bi = 0;
        for (auto i = 0; i < capacity; i++) {
            if (vec[i]) {
                b[bi++] = i;
            }
        }
        auto s1 = s;
        for (auto i = 0; i < s1; i++) {
            func(b[i]);
        }
    }

    [[nodiscard]] vector<int>& bag() const {
        auto b = new vector<int>(s);
        auto bi = 0;
        for (auto i = 0; i < capacity; i++) {
            if (vec[i]) {
                (*b)[bi++] = i;
            }
        }
        return *b;
    }

} IntSet;

#endif //PAR_DPLL_INTSET_H
