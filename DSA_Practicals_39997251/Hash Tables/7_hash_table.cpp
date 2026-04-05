#include <iostream>
#include <list>
#include <string>
#include <cmath>
using namespace std;

// ============================================================================
// ABSTRACT DATA TYPE: HASH TABLE (using Separate Chaining)
// ============================================================================
// A Hash Table is a data structure that implements an associative array -
// a structure that maps keys to values using a hash function.
// Uses separate chaining to handle collisions with linked lists.
// Time Complexity (Average):
//   - Insert: O(1)
//   - Delete: O(1)
//   - Search: O(1)
// Time Complexity (Worst - all collisions):
//   - Insert: O(n)
//   - Delete: O(n)
//   - Search: O(n)
// Space: O(n + m) where n is entries and m is table size
// ============================================================================

template <typename K, typename V>
class KeyValuePair {
public:
    K key;
    V value;
    
    KeyValuePair(K k, V v) : key(k), value(v) {}
};

template <typename K, typename V>
class HashTable {
private:
    static const int TABLE_SIZE = 20;  // Initial size of hash table
    
    // Array of lists (buckets) - each list handles collisions for a hash value
    list<KeyValuePair<K, V>>* table;
    
    // Hash function that computes index for a given key
    // Returns a value between 0 and TABLE_SIZE-1
    int hashFunction(K key) {
        hash<K> hasher;
        return hasher(key) % TABLE_SIZE;
    }

public:
    // Constructor: Initialize hash table with empty lists
    HashTable() {
        table = new list<KeyValuePair<K, V>>[TABLE_SIZE];
    }

    // Destructor: Free allocated memory
    ~HashTable() {
        delete[] table;
    }

    // Insert a key-value pair
    void insert(K key, V value) {
        int index = hashFunction(key);
        
        // Check if key already exists
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                pair.value = value;  // Update existing value
                return;
            }
        }
        
        // Key doesn't exist, add new pair
        table[index].push_back(KeyValuePair<K, V>(key, value));
    }

    // Search for a value by key
    V search(K key) {
        int index = hashFunction(key);
        
        // Search in the bucket (list) for the key
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                return pair.value;
            }
        }
        
        // Key not found, throw exception
        throw runtime_error("Key not found in hash table");
    }

    // Check if a key exists
    bool containsKey(K key) {
        int index = hashFunction(key);
        
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                return true;
            }
        }
        return false;
    }

    // Delete a key-value pair by key
    bool deleteKey(K key) {
        int index = hashFunction(key);
        
        // Search and delete in the bucket
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
                return true;
            }
        }
        return false;  // Key not found
    }

    // Print all key-value pairs in the hash table
    void print() {
        cout << "\nHash Table Contents:" << endl;
        cout << "Index | Entries" << endl;
        cout << "------|--------------------" << endl;
        
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << "     | ";
            
            if (table[i].empty()) {
                cout << "(empty)" << endl;
            } else {
                for (auto& pair : table[i]) {
                    cout << "[" << pair.key << ": " << pair.value << "] ";
                }
                cout << endl;
            }
        }
    }

    // Get the number of entries
    int size() {
        int count = 0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            count += table[i].size();
        }
        return count;
    }

    // Print details about collisions
    void printCollisionStats() {
        int collisions = 0;
        int nonEmptyBuckets = 0;
        
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (!table[i].empty()) {
                nonEmptyBuckets++;
                if (table[i].size() > 1) {
                    collisions += table[i].size() - 1;
                }
            }
        }
        
        cout << "\nCollision Statistics:" << endl;
        cout << "Non-empty buckets: " << nonEmptyBuckets << "/" << TABLE_SIZE << endl;
        cout << "Total collisions: " << collisions << endl;
        cout << "Load factor: " << (float)size() / TABLE_SIZE << endl;
    }
};

// ============================================================================
// SIMPLE HASH TABLE using Open Addressing (Linear Probing)
// ============================================================================

