//
// Created by Edzia on 2017-03-06.
//

#include "cmake-build-debug/DataStructure.h"
#include "Array.h"

#ifndef SDIZO_1_BINARYHEAP_H
#define SDIZO_1_BINARYHEAP_H

#endif //SDIZO_1_BINARYHEAP_H

class BinaryHeap: public DataStructure{
private:
    Array array;
public:
    BinaryHeap();
    ~BinaryHeap();

    bool fixBinaryHeap(int i);
    bool fixBinaryHeapUp(int i);
    bool fixBinaryHeapDown(int i);

    bool createBH();

    int getSize() const;

    bool loadFile(string name);
    bool addElement(int value, int notUsed);
    bool deleteElement(int position);
    int findElement(int value);

    friend ostream & operator<<(ostream & os , const BinaryHeap & a);

    void menu();

};