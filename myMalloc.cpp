//
//  myMalloc.cpp
//  MyMalloc
//
//  Created by Braden Potter on 3/24/21.
//

#include "myMalloc.hpp"
#include <sys/mman.h>
#include <iostream>

MemoryManager::MemoryManager(size_t size) { //
    //tableEntry->pointer = (TableEntry*)mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);

    //tableEntry->size = size; //size used inside the mmap
    
    for (int i = 0; i < hashTableCapacity; i++) {
        hashTable[i].pointer = 0x0;
    }
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
    
    // check exceeded index grow table
    
    
    
}

void MemoryManager::growTable() {
    hashTableCapacity *= 2;
    TableEntry newTable[hashTableCapacity];
    for (int i = 0; i < hashTableSize; i++) {
        newTable[i] = hashTable[i];
    }
    //hashTable = newTable;
    TableEntry* temp = newTable;
    //hashTable = temp;
}

void MemoryManager::printHashTable() {
    for (int i = 0; i < hashTableCapacity; i++) {
        std::cout << hashTable[i].pointer << std::endl;
    }
}

