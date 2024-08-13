#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T> // Generic stack class template
class stack {
    public:
        stack(); //Default constructor

        void push(T val); //pushes value to end of stack. 

        void pop(); //removes first value from top of stack.

        void pop_two(); //removes two values from top of stack.

        T top(); //returns first value of stack

        bool empty(); //returns if the stack is empty or not
    private: 

        static const int MAX = 20; // Maximum size of the stack

        int size; //size of stack

        T data [MAX]; // data in stack
};

template <typename T> stack<T>::stack() {
    size = 0; 
}

template <typename T> void stack<T>::push(T val){
    if(size == MAX){ //check if full
        throw overflow_error ("Overflow.");
    } else {
        data[size] = val;
        size++;
    }
}

template <typename T> void stack<T>::pop(){
    if(empty()){
        throw out_of_range ("No data to pop.");
    } else {
        size--; 
    }
}

template <typename T> void stack<T>::pop_two(){
    if(empty()){
\        throw out_of_range ("Cannot pop from empty stack.");
    } else if (size == 1){
\        throw out_of_range ("Stack too small for pop_two");
    } else {
        size = size-2;
    }
}

template <typename T> T stack<T>::top() {
    if(empty()){
\        throw underflow_error ("No top in empty stack.");
    }
    return data[size-1];
}

template <typename T> bool stack<T>::empty() {
    return (size == 0);
}

#endif 
