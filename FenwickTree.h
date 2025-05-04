// FenwickTree.h
#pragma once
#include <vector>

class FenwickTree {
private:
    std::vector<int> tree;
    int size;

public:
    FenwickTree(int n);

    void update(int index, int delta);
    int query(int index) const;
    int rangeQuery(int left, int right) const;
    int total() const;
};
