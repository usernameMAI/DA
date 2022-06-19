#include <fstream>
#include "patricia.hpp"
#include "bits.hpp"

Patricia::Patricia() {
    header = nullptr;
}

Patricia::~Patricia() {
    Clear();
}

bool Patricia::Empty() {
    return header == nullptr;
}

Node *Patricia::GetHeader() {
    return header;
}

Node *Patricia::FindElement(const std::string &key) {
    if (Empty()) {
        return nullptr;
    }
    if (header->GetKey() == key) {
        return header;
    }
    Node *parentNode = header;
    Node *findNode = header->GetLeftNode();
    //    пока не прошли по обратной ссылке
    while (findNode->GetIndex() > parentNode->GetIndex()) {
        parentNode = findNode;
        if (BitNumberIndexIsOne(key, findNode->GetIndex())) {
            findNode = findNode->GetRightNode();
        } else {
            findNode = findNode->GetLeftNode();
        }
    }
    return findNode;
}

bool Patricia::AddElement(const std::string &new_key, const unsigned long long &new_value) {
    if (Empty()) {
        Node *new_node = new Node(new_key, new_value, HEADER_VALUE);
        header = new_node;
        new_node->SetRightNode(nullptr);
        new_node->SetLeftNode(new_node);
    } else {
        Node *node = FindElement(new_key);
        if (node->GetKey() == new_key) {
            return false;
        }
        int newIndex = FirstDifferenceInBit(new_key, node->GetKey());
        Node *newNode = new Node(new_key, new_value, newIndex);
//      ищем место, куда будем вставлять новый элемент
        Node *parentNode = header;
        Node *findNode = header->GetLeftNode();
        while (findNode->GetIndex() > parentNode->GetIndex() and findNode->GetIndex() < newNode->GetIndex()) {
            parentNode = findNode;
            if (BitNumberIndexIsOne(newNode->GetKey(), findNode->GetIndex())) {
                findNode = findNode->GetRightNode();
            } else {
                findNode = findNode->GetLeftNode();
            }
        }
        if (BitNumberIndexIsOne(newNode->GetKey(), newNode->GetIndex())) {
            newNode->SetRightNode(newNode);
            if (parentNode == findNode) {
                newNode->SetLeftNode(parentNode);
            } else {
                newNode->SetLeftNode(findNode);
            }
        } else {
            newNode->SetLeftNode(newNode);
            if (parentNode == findNode) {
                newNode->SetRightNode(parentNode);
            } else {
                newNode->SetRightNode(findNode);
            }
        }
        if (parentNode->GetRightNode() == findNode) {
            parentNode->SetRightNode(newNode);
        } else {
            parentNode->SetLeftNode(newNode);
        }
    }
    return true;
}

bool Patricia::DeleteElement(const std::string &key) {
    if (Empty()) {
        return false;
    }
//   1 кейс -- patricia == header
    if (header->GetLeftNode() == header and header->GetKey() == key) {
        return FirstCaseDeletion();
    }
//    поиск родителя
    Node *parent = this->header;    // q
    Node *deleteNode = this->header->GetLeftNode();
    Node *parentParentDeleteNode;
    while (deleteNode->GetIndex() > parent->GetIndex()) {
        parentParentDeleteNode = parent;
        parent = deleteNode;
        if (BitNumberIndexIsOne(key, deleteNode->GetIndex())) {
            deleteNode = deleteNode->GetRightNode();
        } else {
            deleteNode = deleteNode->GetLeftNode();
        }
    }
    if (deleteNode->GetKey() != key) {
        return false;
    }
//      2 кейс -- удаляемая нода имеет ссылку на себя
    if (parent == deleteNode) {
        return SecondCaseDeletion(parentParentDeleteNode, deleteNode);
    }
//    3 кейс
    return ThirdCaseDeletion(deleteNode, parent,
                             parentParentDeleteNode, header, header->GetLeftNode());
}

