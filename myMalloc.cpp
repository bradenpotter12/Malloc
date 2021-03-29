//
//  myMalloc.cpp
//  MyMalloc
//
//  Created by Braden Potter on 3/24/21.
//

#include "myMalloc.hpp"
#include <sys/mman.h>
#include <iostream>

MemoryManager::MemoryManager(size_t capacity) { //
    hashTable = (TableEntry*)mmap(nullptr, capacity, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);

    hashTableCapacity = capacity;
    
//    for (int i = 0; i < hashTableCapacity; i++) {
//        hashTable[i].pointer = 0x0;
//    }
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
    
    for (int i = 0; i < hashTableCapacity; i++) {
        newTable[i].pointer = 0x0;
    }
    
    for (int i = 0; i < oldCapacity; i++) {
        newTable[i] = hashTable[i];
    }
    hashTable = newTable;
}

void MemoryManager::printHashTable() {
    for (int i = 0; i < hashTableCapacity; i++) {
        std::cout << hashTable[i].pointer << std::endl;
    }
}

