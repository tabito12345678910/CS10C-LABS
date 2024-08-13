#include "Node.h"

Node::Node(const string &key) {
    small = key;
    large = "";
    left = nullptr;
    middle = nullptr;
    right = nullptr;
    parent = nullptr;
}

bool Node::isFull() const {
    return !large.empty();
}

bool Node::hasTwoChildren() const {
    return left && middle && right;
}
