#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
using namespace std;


class LRUCache {
public:
    int capacity;
    list<pair<string, int>> cacheList;
    unordered_map<string, list<pair<string, int>>::iterator> cacheMap;

    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(const string &key) {
        if (cacheMap.find(key) == cacheMap.end()) {
            cerr << "Key not found: " << key << endl;
            return -1;
        }
        auto it = cacheMap[key];
        int value = it->second;
        cacheList.erase(it);

        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();

        return value;
    }

    void put(const string &key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            cacheList.erase(cacheMap[key]);
        }

        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();

        if (cacheList.size() > capacity) {
            evict();
        }
    }

    void evict() {
        auto last = cacheList.back();
        cacheMap.erase(last.first);
        cacheList.pop_back();
    }

    void display() const {
        cout << "Cache state: ";
        for (const auto &entry : cacheList) {
            cout << "{" << entry.first << ", " << entry.second << "} ";
        }
        cout << endl;
    }
};

#endif //LRUCACHE_H
