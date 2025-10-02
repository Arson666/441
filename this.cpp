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

//selection sort function
void selection(int arr[], int arrSize) {
    int minimum;
    int adjust = arrSize - 1;

    //loop through arr
    for (int i = 0; i < adjust; i++) {
        minimum = i;
        int adjustIdx = i + 1;

        //find minimum element in the unsorted sub arr
        for (int j = adjustIdx; j < arrSize; j++) {
            if (arr[minimum] > arr[j]) {
                minimum = j;
            }
        }
        //swap minimum with first element
        if (minimum != i) {
            swap(arr[minimum], arr[i]);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//insertion sort
void insertion(int arr[], int arrSize) {
    int temp;
    for (int i = 1; i < arrSize; i++) {
        temp = arr[i];
        int idx = i - 1;

        //move elements of arr[0 to (i-1)], that are greater than temp, to one position ahead of current position
        while (idx >= 0 && arr[idx] > temp) {
            arr[idx + 1] = arr[idx];
            idx -= 1;
        }
        arr[idx + 1] = temp;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//merge two subarrs of arr[]
void merge1(int arr[], int const L, int const center, int const R) {
    int const subArr1 = center - L + 1;
    int const subArr2 = R - center;

    int* arrL = new int[subArr1];
    int* arrR = new int[subArr2];

    //copy data to temp arrs arrL[] and arrR[]
    for (int i = 0; i < subArr1; i++) {
        arrL[i] = arr[L + i];
    }

    for (int j = 0; j < subArr2; j++) {
        arrR[j] = arr[center + 1 + j];
    }

    //merge temp arrs back into full arr
    int index1 = 0;
    int index2 = 0;
    int mergeIndex = L;

    do {
        if (arrR[index2] >= arrL[index1]) {
            arr[mergeIndex] = arrL[index1];
            index1++;
        }
        else {
            arr[mergeIndex] = arrR[index2];
            index2++;
        }
        mergeIndex++;
    } while ((subArr2 > index2) && (subArr1 > index1));

    //copy existing remaining elements of arrL[]
    do {
        arr[mergeIndex] = arrL[index1];
        index1 += 1;
        mergeIndex += 1;
    } while (subArr1 > index1);

    //copy existing remaining elements of arrR[]
    do {
        arr[mergeIndex] = arrR[index2];
        index2 += 1;
        mergeIndex += 1;
    } while (subArr2 > index2);

    delete[] arrL;
    delete[] arrR;
}

//recursively merge sort an arr
void merge2(int arr[], int const start, int const finish) {
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

//split arr and return the split index
int split(int arr[], int min, int max) {
    int change = arr[max];
    int hold = (min - 1);

    for (int i = min; i <= max; i++) {
        if (arr[i] < change) {
            hold += 1;
            swap(arr[hold], arr[i]);
        }
    }
    swap(arr[hold + 1], arr[max]);
    return (hold + 1);
}

//quick sort
void quick(int arr[], int min, int max) {
    if (min < max) {
        int hold = split(arr, min, max);
        quick(arr, min, hold - 1);
        quick(arr, hold + 1, max);
    }
}

//initialize arr
void initializeArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000; //generate random nums 0 to 999
    }
}
int main(){
    srand(time(nullptr));

    const int arraySize = 1000;
    const int arraySize2 = 10000;
    const int arraySize3 = 100000;

    cout << "#################################Start selection sort#######################################################\n";

    cout << "\nStart 1000 size selection sort-------------------------------------------------\n";
    double totalTime1 = 0.0;
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize];
        initializeArray(arr, arraySize);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        selection(arr, n);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        totalTime1 += elapsed_seconds.count();

        cout << "Selection sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }
    double averageTime1 = totalTime1 / 10.0; //calculate average time
    cout << "Average time: " << averageTime1 << "s\n";

    cout << "\nStart 100000 size selection sort-------------------------------------------------\n";
    double totalTime2 = 0.0;
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize2];
        initializeArray(arr, arraySize2);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        selection(arr, n);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        totalTime2 += elapsed_seconds.count();

        cout << "Selection sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }
    double averageTime2 = totalTime2 / 10.0; //calculate average time
    cout << "Average time: " << averageTime2 << "s\n";

    cout << "\nStart 1000000 size selection sort-------------------------------------------------\n";
    double totalTime3 = 0.0;
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize3];
        initializeArray(arr, arraySize3);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        selection(arr, n);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        totalTime3 += elapsed_seconds.count();

        cout << "Selection sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }
    double averageTime3 = totalTime3 / 10.0; //calculate average time
    cout << "Average time: " << averageTime3 << "s\n";

    cout << "\n#################################Start insertion sort#######################################################\n";

    cout << "\nStart 1000 size insertion sort-------------------------------------------------\n";
    double totalTime4 = 0.0;
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize];
        initializeArray(arr, arraySize);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        insertion(arr, n);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        totalTime4 += elapsed_seconds.count();

        cout << "Insertion sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }
    double averageTime4 = totalTime4 / 10.0; //calculate average time
    cout << "Average time: " << averageTime4 << "s\n";

    cout << "\nStart 100000 size insertion sort-------------------------------------------------\n";
    double totalTime5 = 0.0;
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize2];
        initializeArray(arr, arraySize2);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        insertion(arr, n);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        
        totalTime5 += elapsed_seconds.count();

        cout << "Insertion sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }
    double averageTime5 = totalTime5 / 10.0; //calculate average time
    cout << "Average time: " << averageTime5 << "s\n";

    cout << "\nStart 1000000 size insertion sort-------------------------------------------------\n";
    double totalTime6 = 0.0;
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize3];
        initializeArray(arr, arraySize3);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        insertion(arr, n);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        totalTime6 += elapsed_seconds.count();

        cout << "Insertion sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }
    double averageTime6 = totalTime6 / 10.0; //calculate average time
    cout << "Average time: " << averageTime6 << "s\n";

    cout << "#################################Start merge sort#######################################################\n";

    cout << "\nStart 1000 size merge sort-------------------------------------------------\n";
    double totalTime7 = 0.0;
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize];
        initializeArray(arr, arraySize);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        merge2(arr, 0, n - 1);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        totalTime7 += elapsed_seconds.count();

        cout << "Merge sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }
    double averageTime7 = totalTime7 / 10.0; //calculate average time
    cout << "Average time: " << averageTime7 << "s\n";
    
    cout << "\nStart 100000 size merge sort-------------------------------------------------\n";
    double totalTime8 = 0.0;
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize2];
        initializeArray(arr, arraySize2);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        merge2(arr, 0, n - 1);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        totalTime8 += elapsed_seconds.count();

        cout << "Merge sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }
    double averageTime8 = totalTime8 / 10.0; //calculate average time
    cout << "Average time: " << averageTime8 << "s\n";

    cout << "\nStart 1000000 size merge sort-------------------------------------------------\n";
    double totalTime9 = 0.0;
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize3];
        initializeArray(arr, arraySize3);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        merge2(arr, 0, n - 1);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        totalTime9 += elapsed_seconds.count();

        cout << "Merge sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }
    double averageTime9 = totalTime9 / 10.0; //calculate average time
    cout << "Average time: " << averageTime9 << "s\n";

    cout << "\n#################################Start quick sort#######################################################\n";

    cout << "\nStart 1000 size quick sort-------------------------------------------------\n";
    double totalTime10 = 0.0;
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize];
        initializeArray(arr, arraySize);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        quick(arr, 0, n - 1);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        totalTime10 += elapsed_seconds.count();

        cout << "Quick sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }
    double averageTime10 = totalTime10 / 10.0; //calculate average time
    cout << "Average time: " << averageTime10 << "s\n";

    cout << "\nStart 100000 size quick sort-------------------------------------------------\n";
    double totalTime11 = 0.0;
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize2];
        initializeArray(arr, arraySize2);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        quick(arr, 0, n - 1);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        totalTime11 += elapsed_seconds.count();

        cout << "Quick sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }
    double averageTime11 = totalTime11 / 10.0; //calculate average time
    cout << "Average time: " << averageTime11 << "s\n";

    cout << "\nStart 1000000 size quick sort-------------------------------------------------\n";
    double totalTime12 = 0.0;
    for (int i = 0; i < 10; ++i) {
        int arr[arraySize3];
        initializeArray(arr, arraySize3);
        int n = sizeof(arr) / sizeof(arr[0]);

        auto start = chrono::steady_clock::now();

        quick(arr, 0, n - 1);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        totalTime12 += elapsed_seconds.count();

        cout << "Quick sort array time " << i + 1 << ": " << elapsed_seconds.count() << "s\n";
    }
    double averageTime12 = totalTime12 / 10.0; //calculate average time
    cout << "Average time: " << averageTime12 << "s\n";

    return 0;
}

