#include <string>

#ifndef LAB2_V2_NODE_H
#define LAB2_V2_NODE_H

class Node {
public:
    Node(const std::string &new_key, const unsigned long long &new_value, int new_index);

    ~Node();

    void SetLeftNode(Node *newLeftNode);

    void SetRightNode(Node *newRightNode);

    void SetKey(const std::string &new_key);

    void SetValue(const unsigned long long &new_value);

    void SetIndex(int new_index);

    Node *GetLeftNode();

    Node *GetRightNode();

    [[nodiscard]] std::string GetKey() const;

    [[nodiscard]] unsigned long long GetValue() const;

    [[nodiscard]] int GetIndex() const;

private:
    std::string key;
    unsigned long long value;
    int index;
    Node *right;
    Node *left;
};

#endif //LAB2_V2_NODE_H
