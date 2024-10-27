#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

template <typename T>
class Node {
public:
    int key;
    int degree;
    T value;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    bool mark;

    Node(int key, const T& value) : key(key), value(value), degree(0), parent(nullptr), child(nullptr),
                    left(this), right(this), mark(false) {}
};

template <typename T>
class FibonacciHeap {
private:
    Node<T>* min;
    int n;

    void link(Node<T>* y, Node<T>* x) {
        y->left->right = y->right;
        y->right->left = y->left;
        y->parent = x;
        if (x->child == nullptr) {
            x->child = y;
            y->left = y;
            y->right = y;
        } else {
            x->child->left->right = y;
            y->left = x->child->left;
            y->right = x->child;
            x->child->left = y;
        }
        x->degree++;
        y->mark = false;
    }
    void consolidate() {
        int maxDegree = static_cast<int>(log2(n)) + 1;
        vector<Node<T>*> A(maxDegree, nullptr);
        vector<Node<T>*> rootList;
        Node<T>* x = min;
        do {
            rootList.push_back(x);
            x = x->right;
        } while (x != min);
        for (int i = 0; i < rootList.size(); i++) {
            x = rootList[i];
            int d = x->degree;
            while (A[d] != nullptr) {
                Node<T>* y = A[d];
                if (x->key > y->key)
                    swap(x, y);
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
        }
        min = nullptr;
        for (int i = 0; i < maxDegree; i++) {
            if (A[i] != nullptr) {
                if (min == nullptr) {
                    min = A[i];
                    min->left = min;
                    min->right = min;
                } else {
                    min->left->right = A[i];
                    A[i]->left = min->left;
                    A[i]->right = min;
                    min->left = A[i];
                    if (A[i]->key < min->key)
                        min = A[i];
                }
            }
        }
    }
    void cut(Node<T>* x, Node<T>* y) {
        y->degree--;
        if (y->degree == 0)
            y->child = nullptr;
        else if (y->child == x)
            y->child = x->right == x ? nullptr : x->right;
        x->left->right = x->right;
        x->right->left = x->left;
        // Add x to the root list
        min->left->right = x;
        x->left = min->left;
        x->right = min;
        min->left = x;
        x->parent = nullptr;
        x->mark = false;
    }
    void cascadingCut(Node<T>* y) {
        Node<T>* z = y->parent;
        if (z != nullptr) {
            if (!y->mark)
                y->mark = true;
            else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }
public:
    FibonacciHeap() : min(nullptr), n(0) {}
    int size() const {return n;}
    Node<T>* findMin(){return min;}
    void insert(Node<T>* x) {
        x->degree = 0;
        x->parent = nullptr;
        x->child = nullptr;
        x->mark = false;
        if (min == nullptr) {
            min = x;
            x->left = x;
            x->right = x;
        } else {
            min->left->right = x;
            x->left = min->left;
            x->right = min;
            min->left = x;
            if (x->key < min->key) {
                min = x;
            }
        }
        n++;
    }
    Node<T>* extractMin() {
        Node<T>* z = min;
        if (z != nullptr) {
            Node<T>* x = z->child;
            if (x != nullptr) {
                do {
                    Node<T>* next = x->right;
                    min->left->right = x;
                    x->left = min->left;
                    x->right = min;
                    min->left = x;
                    x->parent = nullptr;
                    x = next;
                } while (x != z->child);
            }
            z->left->right = z->right;
            z->right->left = z->left;
            if (z == z->right) {
                min = nullptr;
            } else {
                min = z->right;
                consolidate();
            }
            n--;
        }
        return z;
    }
    void decreaseKey(Node<T>* x, int k) {
        if (k > x->key) {
            cerr << "New key is greater than current key." << endl;
            return;
        }
        x->key = k;
        Node<T>* y = x->parent;
        if (y != nullptr && x->key < y->key) {
            cut(x, y);
            cascadingCut(y);
        }
        if (x->key < min->key)
            min = x;
    }
    void deleteNode(Node<T>* x) {
        decreaseKey(x, INT_MIN);
        extractMin();
    }
    void increaseKey(Node<T>* x, int k) {
        if (k < x->key) {
            cerr << "New key is smaller than current key." << endl;
            return;
        }
        deleteNode(x);
        x->key = k;
        insert(x);
    }
    void printNode(Node<T>* node, int depth = 0) {
        if (node == nullptr) return;

        Node<T>* start = node;
        do {
            // Print the node's details with indentation based on depth level
            for (int i = 0; i < depth; ++i) cout << "  ";
            cout << "Key: " << node->key << ", Value: " << node->value
                 << ", Degree: " << node->degree
                 << ", Marked: " << (node->mark ? "true" : "false") << endl;

            // If the node has children, print them recursively
            if (node->child != nullptr) {
                for (int i = 0; i < depth + 1; ++i) cout << "  ";
                cout << "Children of " << node->key << ":" << endl;
                printNode(node->child, depth + 1);
            }

            node = node->right; // Move to the next node in the circular list
        } while (node != start);
    }
    void printHeap() {
        if (min == nullptr) {
            cout << "The heap is empty." << endl;
            return;
        }
        cout << "Root List of the Fibonacci Heap:" << endl;
        printNode(min); // Print all nodes in the root list
    }
};

#endif //FIBONACCIHEAP_H
