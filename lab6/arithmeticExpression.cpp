#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "arithmeticExpression.h"
using namespace std;


arithmeticExpression::arithmeticExpression(const string & expression){
    infixExpression = expression;
    root = nullptr;
}

    /* Converts the infixExpression to its equivalent postfix string
       and then generates the tree and assigns the root node to the 
       root data field. The key for the first node is 'a', 'b' for the second node and so on. */
void arithmeticExpression::buildTree(){
    string postfixString = infix_to_postfix();
    stack<TreeNode*> temp;
    unsigned int i = 0;
    char c = 'a';
    while (i < postfixString.size()) {
        char element = postfixString[i];
        TreeNode* node = new TreeNode(element, c);
        if (priority(element) != 0) { //when priority != 0, the character is a symbol of some sort
            node->right = temp.top();
            temp.pop();
            node->left = temp.top();
            temp.pop();
            temp.push(node);
            root = node;
        }
        else if (priority(element) == 0) { //when priority is 0, element is a letter
            temp.push(node);
        }
        i++;
        c++;
    }
}



    /* Calls the recursive infix function. */
void arithmeticExpression::infix(){
    return infix(root);
}

void arithmeticExpression::infix(TreeNode *curr){
    if (curr == nullptr) { //ends recursion
        return;
    } 
    else {
        if (curr->left != nullptr) {
            cout << "(";
        }
        infix(curr->left);
        cout << curr->data; //cout in between iterations of both left and right
        infix(curr->right);
        if (curr->right != nullptr) {
            cout << ")";
        }
    }
}

    /* Calls the recursive prefix function. */
void arithmeticExpression::prefix(){
    return prefix(root);
}

void arithmeticExpression::prefix(TreeNode *curr){
    if (curr == nullptr) { 
        return;
    } 
    else {
        cout << curr->data; //cout before iterations
        prefix(curr->left);
        prefix(curr->right);
    }
}

    /* Calls the recursive postfix function. */
void arithmeticExpression::postfix(){
    return postfix(root);
}

void arithmeticExpression::postfix(TreeNode *curr){
    if (curr == nullptr) {
        return;
    } else {
        postfix(curr->left);
        postfix(curr->right);
        cout << curr->data; //cout after iterations
    }
}



int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string& outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void arithmeticExpression::visualizeTree(ofstream &outFS, TreeNode *curr){
    if(curr){
        outFS<<curr->key << " [ label = \""<<curr->data<<"\"];"<<endl;
        if(curr->left){
            visualizeTree(outFS,curr->left);
            outFS<<curr->key <<" -> " <<curr->left->key<<";"<<endl;    
        }
        
        if(curr->right){
            visualizeTree(outFS,curr->right);
            outFS<<curr->key <<" -> " <<curr->right->key<<";"<<endl;    
        }
    }
}

