#ifndef __TREE_H
#define __TREE_H

#include "Node.h"
#include <iostream>


class Tree {
private:
  Node *root;

public:
  Tree();
  ~Tree();
  void insert(const string &);
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
  void remove(const string &);
  bool search(const string &) const;

private:
  // Add additional functions/variables here
  void shiftUp(Node*);
  void preOrderHelper(Node*) const;
  void inOrderHelper(Node*) const;
  void postOrderHelper(Node*) const;
  bool search(Node*, const string&) const;
    
};

#endif
