#include "BSTree.h"
#include "Node.h"

#include <iostream>

using namespace std;

BSTree::BSTree(){
    root = nullptr;
}

BSTree::~BSTree(){
    delete root;
}

void BSTree::insert(const string &newString){
    if(search(newString)){
        Node *curr = getNode(root, newString);
        curr->increaseCount();
    } else {
        Node *temp = new Node(newString); //temp node to be inserted into list
        if(root == nullptr){ //case for empty tree
            root = temp;
        } 
        else {
            Node *curr = root;
            while(curr != nullptr){
                if(temp->getLabel() < curr->getLabel()){ //if inserted node is less than curr node
                    if(curr->getLeftNode() == nullptr){ //if at leaf position, insert node
                        curr->setLeftNode(temp);
                        curr = nullptr;
                    } else { //otherwise continue iterating down left 
                        curr = curr->getLeftNode();
                    }
                } else if(temp->getLabel() > curr->getLabel()){ //if inserted node is greater than curr node
                    if(curr->getRightNode() == nullptr){ //if at leaf position, insert node
                        curr->setRightNode(temp);
                        curr = nullptr;
                    } else { //otherwise continue iterating down right
                        curr = curr->getRightNode();
                    }
                }
            }
        }
    }
}

void BSTree::remove(const string &key){
    if(!search(key)){
        return;
    } else if(root->getLeftNode() == nullptr && root->getRightNode() == nullptr){ //only root 
        delete root;
        root = nullptr;
        return;
    } else {
        remove(root,key);
    }
}

Node* BSTree::remove(Node *n, const string &key){
    if(n == nullptr){
        return n;
    } else if(key < n->getLabel()){
        n->setLeftNode(remove(n->getLeftNode(),key));
    } else if(key > n->getLabel()){
        n->setRightNode(remove(n->getRightNode(),key));
    } else { //found node
        if(n->getCount() > 1){
            n->decreaseCount();
            return n;
        }
        if(n->getRightNode() == nullptr && n->getLeftNode() == nullptr){ //case 1: no child
            delete n;
            n = nullptr;
        } else if(n->getLeftNode() == nullptr){ //case 2: only right child
            Node *min = findMin(n->getRightNode()); //finds minimum in right tree
            n->setLabel(min->getLabel()); //copy over values from minimum
            n->setCount(min->getCount());
            min->setCount(0);
            n->setRightNode(remove(n->getRightNode(),min->getLabel()));
            return n;
        } else if(n->getRightNode() == nullptr){ //case 3: only left child
            Node *max = findMax(n->getLeftNode()); //finds maximum in left tree
			n->setLabel(max->getLabel()); //copy over values from maximum
			n->setCount(max->getCount());
			max->setCount(0);
			n->setLeftNode(remove(n->getLeftNode(),max->getLabel()));
			return n;
        } else { //case 4: 2 children
            Node *max = findMax(n->getLeftNode()); //finds max from left tree
            n->setLabel(max->getLabel()); //copy over values
            n->setCount(max->getCount());
            n->setLeftNode(remove(n->getLeftNode(), max->getLabel()));
            return n;
        }
    }
    return n;

}

Node* BSTree::findMin(Node *n){
    Node *curr = n;
    while(curr != nullptr && curr->getLeftNode() != nullptr){ //finds minimum node in right subtree
        curr = curr->getLeftNode();
    }
    return curr;
}

Node* BSTree::findMax(Node *n){
    Node *curr = n;
    while(curr != nullptr && curr->getRightNode() != nullptr){ //finds minimum node in right subtree
        curr = curr->getRightNode();
    }
    return curr;
}

bool BSTree::search(const string &key) const {
    return search(root,key);
}

bool BSTree::search(Node *n, const string &key) const{
    if(n == nullptr){
        return false;
    } else if(n->getLabel() == key){
        return true;
    } else {
        if(key < n->getLabel()){
            return search(n->getLeftNode(),key);
        } else if (key > n->getLabel()){
            return search(n->getRightNode(),key);
        }
    }
    return false;
}

string BSTree::largest() const{
    if(root == nullptr){ //if tree is empty, return NULL
        return "";
    } else {
        Node *curr = root;
        while(curr->getRightNode() != nullptr){ //iterate through right side of tree
            curr = curr->getRightNode();
        }
        return curr->getLabel(); 
    }
}

string BSTree::smallest() const{
    if(root == nullptr){ //if tree is empty, return NULL
        return "";
    } else {
        Node *curr = root;
        while(curr->getLeftNode() != nullptr){ //iterate through side left of tree
            curr = curr->getLeftNode();
        }
        return curr->getLabel();
    }
}

int BSTree::height(const string &key) const{
    if(search(key)){
        Node *n = getNode(root, key); //finds the node of the key
        return height(n);
    } else {return -1;} //if node doesn't exist, return -1
}

int BSTree::height(Node * n) const{
    if(n == nullptr){
        return -1;
    } else {
        int leftHeight = height(n->getLeftNode());
        int rightHeight = height(n->getRightNode());
        return max(leftHeight, rightHeight) + 1; //compares left and right height and returns the greatest
    }
}

Node *BSTree::getNode(Node *n, const string &key) const{ //helper function to find the node of the desired key value
    if(n != nullptr){
        if(n->getLabel() == key){
            return n;
        } else if(key < n->getLabel()){
            return getNode(n->getLeftNode(),key);
        } else{
            return getNode(n->getRightNode(),key);
        }
    }
    return NULL;
}

void BSTree::preOrder() const{
    preOrder(root);
}

void BSTree::preOrder(Node* n) const{
    if(n == nullptr){
        return;
    } else {
        printNode(n);
        preOrder(n->getLeftNode());
        preOrder(n->getRightNode());
    }
}

void BSTree::postOrder() const{
    postOrder(root);
}

void BSTree::postOrder(Node *n) const{
    if(n == nullptr){
        return;
    } else {
        postOrder(n->getLeftNode());
        postOrder(n->getRightNode());
        printNode(n);
    }
}

void BSTree::inOrder() const{
    inOrder(root);
}

void BSTree::inOrder(Node* n) const{
    if(n == nullptr){
        return;
    } else {
        inOrder(n->getLeftNode());
        printNode(n);
        inOrder(n->getRightNode());
    }
}

void BSTree::printNode(Node *n) const{
    cout << n->getLabel() << "(" << n->getCount() << "), ";
}