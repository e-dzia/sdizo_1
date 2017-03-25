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
    ofstream fout;
    fout.open("results_add_100.txt", ios::out);
    int n = 10000;
    createFile(n);
    chrono::time_point<chrono::system_clock> start, end;
    DataStructure * ds;
    std::chrono::duration<double> addTime;

    //mainMenu();

    fout << "ARRAY:\n";
    for (int i = 0; i < 100; i++){
        ds = new Array;
        start = chrono::system_clock::now();
        ds->loadFile("numbers.txt");
        end = chrono::system_clock::now();
        addTime = end - start;
        fout << addTime.count() << endl;
        delete ds;
    }

    fout << "\n\nLIST:\n";
    for (int i = 0; i < 100; i++){
        ds = new List;
        start = chrono::system_clock::now();
        ds->loadFile("numbers.txt");
        end = chrono::system_clock::now();
        addTime = end - start;
        fout << addTime.count() << endl;
        delete ds;
    }


    fout << "\n\nBINARY HEAP:\n";
    for (int i = 0; i < 100; i++){
        ds = new BinaryHeap;
        start = chrono::system_clock::now();
        ds->loadFile("numbers.txt");
        end = chrono::system_clock::now();
        addTime = end - start;
        fout << addTime.count() << endl;
        delete ds;
    }

    fout << "\n\nRED BLACK TREE:\n";
    for (int i = 0; i < 100; i++){
        ds = new RedBlackTree;
        start = chrono::system_clock::now();
        ds->loadFile("numbers.txt");
        end = chrono::system_clock::now();
        addTime = end - start;
        fout << addTime.count() << endl;
        delete ds;
    }


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
    srand(time(NULL));
    ofstream fout;
    fout.open("numbers.txt", ios::out);
    if (fout.is_open()){
        fout << n << endl;
        for (int i = 0; i < n; i++){
            int element = rand()%100;
            fout << element << endl;
        }
        fout.close();
        return true;
    }
    else return false;
}