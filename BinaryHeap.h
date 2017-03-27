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

    void fixBinaryHeap(int i);
    void fixBinaryHeapUp(int i);
    void fixBinaryHeapDown(int i);

    void createBH();

    int getSize() const;

    void loadFile(string name);
    void addElement(int value, int notUsed);
    void deleteElement(int value);
    int findElement(int value);

    friend ostream & operator<<(ostream & os , const BinaryHeap & a);

    void printBH(string sp, string sn, int v, ostream &os)const;

    void menu();

    void print(std::ostream &str) const;

    int getElement(int position) override;

};