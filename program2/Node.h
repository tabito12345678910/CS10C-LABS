#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node{
    private:
        int count;
        string label;
        Node *leftNode;
        Node *rightNode;
    public:
        Node(); //constructor
        ~Node(); //destructor
        Node(string s); //label
        void setCount(int);//value
        int getCount();//get value       
        void increaseCount();
        void decreaseCount();
        string getLabel();
        void setLabel(string);
        Node* getLeftNode();
        void setLeftNode(Node*);
        Node* getRightNode();
        void setRightNode(Node*);
};

#endif
