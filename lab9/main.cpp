#include <iostream>
#include <ctime>
#include <cstdlib>


using namespace std;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds

/*
returns random integer
*/
int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

/*
fills an 3 arrays with random numbers
*/
void fillArrays(int arr1[], int arr2[],int arr3[]) {
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

/*
sorts list through pivot as midpoint
*/
int partitionMid(int arr[], int start, int end) {
    int pivot = arr[(start + end) / 2]; // Selecting the midpoint as pivot
    while (start <= end) {
        while (arr[start] < pivot) {
            start++;
        }
        while (arr[end] > pivot) {
            end--;
        }
        if (start <= end) {
            swap(arr[start], arr[end]);
            start++;
            end--;
        }
    }
    return start;
}

/*
sorts list by using the median of the 1st, middle, and last value as the pivot
*/
int partitionMedian(int numbers[], int i, int k) {
    int l,h,mid,med,pivot;
    mid = (i+k)/2;
    bool done = false;

    if ((numbers[mid]>=numbers[i] && numbers[mid]<=numbers[k]) || (numbers[mid]>=numbers[k] && numbers[mid]<=numbers[i])){ 
        med = mid;
    } else if ((numbers[i]<=numbers[mid] && numbers[i]>=numbers[k]) || (numbers[i]>=numbers[mid] && numbers[i]<=numbers[k])) { 
        med = i;
    } else if ((numbers[k]<=numbers[i] && numbers[k]>=numbers[mid]) || (numbers[k]>=numbers[i] && numbers[k]<=numbers[mid])) {
        med = k; 
    }

    pivot = numbers[med]; //make the pivot the median 
    l = i;
    h = k;
    
    while (!done) {
        while (numbers[l] < pivot) {
            l++;
        }
        while (pivot < numbers[h]) {
            h--;
        }
        if (l >= h) {
            done = true;
        } else {
            swap(numbers[l],numbers[h]);
            l++;
            h--;
        }
    }
    
    return h;
}

/*
this function sorts the given array in the range from i to k using quicksort method. 
In this function, pivot is the midpoint element (numbers[(i+k)/2]). 
(implementation of this function is given in section 21.5)
*/
void Quicksort_midpoint(int numbers[], int i, int k) {
    if (i >= k) {
        return;
    }
    int index = partitionMid(numbers, i, k);
    Quicksort_midpoint(numbers, i, index - 1);
    Quicksort_midpoint(numbers, index, k);
}

/*
this function utilizes different pivot selection technique in quicksort algorithm. 
The pivot is the median of the following three values: leftmost (numbers[i]), midpoint (numbers[(i+k)/2]) and rightmost (numbers[k]). 
You should modify the partition function given in section 21.5 to select the pivot using median-of-three technique.
*/
void Quicksort_medianOfThree(int numbers[], int i, int k) {
    if (i >= k) {
       return;
    }
    int index = partitionMedian(numbers, i, k); 
    Quicksort_medianOfThree(numbers,i,index); 
    Quicksort_medianOfThree(numbers, index +1, k); 
}

/*
this function sorts the given array using InsertionSort method.
(implementation of this method is provided in section 21.3).
*/
void InsertionSort(int numbers[], int numbersSize) {
    int i, key, j;
    for (i = 1; i < numbersSize; i++) {
        key = numbers[i];
        j = i - 1;

        // Move elements of array that are greater than key, to one position ahead of their current position
        while (j >= 0 && numbers[j] > key) {
            numbers[j + 1] = numbers[j];
            j = j - 1;
        }
        numbers[j + 1] = key;
    }
}

int main () {
    int arr1 [NUMBERS_SIZE];
    int arr2 [NUMBERS_SIZE];
    int arr3 [NUMBERS_SIZE];
    fillArrays(arr1,arr2,arr3);

    //Quicksort MIDPOINT
        clock_t Start = clock();
        Quicksort_midpoint(arr1,0,NUMBERS_SIZE);
        clock_t End = clock();
        int elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
        cout << "time took quicksortMidpoint: " << elapsedTime << endl;
    //Quicksort MEDIAN
        Start = clock();
        Quicksort_medianOfThree(arr2,0,NUMBERS_SIZE);
        End = clock();
        elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
        cout << "time took quicksortMedian: " << elapsedTime << endl;
    //Insertion sort
        Start = clock();
        InsertionSort(arr3,NUMBERS_SIZE);
        End = clock();
        elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
        cout << "time took insertionSort: " << elapsedTime << endl;
    return 0;
} 
