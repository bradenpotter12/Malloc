//
//  myMalloc.cpp
//  MyMalloc
//
//  Created by Braden Potter on 3/24/21.
//

#include "myMalloc.hpp"
#include <sys/mman.h>
#include <iostream>

MemoryManager::MemoryManager(size_t capacity) {
    TableEntry *tempPtr = (TableEntry*)mmap(nullptr, capacity, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);

    hashTable = tempPtr;
    hashTableCapacity = capacity;
    
    // store hashtable's ptr and size in the hashtable;
    //size_t index = std::hash<void *>()(tempPtr);
    //tableInsert(tempPtr, capacity, index % hashTableCapacity);
    
}

void* MemoryManager::allocate(size_t bytes) {
    void *ptr = mmap(nullptr, bytes, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    size_t index = std::hash<void *>()(ptr); // converts pointer to int value
    tableInsert(ptr, bytes, index % hashTableCapacity);
    return ptr;
}

void MemoryManager::tableInsert(void *ptr, size_t size, size_t index) {
    
    TableEntry tableEntry;
    tableEntry.pointer = ptr;
    tableEntry.size = size;
    
    // check for collisions before insert
    size_t firstIndex = index;
    while (1) {
        
        if (hashTable[index].pointer == 0x0) {
            hashTable[index] = tableEntry;
            hashTableSize++;
            break;
        }
        else {
            index++;
            index = index % hashTableCapacity;
        }
        
        // check if probed every index in the hashtable
        if (index == firstIndex) {
            break;
        }
    }
    
    // check if table needs to grow
    double amountUsed = ((double)hashTableSize / (double)hashTableCapacity);
    
    if (amountUsed > .6) {
        growTable();
    }
    
}

void MemoryManager::growTable() {
    size_t oldCapacity = hashTableCapacity;
    hashTableCapacity *= 2;
    TableEntry *newTable = (TableEntry*)mmap(nullptr, hashTableCapacity, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    
    // storing ptr for new table in the new hashTable
    //size_t index = std::hash<void *>()(newTable);
    //tableInsert(newTable, hashTableCapacity, index % hashTableCapacity);
    
    for (int i = 0; i < hashTableCapacity; i++) {
        newTable[i].pointer = 0x0;
    }
    
    // copy values from old hashtable to new hashtable
    for (int i = 0; i < oldCapacity; i++) {
        // don't copy lazy deletes
        if (hashTable[i].pointer != nullptr) {
            newTable[i] = hashTable[i];
            deallocate(hashTable[i].pointer);  // deallocate ptr in old hashTable
        }
    }
    
    TableEntry *tempPtr = hashTable;
    hashTable = newTable;
    deallocate(tempPtr);  // deallocate original hashTable
    newTable = nullptr;
}

void MemoryManager::printHashTable() {
    for (int i = 0; i < hashTableCapacity; i++) {
        std::cout << hashTable[i].pointer << std::endl;
    }
}

void MemoryManager::deallocate(void* ptr) {
    
    for (int i = 0; i < hashTableCapacity; i++) {
        
        // find pointer in hash table
        if (ptr == hashTable[i].pointer) {
            
            // deallocate memory
            munmap(ptr, hashTable[i].size);
            
            // remove element from hashTable
            hashTable[i].pointer = nullptr;
            hashTable[i].size = 0x0;
            hashTableSize--;
            break;
        }
    }
}

// unmap pointers in hashtable
// then unmap hashtable itself in the destructor
MemoryManager::~MemoryManager() {
    for (int i = 0; i < hashTableCapacity; i++) {
        if (hashTable[i].pointer != 0x0 && hashTable[i].pointer != nullptr) {
            deallocate(hashTable[i].pointer);
        }
    }
    deallocate(hashTable);
}



