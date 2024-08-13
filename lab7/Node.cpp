#include "Node.h"
#include <iostream>

using namespace std;

string Node::getData(){
    return data;
}

void Node::setData(const string &s){
    data = s;
}

int Node::getHeight(){
    return height;
}

void Node::setHeight(int value){
    height = value;
}

Node* Node::getLeft(){
    return this->left;
}

void Node::setLeft(Node* node){
    this->left = node;
}

Node* Node::getRight(){
    return this->right;
}

void Node::setRight(Node* node){
    this->right = node;
}

Node* Node::getParent(){
    return this->parent;
}

void Node::setParent(Node *node){
    this->parent = node;
}