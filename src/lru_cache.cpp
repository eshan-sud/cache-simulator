
#include <iostream>
#include <unordered_map>

using namespace std;

// Implementation of a node in a doubly linked list
class Node {
public:
    int key, value;
    Node* prev;
    Node* next;

    Node(int k, int v) {
        key = k;
        value = v;
        prev = nullptr;
        next = nullptr;
    }
};


// Implementation of LRU Cache
class LRUCache {
private:
    unordered_map<int, Node*> cache;  // Hash map for O(1) lookup
    int capacity;  // Maximum cache size
    Node* head;    // Dummy head of doubly linked list
    Node* tail;    // Dummy tail of doubly linked list

public:
    LRUCache(int cap) {
        capacity = cap;

        // Create dummy head and tail nodes
        head = new Node(-1, -1);
        tail = new Node(-1, -1);

        head->next = tail;
        tail->prev = head;
    }
    // Function to remove a node from the doubly linked list
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    // Function to insert a node right after the head (making it most recently used)
    void insertAtFront(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
    int get(int key) {
        // If key is not in the cache, return -1
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        // Retrieve the node from the cache
        Node* node = cache[key];
        // Move the accessed node to the front (MRU)
        removeNode(node);
        insertAtFront(node);
        return node->value; // Return the value of the key
    }
    void put(int key, int value) {
        // If key already exists, update its value and move it to front
        if (cache.find(key) != cache.end()) {
            Node* existingNode = cache[key];
            existingNode->value = value;
            removeNode(existingNode);
            insertAtFront(existingNode);
            return;
        }
        // If the cache is full, remove the least recently used (LRU) node
        if (cache.size() >= capacity) {
            Node* lruNode = tail->prev; // The node before the dummy tail is LRU
            cache.erase(lruNode->key); // Remove from hashmap
            removeNode(lruNode); // Remove from linked list
            delete lruNode; // Free memory
        }
        // Insert the new node at the front (MRU position)
        Node* newNode = new Node(key, value);
        insertAtFront(newNode);
        cache[key] = newNode; // Add to hashmap
    }
};



int main() {
    LRUCache lru(3); // Create an LRU cache with a capacity of 3

    lru.put(1, 100);
    lru.put(2, 200);
    lru.put(3, 300);

    cout << "Get 1: " << lru.get(1) << endl; // Expected: 100

    lru.put(4, 400); // This should evict key 2 (Least Recently Used)

    cout << "Get 2: " << lru.get(2) << endl; // Expected: -1 (since key 2 was evicted)
    cout << "Get 3: " << lru.get(3) << endl; // Expected: 300
    cout << "Get 4: " << lru.get(4) << endl; // Expected: 400

    lru.put(5, 500); // This should evict key 1

    cout << "Get 1: " << lru.get(1) << endl; // Expected: -1 (since key 1 was evicted)
    cout << "Get 5: " << lru.get(5) << endl; // Expected: 500

    return 0;
}

