#include <iostream>
#include "Heap.h"
using namespace std;

Heap::Heap(){
    numItems = 0; //empty heap
}

void Heap::enqueue(PrintJob *job){
    if(numItems==MAX_HEAP_SIZE){
        return; //prevent overflow
    }
    else if(numItems == 0){ //empty heap
        arr[0] = job; 
        ++numItems;
    }
    else{ //value percolates up to correct spot
        arr[numItems] = job;
        ++numItems; 
        trickleUp(numItems-1);
    }
}

void Heap::dequeue(){
    if(numItems == 0 || numItems == 1){ //if empty or only root
        numItems = 0; 
        return;
    } else {
        swap(arr[0], arr[numItems-1]); //swaps last node to root
        numItems--; 
        trickleDown(0); //percolates the swapped node down
    }   
}

PrintJob* Heap::highest(){
    if(numItems > 0){
        return arr[0];
    } 
    else{//nullptr if heap is empty
        return nullptr;
    }
}

void Heap::print(){
    cout << "Priority: " << arr[0]->getPriority() << ", ";
    cout << "Job Number: " << arr[0]->getJobNumber() << ", ";
    cout << "Number of Pages: " << arr[0]->getPages() << endl;
}

void Heap::trickleDown(int currentIndex){
    int childIndex = 2*currentIndex + 1; //child of the index node
    int currentValue = arr[currentIndex]->getPriority();

    while(childIndex < numItems){
        int maxValue = currentValue;
        int maxIndex = childIndex;
        for(int i = 0; i < 2 && i+childIndex < numItems; i++){ // Finds largest child node, assigns its index and value to variables
            if(maxValue < arr[childIndex + i]->getPriority()){
                maxValue = arr[childIndex + i]->getPriority();
                maxIndex = childIndex + i;
            }
        }

        if(maxValue == currentValue) { 
            return;
        } else { //swaps the root with highest node
            swap(arr[maxIndex], arr[currentIndex]);
            currentIndex = maxIndex;
            childIndex = currentIndex*2 + 1;
        }
    }
}

void Heap::trickleUp(int currentIndex){
    while(currentIndex > 0){
        int parentIndex = (currentIndex-1) / 2; //index for parent
        if(arr[currentIndex]->getPriority() <= arr[parentIndex]->getPriority()){ //if new node added is smaller/equal, keeps position
            return;
        } else { //percolates new node up, switching with parent node
            swap(arr[currentIndex], arr[parentIndex]);
            currentIndex = parentIndex; 
        }
    }
}

