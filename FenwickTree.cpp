// FenwickTree.cpp
#include "FenwickTree.h"

FenwickTree::FenwickTree(int n) : size(n) {
    tree.resize(n + 1, 0); // 1-based indexing
}

void FenwickTree::update(int index, int delta) {
    while (index <= size) {
        tree[index] += delta;
        index += index & -index;
    }
}

int FenwickTree::query(int index) const {
    int sum = 0;
    while (index > 0) {
        sum += tree[index];
        index -= index & -index;
    }
    return sum;
}

int FenwickTree::rangeQuery(int left, int right) const {
    return query(right) - query(left - 1);
}

int FenwickTree::total() const {
    return query(size);
}
