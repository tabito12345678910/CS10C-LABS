#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node{
    public:
        Node(const string &s) : data(s), height(0), left(nullptr), right(nullptr) {}
        string getData();
        void setData(const string &);
        int getHeight();
        void setHeight(int);
        Node *getLeft();
        void setLeft(Node*);
        Node*getRight();
        void setRight(Node*);
        Node *getParent();
        void setParent(Node *);
    private: 
        string data;
        int height;
        Node *left;
        Node *right;
        Node *parent;
};

#endif