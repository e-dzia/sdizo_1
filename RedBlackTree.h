//
// Created by Edzia on 2017-03-06.
//

#include "cmake-build-debug/DataStructure.h"

#ifndef SDIZO_1_REDBLACKTREE_H
#define SDIZO_1_REDBLACKTREE_H

#endif //SDIZO_1_REDBLACKTREE_H

struct RBTNode
{
    RBTNode * up;
    RBTNode * left;
    RBTNode * right;
    char color; //B - czarny, R - czerwony
    int value;
};

class RedBlackTree: public DataStructure{
private:
    RBTNode * guard;             // Węzeł strażnika
    RBTNode * root;        // Korzeń drzewa czerwono-czarnego

public:
    RedBlackTree();
    ~RedBlackTree();

    int getSize() const;

    void loadFile(string name);
    void addElement(int value, int position) ;
    void deleteElement(int value);
    int findElement(int value);

    void menu();

    friend ostream & operator<<(ostream & os , const RedBlackTree & a);

    RBTNode *findEl(int value);

    RBTNode *nextValue(RBTNode *p);

    void printRBT(string sp, string sn, RBTNode *v, ostream &os)const;

    void deleteTree(RBTNode *pNode);

    void fixRBT_A(RBTNode *pNode);

    void rot_R(RBTNode *pNode);

    void rot_L(RBTNode *pNode);

    void fixRBT_D(RBTNode *pNode);

    void print(std::ostream &str) const override;

    int getElement(int position) override;
};