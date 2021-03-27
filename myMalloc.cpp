//
//  myMalloc.cpp
//  MyMalloc
//
//  Created by Braden Potter on 3/24/21.
//

#include "myMalloc.hpp"
#include <sys/mman.h>

MemoryManager::MemoryManager(size_t size) { //
    tableEntry->pointer = (TableEntry*)mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);

    tableEntry->size = size; //size used inside the mmap
}

void* MemoryManager::allocate(size_t bytes) {
    void *ptr = mmap(nullptr, bytes, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    size_t index = std::hash<void *>()(ptr); // converts pointer to int value
    tableInsert(ptr, bytes, index % hashTableSize);
    return ptr;
}

void MemoryManager::tableInsert(void *ptr, size_t size, size_t index) {
    // check for collisions before insert
    // find index
    // check exceeded index grow table
    
    //Hashtable[index] = // struct(ptr, size);
}

