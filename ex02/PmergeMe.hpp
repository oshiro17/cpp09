#pragma once

#include <iostream>
#include <list>
#include <vector>


void PmergeMe(int *data, std::size_t size);

class Node {
private:
    bool _isLeaf;
    union Value {
        int *leaf;
        Node *inner;
    } _value;
    Node *_pair;

public:
    Node(int *value = nullptr);
    Node(Node *value);
    Node(Node const &rhs);
    ~Node();

    bool hasPair() const;
    void push(Node *node);
    Node *pop();
    int &getTypical() const;
    bool operator<(Node const &rhs) const;

    void getValue(int *&value);
    void getValue(Node *&value);
};

void printData(const std::vector<int> &data);
