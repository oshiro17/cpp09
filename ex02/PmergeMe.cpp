#include "PmergeMe.hpp"
#include <algorithm>

Node::Node(int *value) : _isLeaf(true), _pair(nullptr) {
    _value.leaf = value;
}

Node::Node(Node *value) : _isLeaf(false), _pair(nullptr) {
    _value.inner = value;
}

Node::Node(Node const &rhs) : _isLeaf(rhs._isLeaf), _pair(rhs._pair) {
    if (rhs._isLeaf)
        _value.leaf = rhs._value.leaf;
    else
        _value.inner = rhs._value.inner;
}

Node::~Node() {}

bool Node::hasPair() const {
    return _pair != nullptr;
}

void Node::push(Node *node) {
    _pair = node;
}

Node *Node::pop() {
    Node *tmp = _pair;
    _pair = nullptr;
    return tmp;
}

int &Node::getTypical() const {
    if (_isLeaf)
        return *_value.leaf;
    else
        return _value.inner->getTypical();
}

bool Node::operator<(Node const &rhs) const {
    return getTypical() < rhs.getTypical();
}

void Node::getValue(int *&value) {
    value = _value.leaf;
}

void Node::getValue(Node *&value) {
    value = _value.inner;
}

void printData(const std::vector<int> &data) {
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << data[i];
        if (i != data.size() - 1)
            std::cout << " ";
    }
    std::cout << std::endl;
}
