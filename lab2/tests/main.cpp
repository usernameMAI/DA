#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "patricia.hpp"
#include "node.hpp"
#include <chrono>

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
    int cnt;
    cin >> cnt;

    std::chrono::steady_clock::time_point addStart = std::chrono::steady_clock::now();
    for (int i = 0; i < cnt; ++i) {
        string key;
        unsigned long long value;
        cin >> key >> value;
        ToLower(key);
        tree.AddElement(key, value);
    }
    std::chrono::steady_clock::time_point addFinish = std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point findStart = std::chrono::steady_clock::now();
    for (int i = 0; i < cnt; ++i) {
        cin >> command;
        ToLower(command);
        Node *node = tree.FindElement(command);
    }
    std::chrono::steady_clock::time_point findFinish = std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point popStart = std::chrono::steady_clock::now();
    for (int i = 0; i < cnt; ++i) {
        string key;
        cin >> key;
        ToLower(key);
        tree.DeleteElement(key);
    }
    std::chrono::steady_clock::time_point popFinish = std::chrono::steady_clock::now();

    unsigned timeOfAdd = std::chrono::duration_cast<std::chrono::milliseconds>(addFinish - addStart).count();
    unsigned timeOfFind = std::chrono::duration_cast<std::chrono::milliseconds>(findFinish - findStart).count();
    unsigned timeOfPop = std::chrono::duration_cast<std::chrono::milliseconds>(popFinish - popStart).count();

    cout << "Time to push PATRICIA " << cnt << " elements: " << timeOfAdd << endl;
    cout << "Time to find PATRICIA " << cnt << " elements: " << timeOfFind << endl;
    cout << "Time to pop PATRICIA " << cnt << " elements: " << timeOfPop << endl;


    map<string, unsigned long long> myMap;


    addStart = std::chrono::steady_clock::now();
    for (int i = 0; i < cnt; ++i) {
        string key;
        unsigned long long value;
        cin >> key >> value;
        ToLower(key);
        if (myMap.find(key) != myMap.end()) {
            myMap[key] = value;
        }
    }
    addFinish = std::chrono::steady_clock::now();

    findStart = std::chrono::steady_clock::now();
    for (int i = 0; i < cnt; ++i) {
        string key;
        cin >> key;
        ToLower(key);
        unsigned long long value = myMap[key];
    }
    findFinish = std::chrono::steady_clock::now();

    popStart = std::chrono::steady_clock::now();
    for (int i = 0; i < cnt; ++i) {
        string key;
        cin >> key;
        ToLower(key);
        myMap.erase(key);
    }
    popFinish = std::chrono::steady_clock::now();

    timeOfAdd = std::chrono::duration_cast<std::chrono::milliseconds>(addFinish - addStart).count();
    timeOfFind = std::chrono::duration_cast<std::chrono::milliseconds>(findFinish - findStart).count();
    timeOfPop = std::chrono::duration_cast<std::chrono::milliseconds>(popFinish - popStart).count();

    cout << "Time to push MAP " << cnt << " elements: " << timeOfAdd << endl;
    cout << "Time to find MAP " << cnt << " elements: " << timeOfFind << endl;
    cout << "Time to pop MAP " << cnt << " elements: " << timeOfPop << endl;
}
