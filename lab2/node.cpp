#include "node.hpp"

Node::Node(const std::string &new_key, const unsigned long long &new_value, const int new_index) {
    key = new_key;
    value = new_value;
    index = new_index;
    right = left = nullptr;
}

Node::~Node() {
    right = left = nullptr;
}

void Node::SetLeftNode(Node *newLeftNode) {
    left = newLeftNode;
}

void Node::SetRightNode(Node *newRightNode) {
    right = newRightNode;
}

Node* Node::GetLeftNode() {
    return left;
}

Node* Node::GetRightNode() {
    return right;
}

void Node::SetKey(const std::string &new_key) {
    key = new_key;
}

void Node::SetValue(const unsigned long long &new_value) {
    value = new_value;
}

void Node::SetIndex(const int new_index) {
    index = new_index;
}

std::string Node::GetKey() const{
    return key;
}

unsigned long long Node::GetValue() const {
    return value;
}

int Node::GetIndex() const {
    return index;
}
