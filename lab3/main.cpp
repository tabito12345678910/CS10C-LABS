#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>


using namespace std;

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index){
    int min = index;
    while(index<vals.size()){
        if(vals[index]<vals[min]){
            min = index;
        }
        ++index;
    }
    return min;
}

template<typename T>

void selection_sort(vector<T> &vals){
    for(unsigned int i = 0; i<vals.size(); ++i){
        swap(vals[i], vals[min_index(vals,i)]);
    }
}

template<typename T>
T getElement(vector<T> vals, unsigned int index){
    if(index<  0||index>vals.size()){
        throw out_of_range("out of range exception occured");
    }
    return vals.at(index);
}

template<typename T>
vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

int main(){

    //Part B
    /*
     srand(time(0));
     vector<char> vals = createVector();
     char curChar;
     int index;
     int numOfRuns = 10;
     while(numOfRuns >= 0){
         cout << "Enter a number: " << endl;
         cin >> index;
         curChar = getElement(vals,index);
         cout << "Element located at " << index << ": is " << curChar << endl;
    }
    */
    

    vector<int> test1{5,3,11,34,9};
    vector<double> test2{5.3,3.1,11.2,34.7,9.5};
    vector<string> test3{"five", "three", "eleven", "thirtyfour", "nine"};
    selection_sort(test1);
    unsigned int i = 0;
    while(i < test1.size()-1){
        if(test1[i] > test1[i+1]) {
            cout << "test1 'selection_sort' failed" << endl;
        }
        i++;
    }
   
    selection_sort(test2);
    i = 0;
    while(i < test2.size()-1){
        if(test2[i] > test2[i+1]) {
            cout << "test1 'selection_sort' failed" << endl;
        }
        i++;
    }
 
    selection_sort(test3);
    i = 0;
    while(i < test1.size()-1){
        if(test3[i] > test3[i+1]) { 
            cout << "test1 'selection_sort' failed" << endl;
        }
        i++;
    }



    
   

    



    return 0; 
}
