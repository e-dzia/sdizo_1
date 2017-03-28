#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>

#include "Array.h"
#include "List.h"
#include "BinaryHeap.h"
#include "RedBlackTree.h"

bool createFile(int n);
void mainMenu();

using namespace std;

int main() {
    srand(time(NULL));

    //std::chrono::time_point<chrono::high_resolution_clock > start, end;
   // std::chrono::duration<double> addTime;

    int n = 10000;

    cout << "Prosze podac wielkosc struktur.\n";
    cin >> n;

    createFile(n);

    mainMenu();

    return 0;
}

void mainMenu() {
    cout << "Prosze wybrac strukture.\n"
            "1. Tablica.\n"
            "2. Lista.\n"
            "3. Kopiec binarny.\n"
            "4. Drzewo czerwono-czarne.\n"
            "5. Wyjscie z programu.\n";
    int chosen = 0;
    cin >> chosen;
    switch(chosen){
        case 1:{
            Array a;
            a.menu();
            break;
        }
        case 2: {
            List l;
            l.menu();
            break;
        }
        case 3: {
            BinaryHeap bh;
            bh.menu();
            break;
        }
        case 4:{
            RedBlackTree rbt;
            rbt.menu();
            break;
        }
        case 5:{
            exit(0);
            break;
        }
        default: {
            cout << "Prosze podac poprawna wartosc.\n";
            cin.clear();
            cin.sync();
            break;
        }
    }
    mainMenu();
}

bool createFile(int n) {
    ofstream fout;
    fout.open("numbers.txt", ios::out);
    if (fout.is_open()){
        fout << n << endl;
        for (int i = 0; i < n; i++){
            int element = rand()%100000;
            fout << element << endl;
        }
        fout.close();
        return true;
    }
    else return false;
}