#include <iostream>
#include <limits>
#include "BSTree.h"
#include "Node.h"


using namespace std;

void printOrders(BSTree *tree) {
  cout << "Preorder = ";
  tree->preOrder( );
  cout << endl;
  cout << "Inorder = ";
  tree->inOrder( );
  cout << endl;
  cout << "Postorder = ";
  tree->postOrder( );
  cout << endl;
}

int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout 
    << "1. Insert" << endl
    << "2. Remove" << endl
    << "3. Print" << endl
    << "4. Search" << endl
    << "5. Smallest" << endl
    << "6. Largest" << endl
    << "7. Height" << endl
    << "8. Quit" << endl;
  cin >> choice;
  
  // fix buffer just in case non-numeric choice entered
  // also gets rid of newline character
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return choice;
}

int main( ) {
    // Pass all your tests before running the executable main
    BSTree tree;
    int input = menu();
    while(input != 8){
      if(input == 1){ //inserts node given string input
        string s; 
        cout << "Enter string to insert: ";
        getline(cin,s);
        cout << endl;
        tree.insert(s);
      } else if (input == 2){
        string s;
        cout << "Enter string to remove: ";
        getline(cin,s);
        cout << endl;
        tree.remove(s);
      } else if (input == 3){ //prints out all 3 types of print orders
        printOrders(&tree);
      } else if (input == 4){ //checks if key exists within the BST
        string key;
        cout << "Enter string to search for: ";
        getline(cin,key);
        cout << endl;
        if(tree.search(key)){
          cout << "Found" << endl;
        } else {
          cout << "Not Found" << endl;
        }
      } else if (input == 5){ //returns smallest node
        cout << "Smallest: " << tree.smallest() << endl;
      } else if (input == 6){ //returns largest node
        cout << "Largest: " << tree.largest() << endl;
      } else if (input == 7){ //returns height of given node
        string key;
        cout << "Enter string: ";
        getline(cin,key);
        cout << endl;
        cout << "Height of subtree rooted at " << key << ": " << tree.height(key) << endl;
      }
      input = menu();
    }
    return 0;
}
