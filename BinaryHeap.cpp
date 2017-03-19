//
// Created by Edzia on 2017-03-06.
//

#include "BinaryHeap.h"
#include <cmath>

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

ostream &operator<<(ostream &os, const BinaryHeap &a) {
    //TODO: wyswietlanie drzewa binarnego lepiej
    os << a.array;
    os << endl;
    int m = a.getSize();
    int n = log2(m);
    for (int j = 1; j < m; j*=2){
        for (int i = 0; i < n; i++){
            os << '\t';
        }
        for (int i = 0; i < j; i++){
            if (j-1+i < m){
                os << a.array[j-1+i] << '\t';
                for (int k = 0; k < n; k++){
                    os << '\t';
                }
            }

        }
        n--;

        os << endl;
    }
    return os;
}

BinaryHeap::BinaryHeap() {
    Array array;
}

BinaryHeap::~BinaryHeap() {
    array.~Array();
}

bool BinaryHeap::fixBinaryHeap(int i) {
   // this->fixBinaryHeapUp();
   // this->fixBinaryHeapDown();
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
    cout << "No elo, naprawa w gore " << this->array << endl;
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
    /*
    * Lista kroków:
K01: 	Jeśli n = 0, to zakończ 	; kopiec jest pusty
K02: 	n ← n - 1 	; kopiec będzie zawierał o 1 element mniej
K03: 	v ← T[n] 	; w v zapamiętujemy ostatni element kopca
K04: 	i ← 0 	; przeszukiwanie drzewa rozpoczynamy od korzenia
K05: 	j ← 1 	; j wskazuje lewego syna
K06: 	Dopóki j < n: wykonuj K07...K11 	; idziemy w dół kopca
K07: 	    Jeśli (j + 1 < n) (T[j + 1] > T[j]), to j ← j + 1 	; szukamy większego syna
K08: 	    Jeśli v ≥ T[j], to Idź do K12 	; jeśli warunek kopca spełniony, wychodzimy z pętli
K09: 	    T[i] ← T[j] 	; inaczej kopiujemy większego syna do ojca
K10: 	    i ← j 	; przechodzimy na pozycję większego syna
K11: 	    j ← 2j + 1 	; j wskazuje lewego syna
K12 	T[i] ← v 	; umieszczamy v w kopcu
K13: 	Zakończ
    */
    cout << "No elo, naprawa w dol " << this->array << endl;
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
        cout << "No elo, koniec petli naprawy w dol " << this->array << endl;
    }
    array[i] = v;
    cout << "No elo, koniec naprawy w dol " << this->array << endl;
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
    int chosen = 5;
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
