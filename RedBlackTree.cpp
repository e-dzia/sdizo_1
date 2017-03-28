//
// Created by Edzia on 2017-03-06.
//

#include <cmath>
#include <fstream>
#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() {
    RBTNode * g = new RBTNode;
    g->up = g;
    g->left = g;
    g->right = g;
    g->color = 'B';
    g->value = -1;
    this->guard = g;
    this->root = this->guard;
    //cout << "Nowe RBT " << this->root << endl;
}

RedBlackTree::~RedBlackTree() {
   // cout << "###############################################################################Usuwam RBT " << this->root << endl;

    deleteTree(this->root);
    delete this->guard;
    //delete this->root;

}

void RedBlackTree::deleteTree(RBTNode *pNode) {
    if (pNode != NULL && pNode != this->guard){
        deleteTree(pNode->right);
        deleteTree(pNode->left);
        //cout << "Usunieto " << pNode->value << endl;
        delete pNode;
    }
    /*if (pNode->right != this->guard && pNode->right != NULL)
        deleteTree(pNode->right);
    if (pNode->left != this->guard && pNode->left != NULL)
        deleteTree(pNode->left);
    if (pNode != this->guard && pNode != NULL)
        delete pNode;*/
}

int RedBlackTree::getSize() const {
    return 0;
}

void RedBlackTree::loadFile(string name) {
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
    }
}

void RedBlackTree::addElement(int value, int notUsed) {
    RBTNode * tmp = this->findEl(value);
    if (tmp != this->guard) return;
    RBTNode* rbt = new RBTNode; //nowy wezel
    rbt->value = value;
    rbt->color = 'R';
    rbt->up = this->guard;
    rbt->left = this->guard;
    rbt->right = this->guard;
    RBTNode* p = this->root; //wezel pomocniczy
    if (p == this->guard){
        this->root = rbt;
        return;
    }
    else while (true){
        if (rbt->value == p->value)
            return;
        else if (rbt->value < p->value){
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
    if (p == p->right) cout << "Blad dodawania###################################################\n";
    //cout << "Korzen po dodaniu: " << this->root->value << endl;

}

void RedBlackTree::deleteElement(int value) {
    RBTNode * p = this->findEl(value); //wezel do usuniecia
    cout << p->value << " ";
    RBTNode * toChange = p; // wezel pomocniczy
    char pColor = p->color;
    RBTNode * b;
    if (p != this->guard){
        //cout << " Mam " ;
        RBTNode * toChange; // wezel pomocniczy
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
                b = tmp->right;

                tmp->up->left = tmp->right; //rodzic tmp
                if (tmp->right != this->guard)
                    tmp->right = tmp->up; //dziecko tmp

                tmp->left = p->left;
                tmp->right = p->right;

                toChange = tmp;
            }

        }
        if (p->up == this->guard)
            this->root = toChange;
        else if (p->up->left == p) //p -y
            p->up->left = toChange;
        else if (p->up->right == p)
            p->up->right = toChange;
        if (toChange != this->guard && toChange != NULL){
            toChange->up = p->up; //Z->up = Y->up
        }

        if (b != NULL && b != this->guard && b->up->right->color == 'R'){
            RBTNode * w;
            while (b != this->root && b->color == 'B') {
                if (b == b->up->left) {
                    w = b->up->right;
                    if (w->color == 'R') {
                        w->color = 'B';
                        b->up->color = 'R';
                        this->rot_L(b->up);
                        w = b->up->right;
                    }
                    if (w->left->color == 'B' && w->right->color == 'B') {
                        w->color = 'R';
                        b = b->up;
                    } else {
                        if (w->right->color == 'B') {
                            w->left->color = 'B';
                            w->color = 'R';
                            this->rot_R(w);
                            w = b->up->right;
                        }
                        w->color = b->up->color;
                        b->up->color = 'B';
                        w->right->color = 'B';
                        this->rot_L(b->up);
                        b = this->root;
                    }
                } else {
                    w = b->up->left;
                    if (w->color == 'R') {
                        w->color = 'B';
                        b->up->color = 'R';
                        this->rot_L(b->up);
                        w = b->up->left;
                    }
                    if (w->right->color == 'B' && w->left->color == 'B') {
                        w->color = 'R';
                        b = b->up;
                    } else {
                        if (w->left->color == 'B') {
                            w->right->color = 'B';
                            w->color = 'R';
                            this->rot_R(w);
                            w = b->up->left;
                        }
                        w->color = b->up->color;
                        b->up->color = 'B';
                        w->left->color = 'B';
                        this->rot_L(b->up);
                        b = this->root;
                    }
                }
            }
            b->color = 'B';
        }

       // cout << "Usunieto " << p->value << endl;

        if (p == this->root){
            toChange->up = this->root->up;
            toChange->right = this->root->right;
            toChange->left = this->root->left;
            this->root = toChange;
        }

        //this->fixRBT_D(p);

        //cout << "Usunieto " << p->value << endl;

        if (p != this->guard)
            delete p;
        //return true;

        //cout << "Korzen po usunieciu: " << this->root->value << endl;
        //cout << "Dzieci: " << this->root->right->value << " " << this->root->left->value << endl;
    }
}

RBTNode * RedBlackTree::nextValue(RBTNode * p){
    if (p->right != this->guard){
        p = p->right;
        while (p->left != this->guard){
            p = p->left;
        }
        return p;
    }
    return this->guard;
}

RBTNode* RedBlackTree::findEl(int value){
    RBTNode * p = this->root;
   // cout << "Szukam";
    while (p != this->guard && p != NULL && p->value != p->right->value){
        if (value == p->value){
            //cout << "Znalazlem";
            return p;
        }
        else if (value > p->value){
            //cout << "prawo";
            p = p->right;
        }
        else {
            //cout << "lewo";
            p = p->left;
        }
    }
    //cout << "Nie";
    return this->guard;
}

int RedBlackTree::findElement(int value) {
    if (findEl(value)== this->guard) return -1;
    else return 1;
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
    if (pNode == this->root){
        this->root = B;
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
    if (pNode == this->root){
        this->root = B;
    }
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
        os << s << sn << v->value/* << "(" << v->color << ")" */<< endl;

        s = sp;
        if(sn == cl) s[s.length() - 2] = ' ';
        printRBT(s + cp, cl, v->left, os);
    }
}

ostream &operator<<(ostream &os, const RedBlackTree &a) {
    a.printRBT("","",a.root, os);
    return os;

}

void RedBlackTree::print(std::ostream &str) const {
    str << *this;
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

int RedBlackTree::getElement(int position) {
    return -1;
}




