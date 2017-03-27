//
// Created by Edzia on 2017-03-16.
//

#ifndef SDIZO_1_DATASTRUCTURE_H
#define SDIZO_1_DATASTRUCTURE_H

#include <iostream>

using namespace std;

class DataStructure{
public:
    virtual ~DataStructure(){};

    virtual int getSize() const = 0;

    virtual void loadFile(string name) = 0;
    virtual void addElement(int value, int position) = 0;
    virtual void deleteElement(int position) = 0;
    virtual int findElement(int value) = 0;

    virtual int getElement(int position) = 0;

    virtual void menu()= 0;

    virtual void print(std::ostream& str) const = 0;

    friend std::ostream& operator<<(std::ostream& str, DataStructure const& data)
    {
        data.print(str);
        return str;
    }

    //virtual friend ostream & operator<<(ostream & os , const DataStructure & a) = 0;

};

#endif //SDIZO_1_DATASTRUCTURE_H
