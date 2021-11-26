#ifndef PAR_DPLL_INTSET_TEST_H
#define PAR_DPLL_INTSET_TEST_H

#include <cassert>
#include <vector>
#include "../intset.h"

void test_intset1() {
    IntSet intSet(5);
    assert(intSet.capacity == 5);

    intSet.insert(0);
    intSet.insert(4);
    intSet.insert(3);
    intSet.insert(2);
    assert(intSet.size == 4);

    auto iter = intSet.bag();
    assert(equal(iter->begin(), iter->end(), (vector<int>{0, 2, 3, 4}).begin()));
}

void test_intset2() {
    IntSet intSet(5);

    intSet.insert(0);
    intSet.insert(4);
    intSet.insert(4);
    intSet.insert(2);
    assert(intSet.size == 3);

    auto iter = intSet.bag();
    assert(equal(iter->begin(), iter->end(), (vector<int>{0, 2, 4}).begin()));
}

void test_intset3() {
    IntSet intSet(5);

    intSet.insert(0);
    intSet.insert(4);
    intSet.insert(4);
    intSet.insert(2);
    intSet.erase(2);
    assert(intSet.size == 2);

    auto iter = intSet.bag();
    assert(equal(iter->begin(), iter->end(), (vector<int>{0, 4}).begin()));
}

void test_intset4() {
    IntSet intSet(5);

    intSet.insert(0);
    intSet.insert(4);
    intSet.insert(4);
    intSet.insert(2);
    assert(intSet.contains(0));
    assert(intSet.contains(2));
    assert(intSet.contains(4));
    intSet.erase(2);
    assert(intSet.contains(0));
    assert(!intSet.contains(2));
    assert(intSet.contains(4));
}

void test_intset() {
    test_intset1();
    test_intset2();
    test_intset3();
    test_intset4();
}

#endif //PAR_DPLL_INTSET_TEST_H
