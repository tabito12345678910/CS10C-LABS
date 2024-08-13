#include "Tree.h"


Tree::Tree() {
    root = nullptr;
}

Tree::~Tree() {
    delete root;
}

void Tree::insert(const string &str) {
    if (!root) {
        // If the root node is empty, create a new node with the given string as the small string and return.
        root = new Node();
        root->small = str;
        return;
    }

    Node* targetNode = root;
    while (targetNode->left) {
        // Traverse down the tree to find the appropriate position for the new string.
        if (targetNode->isFull()) {
            // If the current node has two strings, determine which branch to follow based on the value of the given string.
            if (targetNode->small > str)
                targetNode = targetNode->left;
            else if (targetNode->large < str)
                targetNode = targetNode->right;
            else
                targetNode = targetNode->middle;
        } else {
            // If the current node has only one string, follow the appropriate branch based on the value of the given string.
            if (targetNode->small > str)
                targetNode = targetNode->left;
            else
                targetNode = targetNode->middle;
        }
    }

    if (targetNode->isFull()) {
        // If the target node has two strings, split it into three nodes and insert the new string between the small and large strings.
        string small, middle, large;
        if (targetNode->small > str) {
            small = str;
            middle = targetNode->small;
            large = targetNode->large;
        } else {
            small = targetNode->small;
            if (targetNode->large < str) {
                middle = targetNode->large;
                large = str;
            } else {
                middle = str;
                large = targetNode->large;
            }
        }
        Node* smallNode = new Node();
        smallNode->small = small;
        Node* largeNode = new Node();
        largeNode->small = large;
        targetNode->small = middle;
        targetNode->large = "";
        targetNode->left = smallNode;
        targetNode->middle = largeNode;
        targetNode->right = nullptr;
        smallNode->parent = targetNode;
        largeNode->parent = targetNode;
        shiftUp(targetNode);
    } else {
        // If the target node has only one string, insert the new string into the node.
        if (targetNode->small > str)
            targetNode->large = targetNode->small, targetNode->small = str;
        else
            targetNode->large = str;
    }
}

void Tree::shiftUp(Node* node) {
    if (node->parent) {
        Node* parent = node->parent;
        if (parent->isFull()) {
            if (parent->small > node->small) {
                Node* newLarge = new Node();
                newLarge->left = parent->middle;
                newLarge->left->parent = newLarge;
                newLarge->middle = parent->right;
                newLarge->middle->parent = newLarge;
                newLarge->small = parent->large;
                parent->left = node;
                parent->middle = newLarge;
                parent->right = nullptr;
                parent->large = "";
                newLarge->parent = parent;
            } else if (parent->large < node->small) {
                Node* newSmall = new Node();
                newSmall->left = parent->left;
                newSmall->left->parent = newSmall;
                newSmall->middle = parent->middle;
                newSmall->middle->parent = newSmall;
                newSmall->small = parent->small;
                parent->left = newSmall;
                parent->middle = node;
                parent->right = nullptr;
                parent->small = parent->large;
                parent->large = "";
                newSmall->parent = parent;
            } else {
                Node* newSmall = new Node();
                newSmall->small = parent->small;
                newSmall->left = parent->left;
                newSmall->left->parent = newSmall;
                newSmall->middle = node->left;
                newSmall->middle->parent = newSmall;
                Node* newLarge = new Node();
                newLarge->small = parent->large;
                newLarge->left = node->middle;
                newLarge->left->parent = newLarge;
                newLarge->middle = parent->right;
                newLarge->middle->parent = newLarge;
                parent->left = newSmall;
                parent->middle = newLarge;
                parent->right = nullptr;
                parent->small = node->small;
                parent->large = "";
                newSmall->parent = parent;
                newLarge->parent = parent;
                delete node;
            }
            shiftUp(parent);
        } else {
            if (parent->small > node->small) {
                parent->large = parent->small;
                parent->small = node->small;
                parent->left = node->left;
                parent->right = parent->middle;
                parent->middle = node->middle;
            } else {
                parent->large = node->small;
                parent->middle = node->left;
                node->left->parent = parent;
                parent->right = node->middle;
                node->middle->parent = parent;
            }
                node->left->parent = parent;
                node->middle->parent = parent;
                delete node;
        }
    }
}

