#include "Node.h"
#include <iostream>

using namespace std;

Node::Node(){
    count = 1;
    label = "";
    leftNode = nullptr;
    rightNode = nullptr;
}

Node::Node(string s){
    count = 1;
    label = s;
    leftNode = nullptr;
    rightNode = nullptr;
}

Node::~Node(){
    delete leftNode;
    delete rightNode;
}

void Node::setCount(int num){
    count = num;
}

int Node::getCount(){
    return count;
}
void Node::increaseCount(){
    count++;
}

void Node::decreaseCount(){
    count--;
}

string Node::getLabel(){
    return label;
}

void Node::setLabel(string s){
    label = s;
}

Node* Node::getLeftNode(){
    return leftNode;
}

void Node::setLeftNode(Node* n){
    leftNode = n;
}

Node* Node::getRightNode(){
    return rightNode;
}

void Node::setRightNode(Node* n){
    rightNode = n;
}
