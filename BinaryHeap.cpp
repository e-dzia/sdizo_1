//
// Created by Edzia on 2017-03-06.
//

#include "BinaryHeap.h"
#include <cmath>
#include <cstdlib>


BinaryHeap::BinaryHeap() {
    //Array array;
    //cout << "Nowe BH " << &this->array << endl;
}

BinaryHeap::~BinaryHeap() {
    //cout << "Usuwam BH " << &this->array << endl;
    //array.~Array();
}

int BinaryHeap::getSize() const{
    return array.getSize();
}

bool BinaryHeap::loadFile(string name) {
    array.loadFile(name);
    for(int i = this->getSize()-1; i >= 0; i--)
        this->fixBinaryHeap(i);
    return true;
}

bool BinaryHeap::addElement(int value, int notUsed) {
    array.addElement(value,this->getSize());
    for(int i = this->getSize()-1; i >= 0; i--)
        this->fixBinaryHeap(i);
    return true;
}

bool BinaryHeap::deleteElement(int value) {
    if (array.findElement(value) == -1) return false;
    int tmp = array[array.findElement(value)]; //wartosc elementu
    array[array.findElement(value)] = array[array.getSize()-1];
    array[array.getSize()-1] = tmp;
    array.deleteElement(array.getSize());
    for(int i = this->getSize()-1; i >= 0; i--)
        this->fixBinaryHeap(i);
    return true;
}

int BinaryHeap::findElement(int value) {
    return array.findElement(value);
}

bool BinaryHeap::fixBinaryHeap(int i) {
    int largest;
    int left = 2*i + 1;
    int right = 2*i + 2;
    if (left < this->getSize() && array[left]>array[i]){
        largest = left;
    }
    else {
        largest = i;
    }
    if (right < this->getSize() && array[largest]<array[right]){
        largest = right;
    }
    if (largest!=i){
        int tmp = array[i];
        array[i] = array[largest];
        array[largest] = tmp;
        fixBinaryHeap(largest);
    }
    return false;
}

bool BinaryHeap::fixBinaryHeapUp(int i) {
    int n = this->getSize()-1;
    int v = array[n];
    //int i = n; //pozycja wstawianego elementu
    int j = (i-1)/2; //indeks rodzica
    while (i > 0 && array[j] < v){
        array[i] = array[j];
        i = j;
        j = (i-1)/2;
    }
    array[i] = v;
    return false;
}

bool BinaryHeap::fixBinaryHeapDown(int i) {
    int n = this->getSize();
    int v = array[n]; //ostatni element
    //int i = 0;
    int j = 2*i+1;
    while(j < n){
        if (j+1 < n && array[j+1] > array[j]){
            j++;//szukamy wiekszego syna
        }
        if (v >= array[j]) break;
        array[i] = array[j];
        i = j;
        j = 2*i+1;
    }
    array[i] = v;
    return true;
}

bool BinaryHeap::createBH() { //algorytm Floyda
    for (int i = (this->getSize()-2)/2; i>=0; i++){
        this->fixBinaryHeapDown(i);
    }
    return false;
}

void BinaryHeap::menu() {
    cout << "MENU - kopiec binarny\n"
            "1. Zbuduj z pliku.\n"
            "2. Usun.\n"
            "3. Dodaj.\n"
            "4. Znajdz.\n"
            "5. Wyswietl.\n"
            "6. Wyjdz do glownego menu.\n"
            "Prosze wpisac odpowiednia liczbe.";
    cin.clear();
    int chosen = 6;
    cin >> chosen;
    switch(chosen){
        case 1:
            this->loadFile("numbers.txt");
            break;
        case 2:
            cout << "Prosze podac wartosc liczby do usuniecia.\n";
            int position;
            cin >> position;
            this->deleteElement(position);
            break;
        case 3:
            cout << "Prosze podac liczbe do wpisania.\n";
            cin >> position;
            this->addElement(position,position);
            break;
        case 4:
            cout << "Prosze podac liczbe do znalezienia.\n";
            cin >> position;
            if (this->findElement(position)!=-1)
                cout << "Znaleziono.\n";
            else cout << "Nie znaleziono.\n";
            break;
        case 5:
            cout << *this << endl;
            break;
        case 6:
            return;
        default:
            cout << "Prosze podac poprawna liczbe.\n";
            cin.clear();
            cin.sync();
            break;
    }
    this->menu();
}

void BinaryHeap::printBH(string sp, string sn, int v, ostream &os) const {
    string s;
    string cr = "  ", cl= "  ", cp = "  ";
    cr[0] = 218; cr[1] = 196;
    cl[0] = 192; cl[1] = 196;
    cp[0] = 179;

    if(v < this->getSize())
    {
        s = sp;
        if(sn == cr) s[s.length() - 2] = ' ';
        printBH(s + cp, cr, 2 * v + 2, os);

        s = s.substr(0,sp.length()-2);

        cout << s << sn << this->array[v] << endl;

        s = sp;
        if(sn == cl) s[s.length() - 2] = ' ';
        printBH(s + cp, cl, 2 * v + 1, os);
    }
}

ostream &operator<<(ostream &os, const BinaryHeap &a) {
    a.printBH("","",0, os);
    return os;
}

void BinaryHeap::print(std::ostream &str) const {
    str << *this;
}

