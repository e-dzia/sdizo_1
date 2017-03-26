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
    ofstream foutArray;
    foutArray.open("results_array.txt", ios::out);
    ofstream foutList;
    foutList.open("results_lisrt.txt", ios::out);
    ofstream foutBH;
    foutBH.open("results_bh.txt", ios::out);
    ofstream foutRBT;
    foutRBT.open("results_rbt.txt", ios::out);

    ifstream fin;
    fin.open("numbers2.txt", ios::out);
    Array a;
    int size;
    fin >> size;
    for (int i = 0; i < 1000; i++){
        int element;
        fin >> element;
        a.addElement(element,0);
    }
    fin.close();

    int del = 100;
    int search = 100;
    int n = 1000;

    std::chrono::time_point<chrono::system_clock> start, end;
    std::chrono::duration<double> addTime;
    DataStructure * ds;

    //mainMenu();

    for (int i = 0; i < 100; i++){
        cout << i << endl;
        createFile(n);

        //##########################################TABLICA####################################################################
        ds = new Array;
        start = chrono::system_clock::now();
        ds->loadFile("numbers.txt");
        end = chrono::system_clock::now();
        addTime = end - start;
        foutArray << addTime.count() << " "; //czas dodawania 4000 elementów

       // if (i==0) cout << "Array####################################################################\n" << *ds << endl;

        start = chrono::system_clock::now();
        for(int j = 0; j < search; j++){
            ds->findElement(a[j]);
        }
        end = chrono::system_clock::now();
        addTime = end - start;
        foutArray << addTime.count() << " "; //czas szukania 100 elementów

        start = chrono::system_clock::now();
        for(int j = 0; j < del; j++){
            ds->deleteElement(j+100);
        }
        end = chrono::system_clock::now();
        addTime = end - start;
        foutArray << addTime.count() << " "; //czas usuwania 100 elementów

        foutArray << endl;
        delete ds;

        cout << "Lista\n";

        //##########################################LISTA###################################################################
        ds = new List;
        start = chrono::system_clock::now();
        ds->loadFile("numbers.txt");
        end = chrono::system_clock::now();
        addTime = end - start;
        foutList << addTime.count() << " "; //czas dodawania 4000 elementów

        //if (i==0) cout << "List####################################################################\n" << *ds << endl;

        start = chrono::system_clock::now();
        for(int j = 0; j < search; j++){
            //cout << "Szukam " << a[j] << " ";
            ds->findElement(a[j]);
        }
        //cout << endl << endl;
        end = chrono::system_clock::now();
        addTime = end - start;
        foutList << addTime.count() << " "; //czas szukania 100 elementów

        start = chrono::system_clock::now();
        for(int j = 0; j < del; j++){
            //cout << "Usuwam " << a[j+100] << " ";
            ds->deleteElement(a[j+100]);
        }
        end = chrono::system_clock::now();
        //cout << endl << endl;
        addTime = end - start;
        foutList << addTime.count() << " "; //czas usuwania 100 elementów

        foutList << endl;
        delete ds;

        cout << "Kopiec\n";

        //##########################################KOPIEC####################################################################
        ds = new BinaryHeap;
        start = chrono::system_clock::now();
        ds->loadFile("numbers.txt");
        end = chrono::system_clock::now();
        addTime = end - start;
        foutBH << addTime.count() << " ";

        //if (i==0) cout << "BH####################################################################\n" << *ds << endl;

        start = chrono::system_clock::now();
        for(int j = 0; j < search; j++){
            ds->findElement(a[j]);
        }
        end = chrono::system_clock::now();
        addTime = end - start;
        foutBH << addTime.count() << " "; //czas szukania 100 elementów

        start = chrono::system_clock::now();
        for(int j = 0; j < del; j++){
            ds->deleteElement(a[j+100]);
        }
        end = chrono::system_clock::now();
        addTime = end - start;
        foutBH << addTime.count() << " "; //czas usuwania 100 elementów

        foutBH << endl;
        delete ds;

        cout << "Drzewo\n";

        //##########################################DRZEWO_RBT####################################################################
        ds = new RedBlackTree;
        start = chrono::system_clock::now();
        ds->loadFile("numbers.txt");
        end = chrono::system_clock::now();
        addTime = end - start;
        foutRBT << addTime.count() << " ";

        //if (i==0) cout << "RBT####################################################################\n" << *ds << endl;

        start = chrono::system_clock::now();
        for(int j = 0; j < search; j++){
            ds->findElement(a[j]);
        }
        end = chrono::system_clock::now();
        addTime = end - start;
        foutRBT << addTime.count() << " "; //czas szukania 100 elementów

        start = chrono::system_clock::now();
        for(int j = 0; j < del; j++){
            ds->deleteElement(a[j+100]);
        }
        end = chrono::system_clock::now();
        addTime = end - start;
        foutRBT << addTime.count() << " "; //czas usuwania 100 elementów

        foutRBT << endl;
        delete ds;
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
    srand(time(NULL));
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