#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <unordered_map>
#include <list>
using namespace std;

class lruCache {
    unordered_map<int> cache;
    list<int> lru;
    int capacity;
public:

};

#endif //LRUCACHE_H
