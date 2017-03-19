//
// Created by Edzia on 2017-03-15.
//

#include "Array.h"
#include <iostream>
#include <fstream>


int Array::getSize()const {
    return this->size;
}

Array::Array() {
    this->size = 0;
    this->array = new int[Array::size];
}


Array::~Array() {
    delete [] array;
}

bool Array::addElement(int value, int position) {
    int * newArray = new int [this->getSize() +1]; //tworzy nowa tabele wieksza o 1 od obecnej
    if (position == 0){ //poczatek tabeli
        newArray[0] = value; //do miejsca na poczatku wpisuje (value)
        for (int i = 1; i < this->getSize() + 1; i++) {
            newArray[i] = this->array[i - 1]; //do pozostalych miejsc wpisuje pozostałe wartosi po kolei
        }
    }
    else if (position >= this->getSize()){ //koniec tabeli
        for (int i = 0; i < this->getSize(); i++){
            newArray[i] = this->array[i]; //przepisuje elementy tablicy do nowej
        }
        newArray[this->getSize()] = value; // dopisuje na koniec listy wartosc (value)
    }
    else {//inne miejsce tabeli
        int i = 0;
        for (; i < position; i++){
            newArray[i] = this->array[i]; //do miejsca (position) przepisuje elementy
        }
        newArray[i++] = value; //w miejsce (position) wpisuje wartosc (value)
        for (; i < this->getSize()+1; i++){
            newArray[i] = this->array[i-1]; //do reszty tablicy wpisuje dalsze elementy starej tablicy
        }
    }
    this->size++; //zwieksza (size)
    delete [] this->array; //usuwa stara tablice
    array = newArray; //do starej przypisuje nowa
    return true;
}


bool Array::deleteElement(int position) {
    int * newArray = new int [this->getSize() -1]; //tworzy nowa tabele mniejsza o 1 od obecnej
    this->size--;
    if (position == 0){ //poczatek tabeli
        for (int i = 1; i <= this->getSize(); i++){
            newArray[i-1] = this->array[i]; //do pozostalych miejsc wpisuje pozostałe wartosi (oprocz indeksu 0) po kolei
        }
    }
    else if (position == this->getSize()){ //koniec tabeli
        for (int i = 0; i <= this->getSize()-1; i++){
            newArray[i] = this->array[i]; //przepisuje elementy tablicy do nowej, bez ostatniego
        }
    }
    else {//inne miejsce tabeli
        int i = 0;
        for (; i < position; i++){
            newArray[i] = this->array[i]; //do miejsca (position) przepisuje elementy
        }
        for (; i < this->getSize(); i++){
            newArray[i] = this->array[i+1]; //do reszty tablicy wpisuje dalsze elementy starej tablicy oprócz tego usuniętego
        }
    }
    delete [] this->array; //usuwa stara tablice
    array = newArray; //do starej przypisuje nowa
    return true;
}


int Array::findElement(int value) {
    for (int i = 0; i < this->getSize(); i++){
        if (this->array[i] == value) return i;
    }
    return -1;
}


ostream & operator<< ( ostream & os , const Array & a ){
    for (int i = 0; i < a.getSize(); i++){
        os << a.array[i] << " ";
    }
    return os;
}


bool Array::loadFile(string name) {
    ifstream fin;
    fin.open(name.c_str(), ios::in);
    if (fin.is_open()){
        int size = 0;
        fin >> size;
        for (int i = 0; i < size; i++){
            int element;
            fin >> element;
            this->addElement(element,this->getSize());
        }
        fin.close();
        return true;
    }
    else return false;
}

int& Array::operator[](int n) {
    return array[n];
}

int &Array::operator[](int n) const {
    return array[n];
}

void Array::menu() {
    cout << "MENU - tablica\n"
            "1. Zbuduj z pliku.\n"
            "2. Usun.\n"
            "3. Dodaj.\n"
            "4. Znajdz.\n"
            "5. Wyswietl.\n"
            "6. Wyjdz do glownego menu.\n"
            "Prosze wpisac odpowiednia liczbe.";
    int chosen;
    cin >> chosen;
    switch(chosen){
        case 1:
            this->loadFile("numbers.txt");
            break;
        case 2:
            cout << "Prosze podac pozycje liczby do usuniecia.\n";
            int position;
            cin >> position;
            this->deleteElement(position);
            break;
        case 3:
            cout << "Prosze podac liczbe do wpisania.\n";
            cin >> position;
            cout << "Prosze podac pozycje do wpisania liczby.\n";
            int number;
            cin >> number;
            this->addElement(position,number);
            break;
        case 4:
            cout << "Prosze podac liczbe do znalezienia.\n";
            cin >> number;
            if (this->findElement(number)!=-1)
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
