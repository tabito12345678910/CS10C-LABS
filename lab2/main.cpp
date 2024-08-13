#include <iostream>
#include "IntList.h"
using namespace std;

int main(){

    int test;
    cout<<"Input test number"<<endl;
    cin>>test;

    if(test == 0){
        IntList testList;
    
        if(!testList.empty()){
            cout<<"empty() error"<<endl;
        }
        else{
            cout<<"empty() works"<<endl;
        }

    }

    if(test == 1){
        IntList testList;
        testList.push_back(3);
        testList.push_front(5);
        cout<<"Should print 5 3 Outcome: "<<testList<<endl;

    }
    if(test == 2){
        IntList testList;
        testList.push_back(3);
        testList.push_front(5);
        testList.push_back(1);
        testList.pop_front();
        testList.pop_back();
        cout<<"Should print 3 Outcome: "<<testList<<endl;
    }

    if(test == 3){
        IntList testList;
        testList.push_back(3);
        testList.push_front(5);
        testList.push_back(1);
        testList.printReverse();
        cout<<"Should print 1 3 5 Outcome: "<<testList<<endl;
    }





    

    
    
}
