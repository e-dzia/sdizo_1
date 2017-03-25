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
    rbt->left = this->guard;
    rbt->right = this->guard;
    RBTNode* p = this->root; //wezel pomocniczy
    if (p == this->guard){
        this->root = rbt;
        return true;
    }
    else while (true){
        if (rbt->value < p->value){
            if (p->left == this->guard){
                p->left = rbt;
                rbt->up = p;
                break;
            }
            else p = p->left;
        }
        else {
            if (p->right == this->guard) {
                p->right = rbt;
                rbt->up = p;
                break;
            }
            else p = p->right;
        }
    }
    this->fixRBT_A(rbt);

    return true;
}

bool RedBlackTree::deleteElement(int value) {
    RBTNode * p = this->findEl(value);
    RBTNode * toChange;
    if (p != this->guard){
        if (p->left == this->guard && p->right == this->guard){
            toChange = this->guard;
        }
        else {
            if (p->left == this->guard) {
                toChange = p-> right;
            }
            else if (p->right == this->guard){
                toChange = p->left;
            }
            else if (p->right != this->guard && p->left != this->guard){
                RBTNode * tmp = p;
                tmp = this->nextValue(tmp);

                if (tmp->up->left == tmp)//podstawienie odpowiednich wartosci w wezle rodzica tmp
                    tmp->up->left = tmp->right;
                else tmp->up->right = tmp->right;
                tmp->left = p->left;
                tmp->right = p->right;

                toChange = tmp;
            }

        }
        if (p->up->left == p) //p -y
            p->up->left = toChange;
        else p->up->right = toChange;
        if (toChange != this->guard){
            toChange->up = p->up; //Z->up = Y->up
        }
        this->fixRBT_D(p);
        delete p;
        return true;
        }

    return false;
}

RBTNode * RedBlackTree::nextValue(RBTNode * p){
    p = p->right;
    while (p->left != this->guard){
        p = p->left;
    }
    return p;
}

RBTNode* RedBlackTree::findEl(int value){
    RBTNode * p = this->root;
    while (p != this->guard){
        if (value == p->value){
            return p;
        }
        else if (value > p->value){
            p = p->right;
        }
        else p = p->left;
    }
    return this->guard;
}

int RedBlackTree::findElement(int value) {
    if (findEl(value)== this->guard /*|| findEl(value) == guard*/) return -1;
    else return 1;
}

RedBlackTree::RedBlackTree() {
    RBTNode * g = new RBTNode;
    g->up = g;
    g->left = g;
    g->right = g;
    g->color = 'B';
    this->guard = g;
    this->root = this->guard;
}

