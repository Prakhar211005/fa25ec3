//
// Created by Manju Muralidharan on 11/22/25.
//

#ifndef FA25EC3_TREE_H
#define FA25EC3_TREE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

template <typename U>
class Node {
public:
    string id;
    U data;
    vector<Node<U>*> children;

    Node(const string &nodeID, const U &value)
            : id(nodeID), data(value) {}
};

template <typename T>
class Tree {
private:
    Node<T> *root;
    vector<Node<T> *> allNodes;

    // Helper trim function
    string trim(const string &s) const {
        size_t start = 0;
        while (start < s.size() && isspace((unsigned char)s[start])) start++;
        size_t end = s.size();
        while (end > start && isspace((unsigned char)s[end - 1])) end--;
        return s.substr(start, end - start);
    }

    // To find a node by id
    Node<T>* findNode(const string &id) {
        string s = trim(id);
        for (auto n : allNodes) {
            if (n->id == s) return n;
        }
        return nullptr;
    }

public:
    Tree() : root(nullptr) {}

    void createRoot(const string &id, const T &value) {
        if (root != nullptr) {
            cerr << "Warning: root already exists (id=" << root->id << "). createRoot ignored.\n";
            return;
        }
        string cleanID = trim(id);
        Node<T> *n = new Node<T>(cleanID, value);
        root = n;
        allNodes.push_back(n);
    }

    void addNode(const string &parentID, const string &childID, const T &value) {
        string pID = trim(parentID);
        string cID = trim(childID);

        Node<T> *parent = findNode(pID);
        if (!parent) {
            cerr << "Warning: parent " << pID << " not found. addNode skipped for child '" << cID << "'.\n";
            return;
        }

        Node<T> *child = findNode(cID);
        if (!child) {
            child = new Node<T>(cID, value);
            allNodes.push_back(child);
        }

        // Avoid duplicate child pointers under the same parent
        if (find(parent->children.begin(), parent->children.end(), child) == parent->children.end()) {
            parent->children.push_back(child);
        }
    }

    void printAll() const {
        if (allNodes.empty()) {
            cout << "Tree is empty.\n";
            return;
        }

        cout << "===== Story Tree =====\n";
        for (const auto n : allNodes) {
            cout << "Node " << n->id << ": " << trim(n->data) << "\n";
            if (n->children.empty()) {
                cout << "  Child -> (none)\n\n";
            } else {
                cout << "  Children:\n";
                for (const auto c : n->children) {
                    cout << "    -> " << c->id << "\n";
                }
                cout << "\n";
            }
        }
        cout << "======================\n";
    }

    ~Tree() {
        for (auto n : allNodes) {
            delete n;
        }
        allNodes.clear();
        root = nullptr;
    }
};

#endif //FA25EC3_TREE_H
