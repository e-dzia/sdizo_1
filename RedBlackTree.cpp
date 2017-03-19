//
// Created by Edzia on 2017-03-06.
//

#include <cmath>
#include <fstream>
#include "RedBlackTree.h"

int RedBlackTree::getSize() const {
    return 0;
}

bool RedBlackTree::loadFile(string name) {
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

bool RedBlackTree::addElement(int value, int notUsed) {
    RBTNode* rbt = new RBTNode; //nowy wezel
    rbt->value = value;
    rbt->color = 'R';
    rbt->up = this->guard;
    RBTNode* p = this->root; //wezel pomocniczy
    if (p == NULL){
        this->root = rbt;
        return true;
    }
    while (true){
        if (rbt->value < p->value){
            if (p->left == NULL){
                p->left = rbt;
                rbt->up = p;
                break;
            }
            else p = p->left;
        }
        else {
            if (p->right == NULL) {
                p->right = rbt;
                rbt->up = p;
                break;
            }
            else p = p->right;
        }
    }
    this->fixRBT();
    return true;
}

bool RedBlackTree::deleteElement(int value) {
    RBTNode * p = this->findEl(value);
    RBTNode * toChange;
    if (p != NULL){
        if (p->left == NULL && p->right == NULL){
            toChange = guard;
        }
        else {
            if (p->left == NULL) {
                toChange = p-> right;
            }
            else if (p->right == NULL){
                toChange = p->left;
            }
            else if (p->right != NULL && p->left != NULL){
                RBTNode * tmp = p;
                tmp = this->nextValue(tmp);

                if (tmp->up->left == tmp)//podstawienie odpowiednich wartosci w wezle rodzica tmp
                    tmp->up->left = tmp->right;
                else tmp->up->right = tmp->right;

                toChange = tmp;

            }

        }

        if (p->up->left == p)
            p->up->left = toChange;
        else p->up->right = toChange;
        if (toChange != guard){
            toChange->up = p->up;
        }
        delete p;
        return true;
        }

    this->fixRBT();
    return false;
}

RBTNode * RedBlackTree::nextValue(RBTNode * p){
    p = p->right;
    while (p->left != NULL){
        p = p->left;
    }
    return p;
}

RBTNode* RedBlackTree::findEl(int value){
    RBTNode * p = this->root;
    while (true){
        if (value == p->value){
            return p;
        }
        else if (value > this->root->value){
            p = p->right;
        }
        else p = p->left;
    }
}

int RedBlackTree::findElement(int value) {
    if (findEl(value)== NULL || findEl(value) == guard) return -1;
    else return 1;
}

RedBlackTree::RedBlackTree() {
    RBTNode * g = new RBTNode;
    g->up=NULL;
    g->left=NULL;
    g->right=NULL;
    g->color='B';
    g->value = 0;
    this->guard = g;
    this->root = NULL;
}

RedBlackTree::~RedBlackTree() {
    //TODO: przejdz po wszystkich wezłach i je pousuwaj

}

void RedBlackTree::menu() {
    cout << "MENU - drzewo czerwono-czarne\n"
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
            cout << this << endl;
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

ostream &operator<<(ostream &os, const RedBlackTree &a) {
//TODO: wyswietlanie drzewa RBT lepiej'
    a.printRBT("","",a.root, os);
    return os;

}

void RedBlackTree::printRBT(string sp, string sn, RBTNode *v, ostream &os)const {
    string s;
    string cr = "  ", cl= "  ", cp = "  ";
    cr[0] = 218; cr[1] = 196;
    cl[0] = 192; cl[1] = 196;
    cp[0] = 179;

    if(v)
    {
        s = sp;
        if(sn == cr) s[s.length() - 2] = ' ';
        printRBT(s + cp, cr, v->right, os);

        s = s.substr(0,sp.length()-2);
        os << s << sn << v->value << endl;

        s = sp;
        if(sn == cl) s[s.length() - 2] = ' ';
        printRBT(s + cp, cl, v->left, os);
    }
}

bool RedBlackTree::fixRBT() {

    return false;
}
