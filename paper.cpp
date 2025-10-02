/**
* This code requires a lot of memory to run.
* I recommend compiling and running this code on a GL server
**/

#include <iostream>
#include <cstdlib>  
#include <ctime> 
#include <algorithm> 
#include <chrono>
using namespace std;

void selection(int arr[], int arrSize){
    int minimum;
    int adjust = arrSize - 1;

    for (int i = 0; i < adjust; i++) {
        minimum = i;
        int adjustIdx = i + 1;

        for (int j = adjustIdx; j < arrSize; j++) {
            if (arr[minimum] > arr[j]) {
                minimum = j;
            }
        }
        if (minimum != i) {
            swap(arr[minimum], arr[i]);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insertion(int arr[], int arrSize){
    int temp;
    for (int i = 1; i < arrSize; i++) {
        temp = arr[i];
        int idx = i - 1;

        while (idx >= 0 && arr[idx] > temp) {
            arr[idx + 1] = arr[idx];
            idx -= 1;
        }
        arr[idx + 1] = temp;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void merge1(int arr[], int const L, int const center, int const R){
    int const subArr1 = center - L + 1;
    int const subArr2 = R - center;

    int* arrL = new int[subArr1];
    int* arrR = new int[subArr2];

    for (int i = 0; i < subArr1; i++) {
        arrL[i] = arr[L + i];
    }

    for (int j = 0; j < subArr2; j++) {
        arrR[j] = arr[center + 1 + j];
    }

    int index1 = 0;
    int index2 = 0;
    int mergeIndex = L;

    while ((subArr2 > index2) && (subArr1 > index1)) {
        if (arrR[index2] >= arrL[index1]) {
            arr[mergeIndex] = arrL[index1];
            index1++;
        }
        else {
            arr[mergeIndex] = arrR[index2];
            index2++;
        }
        mergeIndex++;
    }

    while (subArr1 > index1) {
        arr[mergeIndex] = arrL[index1];
        index1 += 1;
        mergeIndex += 1;
    }

    while (subArr2 > index2) {
        arr[mergeIndex] = arrR[index2];
        index2 += 1;
        mergeIndex += 1;
    }
    delete[] arrL;
    delete[] arrR;
}

void merge2(int arr[], int const start, int const finish){
    if (finish <= start) {
        return;
    }

    int hold1 = (finish - start) / 2;
    int center = start + hold1;
    merge2(arr, start, center);
    int hold2 = center + 1;
    merge2(arr, hold2, finish);
    merge1(arr, start, center, finish);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int partition(int arr[],int min,int max){
    int pivot = arr[max];
    int hold = (min - 1);
   
    for(int i = min;i <= max;i++)  {
        if(arr[i]<pivot){
            hold += 1;
            swap(arr[hold],arr[i]);
        }
    }
    swap(arr[hold + 1],arr[max]);
    return (hold + 1);
}
            
void quick(int arr[],int min,int max){
    if(min < max)  {
        int hold = partition(arr, min, max);
        quick(arr, min, hold - 1);
        quick(arr, hold + 1, max);
    }
}

void initializeArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000; // Generating random integers between 0 and 999
    }
}

int main(){
    srand(time(nullptr));

    const int arraySize = 1000;
    const int arraySize2 = 10000;
    const int arraySize3 = 100000;

    cout << "#################################Start selection sort#######################################################\n";

    cout << "\nStart 1000 size selection sort-------------------------------------------------\n";
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize];
        initializeArray(arr, arraySize);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        selection(arr, n);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;


        cout << "Selection sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }

    cout << "\nStart 100000 size selection sort-------------------------------------------------\n";
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize2];
        initializeArray(arr, arraySize2);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        selection(arr, n);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;


        cout << "Selection sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }

    cout << "\nStart 1000000 size selection sort-------------------------------------------------\n";

    for (int i = 0; i < 10; ++i) {
        int arr[arraySize3];
        initializeArray(arr, arraySize3);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        selection(arr, n);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;


        cout << "Selection sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }

    cout << "\n#################################Start insertion sort#######################################################\n";

    cout << "\nStart 1000 size insertion sort-------------------------------------------------\n";
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize];
        initializeArray(arr, arraySize);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        insertion(arr, n);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;


        cout << "Insertion sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }

    cout << "\nStart 100000 size insertion sort-------------------------------------------------\n";
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize2];
        initializeArray(arr, arraySize2);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        insertion(arr, n);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;


        cout << "Insertion sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }

    cout << "\nStart 1000000 size insertion sort-------------------------------------------------\n";

    for (int i = 0; i < 10; ++i) {
        int arr[arraySize3];
        initializeArray(arr, arraySize3);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        insertion(arr, n);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;


        cout << "Insertion sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }

    cout << "#################################Start merge sort#######################################################\n";

    cout << "\nStart 1000 size merge sort-------------------------------------------------\n";
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize];
        initializeArray(arr, arraySize);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        merge2(arr, 0, n - 1);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;


        cout << "Merge sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }
    
    cout << "\nStart 100000 size merge sort-------------------------------------------------\n";
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize2];
        initializeArray(arr, arraySize2);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        merge2(arr, 0, n - 1);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;


        cout << "Merge sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }

    cout << "\nStart 1000000 size merge sort-------------------------------------------------\n";

    for (int i = 0; i < 10; ++i) {
        int arr[arraySize3];
        initializeArray(arr, arraySize3);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        merge2(arr, 0, n - 1);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;


        cout << "Merge sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }
    

    cout << "\n#################################Start quick sort#######################################################\n";

    cout << "\nStart 1000 size quick sort-------------------------------------------------\n";
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize];
        initializeArray(arr, arraySize);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        quick(arr, 0, n - 1);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;


        cout << "Quick sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }

    cout << "\nStart 100000 size quick sort-------------------------------------------------\n";
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize2];
        initializeArray(arr, arraySize2);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        quick(arr, 0, n - 1);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;


        cout << "Quick sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }

    cout << "\nStart 1000000 size quick sort-------------------------------------------------\n";

    for (int i = 0; i < 10; ++i) {
        int arr[arraySize3];
        initializeArray(arr, arraySize3);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        quick(arr, 0, n - 1);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;


        cout << "Quick sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }

    return 0;
}

