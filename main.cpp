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
    ofstream foutArray;
    foutArray.open("results_array.txt", ios::out);
    ofstream foutList;
    foutList.open("results_list.txt", ios::out);
    ofstream foutBH;
    foutBH.open("results_bh.txt", ios::out);
    ofstream foutRBT;
    foutRBT.open("results_rbt.txt", ios::out);

    std::chrono::time_point<chrono::high_resolution_clock > start, end;
    std::chrono::duration<double> addTime;

    DataStructure * ds;

    Array a;




    int add = 100;
    int search = 100;
    int del = 100;
    int n = 1000;

    mainMenu();

    createFile(n);
   // ds = new BinaryHeap;
    //ds->loadFile("numbers.txt");
    ds = new RedBlackTree;
    ds->loadFile("numbers.txt");


    for (int i = 0; i < 100; i++){
        cout << i << endl;
        createFile(n);

        cout << "Dzialam\n";
        ifstream fin;
        fin.open("numbers.txt", ios::out);
        a.deleteAll();
        int size;
        fin >> size;
        for (int i = 0; i < size; i++){
            int element;
            fin >> element;
            a.addElement(element,0);
        }
        //cout << a << endl;
        //cout << a[0] << endl;
        fin.close();
        cout << "Wciaz\n";
        //cout << *ds;

        //cout << "Elo1\n";
        start = chrono::high_resolution_clock::now();
        for(int j = 0; j < add; j++){
            //cout << "Dodaje " << a[a.getSize()-j*2-1] << endl;
            ds->addElement(a[j],0);
        }
        end = chrono::high_resolution_clock::now();
        //cout << "Elo2\n";
        addTime = end - start;
        foutArray << addTime.count() << " "; //czas dodawania

        cout << "Elo3\n";
        start = chrono::high_resolution_clock::now();
        for(int j = 0; j < search; j++){
            ds->findElement(a[a.getSize()-j-1]);
        }
        end = chrono::high_resolution_clock::now();
        //cout << "Elo4\n";
        addTime = end - start;
        foutArray << addTime.count() << " "; //czas szukania

        cout << "Elo5\n";
        start = chrono::high_resolution_clock::now();
        for(int j = 0; j < del; j++){
            //cout << "Chce usunac " << a[j+100] << " ";
            ds->deleteElement(a[j+100]);
            //cout << *ds;
        }
        end = chrono::high_resolution_clock::now();
        //cout << "Elo6\n";
        addTime = end - start;
        foutArray << addTime.count() << " "; //czas usuwania

        //cout << "Elo7\n";
        foutArray << endl;
        cout << "Elo8\n";
        //delete ds;
        cout << "End\n";
    }

    foutArray.close();
    foutList.close();
    foutBH.close();
    foutRBT.close();
//    fin.close();

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