class SimpleHashTable {
private:
    static const int SIZE = 10;
    string keys[SIZE];
    string values[SIZE];
    bool occupied[SIZE];
    
    // Hash function
    int hash(string key) {
        int hashValue = 0;
        for (char c : key) {
            hashValue += c;
        }
        return hashValue % SIZE;
    }
    
    // Linear probing: if collision, check next position
    int findPosition(string key) {
        int index = hash(key);
        int originalIndex = index;
        
        // Search for the key or an empty spot
        while (occupied[index] && keys[index] != key) {
            index = (index + 1) % SIZE;
            if (index == originalIndex) {
                return -1;  // Table is full
            }
        }
        
        return index;
    }

public:
    SimpleHashTable() {
        for (int i = 0; i < SIZE; i++) {
            occupied[i] = false;
        }
    }

    void insert(string key, string value) {
        int index = findPosition(key);
        if (index == -1) {
            throw runtime_error("Hash table is full");
        }
        
        keys[index] = key;
        values[index] = value;
        occupied[index] = true;
    }

    string search(string key) {
        int index = findPosition(key);
        if (index == -1 || !occupied[index]) {
            throw runtime_error("Key not found");
        }
        return values[index];
    }

    void print() {
        cout << "\nSimple Hash Table (Linear Probing):" << endl;
        cout << "Index | Key     | Value" << endl;
        cout << "------|---------|----------" << endl;
        
        for (int i = 0; i < SIZE; i++) {
            cout << i << "     | ";
            if (occupied[i]) {
                cout << keys[i] << "   | " << values[i];
            } else {
                cout << "(empty) | (empty)";
            }
            cout << endl;
        }
    }
};

// ============================================================================
// DEMONSTRATION
// ============================================================================
int main() {
    cout << "=== HASH TABLE ADT (Separate Chaining) ===" << endl;
    
    HashTable<string, int> phoneBook;
    
    // Insert entries
    cout << "\nInserting entries..." << endl;
    phoneBook.insert("Alice", 1001);
    phoneBook.insert("Bob", 1002);
    phoneBook.insert("Charlie", 1003);
    phoneBook.insert("David", 1004);
    phoneBook.insert("Eve", 1005);
    phoneBook.insert("Frank", 1006);
    phoneBook.insert("Grace", 1007);
    phoneBook.insert("Henry", 1008);
    
    phoneBook.print();
    phoneBook.printCollisionStats();
    
    // Search operations
    cout << "\nSearch operations:" << endl;
    cout << "Alice's number: " << phoneBook.search("Alice") << endl;
    cout << "David's number: " << phoneBook.search("David") << endl;
    
    // Check existence
    cout << "\nKey existence check:" << endl;
    cout << "Contains 'Grace': " << (phoneBook.containsKey("Grace") ? "YES" : "NO") << endl;
    cout << "Contains 'Zoe': " << (phoneBook.containsKey("Zoe") ? "YES" : "NO") << endl;
    
    // Update value
    cout << "\nUpdating Alice's number to 2001:" << endl;
    phoneBook.insert("Alice", 2001);
    cout << "Alice's new number: " << phoneBook.search("Alice") << endl;
    
    // Delete
    cout << "\nDeleting Bob's entry:" << endl;
    phoneBook.deleteKey("Bob");
    cout << "Total entries: " << phoneBook.size() << endl;
    
    // ========== SIMPLE HASH TABLE EXAMPLE ==========
    cout << "\n\n=== SIMPLE HASH TABLE (Linear Probing) ===" << endl;
    
    SimpleHashTable stable;
    
    cout << "\nInserting entries..." << endl;
    stable.insert("name", "John");
    stable.insert("age", "25");
    stable.insert("city", "NYC");
    stable.insert("job", "Engineer");
    stable.insert("hobby", "Coding");
    
    stable.print();
    
    // Search
    cout << "\n\nSearching:" << endl;
    cout << "name: " << stable.search("name") << endl;
    cout << "job: " << stable.search("job") << endl;
    
    return 0;
}
