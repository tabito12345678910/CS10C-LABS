#include <iostream>
#include "IntList.h"
using namespace std;

IntList::IntList(){
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
}

IntList::~IntList(){
}

bool IntList::empty()const{
    if(dummyHead->next == dummyTail){
        return true;
    }
    else{
        return false;
    }
}

void IntList::push_front(int value){
    IntNode* node = new IntNode(value);
    node->prev = dummyHead;
    node->next = dummyHead->next;
    dummyHead->next->prev = node;
    dummyHead->next = node;
}

void IntList::pop_front(){
    if(!empty()){
        IntNode* node = dummyHead->next;
        dummyHead->next = node->next;
        node->next->prev = dummyHead;
        delete node;
    }
}

void IntList::push_back(int value){
    IntNode* node = new IntNode(value);
    node->next = dummyTail;
    node->prev = dummyTail->prev;
    dummyTail->prev->next = node;
    dummyTail->prev = node;
}

void IntList::pop_back(){
    if(!empty()){
        IntNode* node = dummyTail->prev;
        dummyTail->prev = node->prev;
        node->prev->next = dummyTail;
        delete node;
    }
}

ostream & operator<<(ostream &out, const IntList &rhs){
    IntNode* currentNode = rhs.dummyHead->next;
    while(currentNode!=rhs.dummyTail){
        if(currentNode->next == rhs.dummyTail){
            out<<currentNode->data;
        }
        else{
            out<<currentNode->data<<" ";
        }
        currentNode = currentNode->next;
    }
    return out;
}

void IntList::printReverse() const{
    IntNode* currentNode = dummyTail->prev;
    while(currentNode!=dummyHead){
        if(currentNode->prev == dummyHead){
            cout<<currentNode->data;
        }
        else{
            cout<<currentNode->data<<" ";
        }
        currentNode = currentNode->prev;
    }
}

  7
