//
// Created by Edzia on 2017-03-06.
//

#ifndef SDIZO_1_LIST_H
#define SDIZO_1_LIST_H

#include <iostream>
#include <fstream>
#include "cmake-build-debug/DataStructure.h"

using namespace std;

//alokowane dynamicznie :/
/*
 * dodawanie elementu:
 *  poczatek listy
 *  koniec listy
 *  losowe miejsce
 * usun element
 * znajdz element
 *
 */

struct ElemList{
    int value;
    ElemList * next;
    ElemList * prev;
};


class List: public DataStructure{
private:
    ElemList * head;
    int size;
public:
    List(); //konstruktor domyślny
    ~List(); //destruktor

    int getSize() const;

    void loadFile(string name);
    void addElement(int afterValue, int value); //za afterValue trzeba wstawic value
    void deleteElement(int value); //podana wartosc do usuniecia
    int findElement(int value);

    int getElement(int position);

    friend ostream & operator<<(ostream & os , const List & a);

    void menu();

    void print(std::ostream &str) const override;
};

#endif //SDIZO_1_LIST_H
