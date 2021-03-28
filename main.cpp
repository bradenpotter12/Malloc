//
//  main.cpp
//  MyMalloc
//
//  Created by Braden Potter on 3/24/21.
//

#include <iostream>
#include "myMalloc.hpp"

void testTable(int numOfTimes) {
    MemoryManager m(1);
    for (int i = 0; i < numOfTimes; i++) {
        m.printHashTable();
        std::cout << "\n";
        m.allocate(15);
    }
}

int main(int argc, const char * argv[]) {
    
    testTable(11);
    
    return 0;
}
