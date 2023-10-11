#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
    list<int> cacheList;
    unordered_map<int, list<int>::iterator> cacheMap;
    int cacheSize;

public:
    LRUCache(int size) {
        cacheSize = size;
    }

    void refer(int pageNumber) {
        // Check if the page is already in the cache
        if (cacheMap.find(pageNumber) == cacheMap.end()) {
            // Check if the cache is full
            if (cacheList.size() == cacheSize) {
                // Remove the least recently used page from cache
                int lastPage = cacheList.back();
                cacheList.pop_back();
                cacheMap.erase(lastPage);
            }
        } else {
            // Page is already in cache, move it to the front of the list
            cacheList.erase(cacheMap[pageNumber]);
        }

        // Add the page to the front of the list and update the cache map
        cacheList.push_front(pageNumber);
        cacheMap[pageNumber] = cacheList.begin();
    }

    void displayCache() {
        for (auto it = cacheList.begin(); it != cacheList.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }
};

int main() {
    // Create an LRU cache with size 3
    LRUCache cache(3);

    // Simulate page requests
    cache.refer(1);
    cache.displayCache(); // Output: 1
    cache.refer(2);
    cache.displayCache(); // Output: 2 1
    cache.refer(3);
    cache.displayCache(); // Output: 3 2 1
    cache.refer(4);
    cache.displayCache(); // Output: 4 3 2
    cache.refer(1);
    cache.displayCache(); // Output: 1 4 3

    return 0;
}
