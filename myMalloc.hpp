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
    
    MemoryManager(void* ptr, size_t size);
    ~MemoryManager();
private:
    
    struct TableEntry {
        void* pointer;
        size_t size;
    };
    
    TableEntry *tableEntry;
    size_t entrySize;
    
    TableEntry hashTable[10];
    int hashTableSize = 10;
    int hashTableCapacity;
    void tableInsert(void *ptr, size_t size, size_t index);
    void growTable();
    void deleteTableElement();
    
};



#endif /* myMalloc_hpp */
