#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "patricia.hpp"
#include "node.hpp"

void ToLower (std::string &key) {
    for (char &i: key) {
        i = std::tolower(i);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    using namespace std;
    Patricia tree;
    string command;
    while (cin >> command) {
        if (command == "+") {
            string key;
            unsigned long long value;
            cin >> key >> value;
            ToLower(key);
            if (tree.AddElement(key, value)) {
                cout << "OK\n";
            } else {
                cout << "Exist\n";
            }
        } else if (command == "-") {
            string key;
            cin >> key;
            ToLower(key);
            if (tree.DeleteElement(key)) {
                cout << "OK\n";
            } else {
                cout << "NoSuchWord\n";
            }
        } else if (command == "!") {
            string saveOrLoad;
            string pathToFile;
            cin >> saveOrLoad >> pathToFile;
            if (saveOrLoad == "Save") {
                ofstream stream(pathToFile, ios::binary);
                tree.SaveToFile(tree.GetHeader(), stream);
                stream.close();
            } else {
                ifstream stream(pathToFile, ios::binary);
                tree.Clear();
                tree.LoadFromFile(stream);
                stream.close();
            }
            cout << "OK\n";
        } else {
            ToLower(command);
            Node *node = tree.FindElement(command);
            if (node != nullptr and node->GetKey() == command) {
                cout << "OK: " << node->GetValue() << "\n";
            } else {
                cout << "NoSuchWord\n";
            }
        }
    }
}
