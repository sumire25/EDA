#ifndef LFUCACHE_H
#define LFUCACHE_H

#include <iostream>
#include <unordered_map>
#include <string>
#include "fibonacciHeap.h"

using namespace std;

template <typename T, typename S>
class LFUCache {
private:
    FibonacciHeap<T>* heap;
    unordered_map<T, pair<Node<T>*, S>> cacheMap;
    int capacity;
public:
    explicit LFUCache(int capacity) : capacity(capacity) {
        heap = new FibonacciHeap<T>();
    }
    S get(const T& key) {
        if (cacheMap.find(key) == cacheMap.end()) {
            cerr << "Key not found: " << key << endl;
            return -1;
        }
        Node<T>* node = cacheMap[key].first;
        S value = cacheMap[key].second;
        heap->increaseKey(node, node->key + 1);
        return value;
    }
    void put(const T& key, S value) {
        if (capacity <= 0) return;
        if (cacheMap.find(key) != cacheMap.end()) {
            cacheMap[key].second = value;
            get(key);
            return;
        }
        if (cacheMap.size() >= capacity) {
            evict();
        }
        Node<T>* newNode = heap->insert(1, key);
        cacheMap[key] = {newNode, value};
    }

    /*
private:
    int capacity;
    int size;
    FibonacciHeap* heap;
    unordered_map<string, Node*> keyNodeMap;
    unordered_map<string, int> keyValueMap;

public:
    LFUCache(int capacity) : capacity(capacity), size(0) {
        heap = new FibonacciHeap();
    }

    ~LFUCache() {
        delete heap;
    }

    int get(const string& key) {
        // Check if the key exists
        if (keyValueMap.find(key) == keyValueMap.end()) {
            cerr << "Key not found: " << key << endl;
            return -1; // Key not found
        }

        Node* node = keyNodeMap[key];
        int value = keyValueMap[key];

        heap->increaseKey(node, node->key + 1);

        return value;
    }

    void put(const string& key, int value) {
        if (capacity <= 0) return;

        if (keyValueMap.find(key) != keyValueMap.end()) {
            keyValueMap[key] = value;
            get(key);
            return;
        }

        if (size >= capacity) {
            evict();
        }

        Node* newNode = heap->insert(1, key);
        keyNodeMap[key] = newNode;
        keyValueMap[key] = value;
        size++;
    }

    void evict() {
        if (size == 0) return;

        Node* minNode = heap->extractMin();
        string keyToEvict = minNode->value;

        keyValueMap.erase(keyToEvict);
        keyNodeMap.erase(keyToEvict);
        delete minNode;
        size--;
    }

    void display() const {
        cout << "Cache state: ";
        for (const auto& pair : keyValueMap) {
            cout << "{" << pair.first << ": " << pair.second << "} ";
        }
        cout << endl;
    }*/
};

#endif //LFUCACHE_H
