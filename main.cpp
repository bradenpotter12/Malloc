//
//  main.cpp
//  MyMalloc
//
//  Created by Braden Potter on 3/24/21.
//

#include <iostream>
#include "myMalloc.hpp"

void testTable(int numOfTimes) {
    MemoryManager m(10);
    for (int i = 0; i < numOfTimes; i++) {
        m.printHashTable();
        std::cout << "\n";
        m.allocate(15);
    }
}

int main(int argc, const char * argv[]) {
    
    MemoryManager m(10);
    
    m.printHashTable();
    std::cout << "\n";
    void* ptr = m.allocate(5);
    m.printHashTable();
    std::cout << "\n";
    m.deallocate(ptr);
    m.printHashTable();
    std::cout << "\n";
    m.allocate(5);
    m.printHashTable();
    std::cout << "\n";
    m.allocate(5);
    m.printHashTable();
    std::cout << "\n";
    m.allocate(5);
    m.printHashTable();
    std::cout << "\n";
    m.allocate(5);
    m.printHashTable();
    std::cout << "\n";
    m.allocate(5);
    m.printHashTable();
    std::cout << "\n";
    m.allocate(5);
    m.printHashTable();
    std::cout << "\n";
    // Table grows after 7th element is added which is
    // greater than 60% of capacity of 10 elements
    m.allocate(5);
    m.printHashTable();
    std::cout << "\n";
    
    return 0;
}