void Tree::remove(const string &str) {
    Node* searchNode = root;
    while (searchNode) {
        if (searchNode->small == str || (searchNode->isFull() && searchNode->large == str)) {
            break;
        } else {
            if (searchNode->small > str) {
                searchNode = searchNode->left;
            } else {
                if (searchNode->isFull() && searchNode->large < str) {
                    searchNode = searchNode->right;
                } else {
                    searchNode = searchNode->middle;
                }
            }
        }
    }

    if (searchNode) {
        if (searchNode->isFull()) {
            if (str == searchNode->small) {
                searchNode->small = searchNode->large;
                searchNode->large = "";
            } else {
                searchNode->large = "";
            }
        } else {
            Node* parent = searchNode->parent;
            if (parent) {
                if (str < parent->small) {
                    parent->left = nullptr;
                    parent->large = parent->middle->small;
                    parent->middle = nullptr;
                } else {
                    parent->middle = nullptr;
                    parent->large = parent->small;
                    parent->small = parent->left->small;
                    parent->left = nullptr;
                }
            } else {
                Node* temp = new Node();
                if (root->left) {
                    temp->small = root->left->small;
                    temp->large = root->middle->small;
                    root = temp;
                } else {
                    root = nullptr;
                }
            }
        }
    }
}

bool Tree::search (const string &key) const {
    return search(root, key);
}

bool Tree::search(Node* node, const string& key) const {
    if (root == nullptr) {
        // Key not found
        return false;
    }

    if (root->small == key || root->large == key) {
        // Key found
        return true;
    } else if (root->left == nullptr) {
        // Leaf node without key
        return false;
    } else if (key < root->small) {
        // Recurse on left child
        return search(root->left, key);
    } else if (root->large == "") {
        // Recurse on middle child
        return search(root->middle, key);
    } else if (key < root->large) {
        // Recurse on middle child
        return search(root->middle, key);
    } else {
        // Recurse on right child
        return search(root->right, key);
    }
}

void Tree::preOrder() const {
    preOrderHelper(root);
    cout << endl;
}

void Tree::inOrder() const {
    inOrderHelper(root);
    cout << endl;    
}

void Tree::postOrder() const {
    postOrderHelper(root);
    cout << endl;    
}

void Tree::preOrderHelper(Node* currNode) const {
    if (currNode) {
        if (currNode->isFull()) {
            cout << currNode->small << ", ";
            preOrderHelper(currNode->left);
            cout << currNode->large << ", ";
            preOrderHelper(currNode->middle);
            preOrderHelper(currNode->right);
        } else {
            cout << currNode->small << ", ";
            preOrderHelper(currNode->left);
            preOrderHelper(currNode->middle);
        }
    }
}

void Tree::inOrderHelper(Node* currNode) const {
    if (currNode) {
        inOrderHelper(currNode->left);
        cout << currNode->small << ", ";
        inOrderHelper(currNode->middle);
        if (currNode->isFull()) {
            cout << currNode->large << ", ";
            inOrderHelper(currNode->right);
        }
    }
}  

void Tree::postOrderHelper(Node* currNode) const {
    if (currNode) {
        if (currNode->isFull()) {
            postOrderHelper(currNode->left);
            postOrderHelper(currNode->middle);
            cout << currNode->small << ", ";
            postOrderHelper(currNode->right);
            cout << currNode->large << ", ";
        } else {
            postOrderHelper(currNode->left);
            postOrderHelper(currNode->middle);
            cout << currNode->small << ", ";
        }
    }
}  
