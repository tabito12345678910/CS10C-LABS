#ifndef AVLTREE_H
#define AVLTREE_H

#include "Node.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>

using namespace std;

class AVLTree {
    public: 
        /*Constructor*/
        AVLTree() : root(nullptr) {}

        /*Insert an item to the binary search tree and perform rotation if necessary.*/
        void insert(const string &);

        /*Return the balance factor of a given node.*/
        int balanceFactor(Node*);

        /*Traverse and print the tree in inorder notation. 
        Print the string followed by its balance factor in parentheses followed by a , and one space.*/
        void printBalanceFactors();

        /*Generate dotty file and visualize the tree using dotty program. Call this function before and after rotation.*/
        void visualizeTree(const string &);
    private:
        Node *root;

        //Helper functions
        void printBalanceFactors(Node *);
        void visualizeTree(ofstream &, Node *);
        void rebalance(Node *);
        void rotateLeft(Node *);
        void rotateRight(Node *);
        bool setChild(Node *, const string &, Node *);
        bool replaceChild(Node *, Node *, Node *);
        void updateHeight(Node *);
        bool search(Node *, const string &) const;
};

#endif
