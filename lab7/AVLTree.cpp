#include "AVLTree.h"

using namespace std;


void AVLTree::insert(const string &newString){
    if(search(root, newString)){
        return;
    }
    Node *temp = new Node(newString); //temp node to be inserted into list
    if(root == nullptr){ //special case for empty tree
        root = temp;
        temp->setParent(nullptr);
    } else {
        Node *curr = root;
        while(curr != nullptr){
            if(temp->getData() < curr->getData()){ //if inserted node is less than curr node
                if(curr->getLeft() == nullptr){ //if at leaf position, insert node
                    curr->setLeft(temp);
                    temp->setParent(curr);
                    curr = nullptr;
                } else { //otherwise continue iterating down left 
                    curr = curr->getLeft();
                }
            } else if(temp->getData() > curr->getData()){ //if inserted node is greater than curr node
                if(curr->getRight() == nullptr){ //if at leaf position, insert node
                    curr->setRight(temp);
                    temp->setParent(curr);
                    curr = nullptr;
                } else { //otherwise continue iterating down right
                    curr = curr->getRight();
                }
            }
        }
    }
    temp = temp->getParent();
    while(temp != nullptr){
        rebalance(temp);
        temp = temp->getParent();
    }
}

int AVLTree::balanceFactor(Node* node){
    int leftHeight = -1;
    if (node->getLeft() != nullptr) {
        leftHeight = node->getLeft()->getHeight();
    }
    int rightHeight = -1;
    if (node->getRight() != nullptr) {
        rightHeight = node->getRight()->getHeight();
    }
    return leftHeight-rightHeight;
}

void AVLTree::printBalanceFactors(){
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::printBalanceFactors(Node *node){
    if (node == nullptr) {
        return;
    } else {
        printBalanceFactors(node->getLeft());
        cout << node->getData() << "(" << balanceFactor(node) << "), ";
        printBalanceFactors(node->getRight());
    }
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
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

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->getLeft()){
            visualizeTree(outFS,n->getLeft());
            outFS<<n->getData() <<" -> " <<n->getLeft()->getData()<<";"<<endl;    
        }

        if(n->getRight()){
            visualizeTree(outFS,n->getRight());
            outFS<<n->getData() <<" -> " <<n->getRight()->getData()<<";"<<endl;    
        }
    }
}

void AVLTree::rebalance(Node *node) {
    updateHeight(node);
    if (balanceFactor(node) == -2) {
        if (balanceFactor(node->getRight()) == 1) {
            // Double rotation case.
            rotateRight(node->getRight());
        }
        rotateLeft(node);
    } else if (balanceFactor(node) == 2) {
        if (balanceFactor(node->getLeft()) == -1) {
            // Double rotation case.
            rotateLeft(node->getLeft());
        }
        rotateRight(node);
    }        
}

void AVLTree::rotateLeft(Node *node){
    Node *rightLeftChild = node->getRight()->getLeft();
    if (node->getParent() != nullptr) {
        replaceChild(node->getParent(), node, node->getRight());
    } else { // node is root
        root = node->getRight();
        root->setParent(nullptr);
    }
    setChild(node->getRight(), "left", node);
    setChild(node, "right", rightLeftChild);
}

void AVLTree::rotateRight(Node *node) {
    Node *leftRightChild = node->getLeft()->getRight();
    if (node->getParent() != nullptr) {
        replaceChild(node->getParent(), node, node->getLeft());
    } else { // node is root
        root = node->getLeft();
        root->setParent(nullptr);
    }
    setChild(node->getLeft(), "right", node);
    setChild(node, "left", leftRightChild);
}

bool AVLTree::setChild(Node *parent, const string &whichChild, Node *child){
    if (whichChild != "left" && whichChild != "right"){
        return false;
    }
    if (whichChild == "left") {
        parent->setLeft(child);
    } else {
        parent->setRight(child);
    }
    if (child != nullptr) {
        child->setParent(parent);
    }
    updateHeight(parent);
    return true;
}


bool AVLTree::replaceChild(Node *parent, Node *currentChild, Node *newChild){
    if (parent->getLeft() == currentChild) {
        return setChild(parent, "left", newChild);
    } else if (parent->getRight() == currentChild) {
        return setChild(parent, "right", newChild);
    }
    return false;
}

void AVLTree::updateHeight(Node *node){ 
    int leftHeight = -1;
    if (node->getLeft() != nullptr) {
        leftHeight = node->getLeft()->getHeight();
    }
    int rightHeight = -1;
    if (node->getRight() != nullptr) {
        rightHeight = node->getRight()->getHeight();
    }
    node->setHeight(max(leftHeight, rightHeight) + 1);
}

bool AVLTree::search(Node *n, const string &key) const{
    if(n == nullptr){
        return false;
    } else if(n->getData() == key){
        return true;
    } else {
        if(key < n->getData()){
            return search(n->getLeft(),key);
        } else if (key > n->getData()){
            return search(n->getRight(),key);
        }
    }
    return false;
}
