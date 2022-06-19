#include "node.hpp"

#ifndef LAB2_V2_PATRICIA_H
#define LAB2_V2_PATRICIA_H

const int HEADER_VALUE = -1;

class Patricia {
public:
    Patricia();

    ~Patricia();

    bool Empty();

    Node *GetHeader();

    Node *FindElement(const std::string &key);

    bool AddElement(const std::string &new_key, const unsigned long long &new_value);

    bool DeleteElement(const std::string &key);

    bool SaveToFile(Node *node, std::ofstream &oStream);

    bool LoadFromFile(std::istream &iStream);

    void Clear();

private:
    bool FirstCaseDeletion();

    bool SecondCaseDeletion(Node *parentParentDeleteNode, Node *deleteNode);

    bool ThirdCaseDeletion(Node *p, Node *q, Node *m, Node *r, Node *deleteNode);

    void DeleteNode(Node *node);

    Node *header;
};

#endif //LAB2_V2_PATRICIA_H