void Patricia::DeleteNode(Node* node) {
    if (node->GetLeftNode()->GetIndex() > node->GetIndex()) {
        DeleteNode(node->GetLeftNode());
    }
    if (node->GetRightNode()->GetIndex() > node->GetIndex()) {
        DeleteNode(node->GetRightNode());
    }
    delete node;
    node = nullptr;
}

void Patricia::Clear() {
    if (header == nullptr) {
        return;
    }
    if (header != header->GetLeftNode()) {
        DeleteNode(header->GetLeftNode());
    }
    delete header;
    header = nullptr;
}

bool Patricia::SaveToFile(Node *node, std::ofstream &oStream) {
    if (!node) {
        return true;
    }
    int index = node->GetIndex();
    int keySize = node->GetKey().size();
    unsigned long long nodeValue = node->GetValue();
    oStream.write((char *) (&keySize), sizeof(int));
    oStream.write(node->GetKey().c_str(), sizeof(char) * node->GetKey().size());
    oStream.write((char *) (&index), sizeof(int));
    oStream.write((char *) (&nodeValue), sizeof(unsigned long long));
    if (node->GetLeftNode() and node->GetLeftNode()->GetIndex() > index) {
        SaveToFile(node->GetLeftNode(), oStream);
    }
    if (node->GetRightNode() and node->GetRightNode()->GetIndex() > index) {
        SaveToFile(node->GetRightNode(), oStream);
    }
    return true;
}

bool Patricia::LoadFromFile(std::istream &iStream) {
    int keySize;
    Patricia loadTree;
    while (iStream.read((char *) &keySize, sizeof(keySize))) {
        std::string key;
        key.resize(keySize);
        unsigned long long value;
        int index;
        iStream.read((char *) key.data(), keySize);
        iStream.read((char *) &index, sizeof(index));
        iStream.read((char *) &value, sizeof(value));
        loadTree.AddElement(key, value);
    }
    std::swap(*this, loadTree);
    return true;
}

bool Patricia::FirstCaseDeletion() {
    delete header;
    header = nullptr;
    return true;
}

bool Patricia::SecondCaseDeletion(Node* parentParentDeleteNode, Node* deleteNode) {
    if (parentParentDeleteNode->GetRightNode() == deleteNode) {
        if (deleteNode->GetRightNode() == deleteNode) {
            parentParentDeleteNode->SetRightNode(deleteNode->GetLeftNode());
        } else {
            parentParentDeleteNode->SetRightNode(deleteNode->GetRightNode());
        }
    } else {
        if (deleteNode->GetRightNode() == deleteNode) {
            parentParentDeleteNode->SetLeftNode(deleteNode->GetLeftNode());
        } else {
            parentParentDeleteNode->SetLeftNode(deleteNode->GetRightNode());
        }
    }
    delete deleteNode;
    deleteNode = nullptr;
    return true;
}

bool Patricia::ThirdCaseDeletion(Node *p, Node *q, Node *m, Node *r, Node *deleteNode) {
    while (deleteNode->GetIndex() > r->GetIndex()) {
        r = deleteNode;
        if (BitNumberIndexIsOne(q->GetKey(), deleteNode->GetIndex())) {
            deleteNode = deleteNode->GetRightNode();
        } else {
            deleteNode = deleteNode->GetLeftNode();
        }
    }
    bool ComingFromRight = BitNumberIndexIsOne(r->GetKey(), q->GetIndex());
    if (r->GetRightNode() == q) {
        r->SetRightNode(p);
    } else {
        r->SetLeftNode(p);
    }
    if (m->GetRightNode() == q) {
        if (ComingFromRight) {
            m->SetRightNode(q->GetRightNode());
        } else {
            m->SetRightNode(q->GetLeftNode());
        }
    } else {
        if (ComingFromRight) {
            m->SetLeftNode(q->GetRightNode());
        } else {
            m->SetLeftNode(q->GetLeftNode());
        }
    }
    p->SetKey(q->GetKey());
    p->SetValue(q->GetValue());
    delete q;
    q = nullptr;
    return true;
}
