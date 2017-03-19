//
// Created by Edzia on 2017-03-16.
//

#ifndef SDIZO_1_DATASTRUCTURE_H
#define SDIZO_1_DATASTRUCTURE_H

#include <iostream>

using namespace std;

class DataStructure{
public:
    virtual int getSize() const = 0;

    virtual bool loadFile(string name) = 0;
    virtual bool addElement(int value, int position) = 0;
    virtual bool deleteElement(int position) = 0;
    virtual int findElement(int value) = 0;

    virtual void menu()= 0;

  //  virtual friend ostream & operator<<(ostream & os , const DataStructure & a) = 0;

};

#endif //SDIZO_1_DATASTRUCTURE_H
