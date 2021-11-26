#ifndef PAR_DPLL_INTSET_H
#define PAR_DPLL_INTSET_H

#include <vector>
#include <iterator>

using namespace std;

typedef struct IntSet {
    vector<bool> vec;
    int capacity;
    int size;

    explicit IntSet(int n) {
        vec.resize(n);
        capacity = n;
        size = 0;
    }

    IntSet() {
        capacity = 0;
        size = 0;
    }

    void insert(int v) {
        if (!vec[v]) {
            size++;
        }
        vec[v] = true;
    }

    void erase(int v) {
        if (vec[v]) {
            size--;
        }
        vec[v] = false;
    }

    bool contains(int v) {
        return vec[v];
    }

    vector<int>* bag() {
        auto b = new vector<int>(size);
        auto bi = 0;
        for (auto i = 0; i < capacity; i++) {
            if (vec[i]) {
                (*b)[bi++] = i;
            }
        }
        return b;
    }

} FixedSizeSet;

#endif //PAR_DPLL_INTSET_H
