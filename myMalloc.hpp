//
//  myMalloc.hpp
//  MyMalloc
//
//  Created by Braden Potter on 3/24/21.
//

#ifndef myMalloc_hpp
#define myMalloc_hpp

#include <stdio.h>
#include <vector>

class MemoryManager {
public:
    
    void* allocate(size_t bytes);  // replaces malloc
    void deallocate(void* ptr);  // replaces free
    
    MemoryManager(size_t size);
    //~MemoryManager();
// private:
    
    struct TableEntry {
        void* pointer;
        size_t size;
    };
    
    TableEntry *tableEntry;
    size_t entrySize;
    
    int hashTableSize = 0;
    size_t hashTableCapacity;
    TableEntry *hashTable;
    
    void tableInsert(void *ptr, size_t size, size_t index);
    void tableRemove();
    void growTable();
    void printHashTable();
};



#endif /* myMalloc_hpp */
