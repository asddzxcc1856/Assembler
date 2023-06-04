#include "HashTable.h"
using namespace std;

template <typename KeyType>
struct hash {
    size_t operator()(const KeyType& key) const {
        // ----------------------------------------
		// Custom hash function implementation
        // ----------------------------------------
		size_t hashValue = 0;
        // ----------------------------------------
        // Convert the key to a string
        // ----------------------------------------
		string keyString = key;
        
		// ----------------------------------------
        // Calculate the hash value by summing the ASCII values of the characters
        // ----------------------------------------
		for (int i = 0 ; i < keyString.length() ; i++) {
            hashValue += static_cast<size_t>(keyString[i]);
        }
        // ----------------------------------------
        // Return the hash value
		// ----------------------------------------
        return hashValue;
    }
};

template<typename KeyType, typename ValueType, size_t TableSize, typename Hash = hash<KeyType> >
class HashTable {
private:
	// ----------------------------------------
    // Hash table entry
	// ----------------------------------------
    struct Entry {
        KeyType key;
        ValueType value;
        Entry* next;
        Entry(const KeyType& k, const ValueType& v) : key(k), value(v), next(0) {}
    };

    Entry* table[TableSize];

    size_t getBucketIndex(const KeyType& key) const {
        Hash hashFunction;
        return hashFunction(key) % TableSize;
    }

public:
    HashTable() {
        for (size_t i = 0; i < TableSize; ++i) {
            table[i] = 0;
        }
    }

    void insert(const KeyType& key, const ValueType& value) {
        size_t bucketIndex = getBucketIndex(key);
		// ----------------------------------------
        // Check if the key already exists in the bucket
		// ----------------------------------------
        Entry* entry = table[bucketIndex];
        while (entry) {
            if (entry->key == key) {
				// ----------------------------------------
                // Key already exists, update the value
				// ----------------------------------------
                entry->value = value;
                return;
            }
            entry = entry->next;
        }
		// ----------------------------------------
        // Key does not exist, add a new entry
		// ----------------------------------------
        entry = new Entry(key, value);
        entry->next = table[bucketIndex];
        table[bucketIndex] = entry;
    }

    bool erase(const KeyType& key) {
        size_t bucketIndex = getBucketIndex(key);
		// ----------------------------------------
        // Find and remove the key if it exists in the bucket
        // ----------------------------------------
		Entry* entry = table[bucketIndex];
        Entry* prev = 0;
        while (entry) {
            if (entry->key == key) {
                if (prev)
                    prev->next = entry->next;
                else
                    table[bucketIndex] = entry->next;

                delete entry;
                return true;
            }
            prev = entry;
            entry = entry->next;
        }

        return false;
    }

    bool search(const KeyType& key, ValueType& value) const {
        size_t bucketIndex = getBucketIndex(key);
		// ----------------------------------------
        // Find the key if it exists in the bucket
        // ----------------------------------------
		Entry* entry = table[bucketIndex];
        while (entry) {
            if (entry->key == key) {
                value = entry->value;
                return true;
            }
            entry = entry->next;
        }

        return false;
    }
};