RedBlackTree::~RedBlackTree() {
    deleteTree(this->root);
    this->root = NULL;
    delete this->guard;

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

ostream &operator<<(ostream &os, const RedBlackTree &a) {
    a.printRBT("","",a.root, os);
    return os;

}

void RedBlackTree::printRBT(string sp, string sn, RBTNode *v, ostream &os)const {
    string s;
    string cr = "  ", cl= "  ", cp = "  ";
    cr[0] = 218; cr[1] = 196;
    cl[0] = 192; cl[1] = 196;
    cp[0] = 179;

    if(v != this->guard)
    {
        s = sp;
        if(sn == cr) s[s.length() - 2] = ' ';
        printRBT(s + cp, cr, v->right, os);

        s = s.substr(0,sp.length()-2);
        os << s << sn << v->value << "(" << v->color << ")" << endl;

        s = sp;
        if(sn == cl) s[s.length() - 2] = ' ';
        printRBT(s + cp, cl, v->left, os);
    }
}

bool RedBlackTree::fixRBT() {
    //TODO: Napraw RBT!
    return false;
}

bool RedBlackTree::deleteTree(RBTNode *pNode) {
    if (pNode->right != this->guard)
        deleteTree(pNode->right);
    if (pNode->left != this->guard)
        deleteTree(pNode->left);
    delete pNode;
    return true;
}

void RedBlackTree::fixRBT_A(RBTNode * pNode) {
    RBTNode * p; //wezel pomocniczy
    pNode->color = 'R';         // Węzeł kolorujemy na czerwono
    while((pNode != this->root) && (pNode->up->color == 'R')) {
        if(pNode->up == pNode->up->up->left) {
            p = pNode->up->up->right; // Y -> wujek pNode
            if(p->color == 'R'){  // Przypadek 1
                pNode->up->color = 'B';
                p->color = 'B';
                pNode->up->up->color = 'R';
                pNode = pNode->up->up;
                continue;
            }
            if(pNode == pNode->up->right){ // Przypadek 2
                pNode = pNode->up;
                rot_L(pNode);
            }

            pNode->up->color = 'B'; // Przypadek 3
            pNode->up->up->color = 'R';
            rot_R(pNode->up->up);
            break;
        }
        else {                  // Przypadki lustrzane
            p = pNode->up->up->left;
            if(p->color == 'R'){ // Przypadek 1
                pNode->up->color = 'B';
                p->color = 'B';
                pNode->up->up->color = 'R';
                pNode = pNode->up->up;
                continue;
            }

            if(pNode == pNode->up->left){ // Przypadek 2
                pNode = pNode->up;
                rot_R(pNode);
            }

            pNode->up->color = 'B'; // Przypadek 3
            pNode->up->up->color = 'R';
            rot_L(pNode->up->up);
            break;
        }
    }
    root->color = 'B';


}

void RedBlackTree::fixRBT_D(RBTNode *pNode) {
    RBTNode * toChange, *p;
    if(pNode->left != this->guard) toChange = pNode->left;
    else              toChange = pNode->right;
    if(pNode->color == 'B')   // Naprawa struktury drzewa czerwono-czarnego
        while((toChange != root) && (toChange->color == 'B')) {
            if(toChange == toChange->up->left) {
            p = toChange->up->right;

            if(p->color == 'R') {
                p->color = 'B';
                toChange->up->color = 'R';
                rot_L(toChange->up);
                p = toChange->up->right;
            }

            if((p->left->color == 'B') && (p->right->color == 'B')){// Przypadek 2
                p->color = 'R';
                toChange = toChange->up;
                continue;
            }

            if(p->right->color == 'B'){// Przypadek 3
                p->left->color = 'B';
                p->color = 'R';
                rot_R(p);
                p = toChange->up->right;
            }

            p->color = toChange->up->color; // Przypadek 4
            toChange->up->color = 'B';
            p->right->color = 'B';
            rot_L(toChange->up);
            toChange = root;         // To spowoduje zakończenie pętli
        }
        else {// Przypadki lustrzane
            p = toChange->up->left;

            if(p->color == 'R') { // Przypadek 1
                p->color = 'B';
                toChange->up->color = 'R';
                rot_R(toChange->up);
                p = toChange->up->left;
            }

            if((p->left->color == 'B') && (p->right->color == 'B')) { // Przypadek 2
                p->color = 'R';
                toChange = toChange->up;
                continue;
            }

            if(p->left->color == 'B'){ // Przypadek 3
                p->right->color = 'B';
                p->color = 'R';
                rot_L(p);
                p = toChange->up->left;
            }

            p->color = toChange->up->color;  // Przypadek 4
            toChange->up->color = 'B';
            p->left->color = 'B';
            rot_R(toChange->up);
            toChange = root;         // To spowoduje zakończenie pętli
        }
    }

    toChange->color = 'B';
}

void RedBlackTree::rot_R(RBTNode *pNode) {
    RBTNode * B, * p;

    B = pNode->left;
    if(B != this->guard)
    {
        p = pNode->up;
        pNode->left = B->right;
        if(pNode->left != this->guard) pNode->left->up = pNode;

        B->right = pNode;
        B->up = p;
        pNode->up = B;

        if(p != this->guard)
        {
            if(p->left == pNode) p->left = B; else p->right = B;
        }
        else root = B;
    }

}

void RedBlackTree::rot_L(RBTNode *pNode) {
    RBTNode * B, * p;

    B = pNode->right;
    if(B != this->guard)
    {
        p = pNode->up;
        pNode->right = B->left;
        if(pNode->right != this->guard) pNode->right->up = pNode;

        B->left = pNode;
        B->up = p;
        pNode->up = B;

        if(p != this->guard)
        {
            if(p->left == pNode) p->left = B; else p->right = B;
        }
        else root = B;
    }
}

void RedBlackTree::print(std::ostream &str) const {
    str << *this;
}


