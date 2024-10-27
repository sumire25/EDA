#ifndef FIFO_H
#define FIFO_H

#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

class Fifo {
public:
    int capacity;
    queue<string> cacheQueue;
    unordered_map<string, int> cacheMap;

    Fifo(int capacity) {
        this->capacity = capacity;
    }

    int get(const string &key) {
        if (cacheMap.find(key) == cacheMap.end()) {
            cerr << "Key not found: " << key << endl;
            return -1;
        }
        return cacheMap[key];
    }

    void put(const string &key, int value) {
        if (cacheMap.find(key) == cacheMap.end()) {
            cacheQueue.push(key);
        }
        cacheMap[key] = value;
        if (cacheQueue.size() > capacity) {
            evict();
        }
    }

    void evict() {
        string key = cacheQueue.front();
        cacheMap.erase(key);
        cacheQueue.pop();
    }
};

#endif //FIFO_H
