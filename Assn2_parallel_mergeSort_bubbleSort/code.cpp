// paralle merge sort and bubble sort

#include <bits/stdc++.h>
#include <chrono>
#include <omp.h>
using namespace std;


void bubbleSort(vector<int> &arr){
    int n = arr.size();
    for(int i=0; i<n; i++){
        for(int j=0; j<n-i-1; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}




void bubbleSortParallel(vector<int> &arr){
    int n = arr.size();
    for(int i=0; i<n; i++){
        
        #pragma omp parallel for
        for(int j=0; j<n-i-1; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}



void merge(vector<int> &arr, int start, int mid, int end){
    vector<int> temp;
    int left = start, right = mid+1;

    while(left<=mid && right<=end){
        if(arr[left] <= arr[right]){
            temp.push_back(arr[left]);
            left++;
        }
        else{
            temp.push_back(arr[right]);
            right++;
        }
    }

    while(left<=mid){
        temp.push_back(arr[left]);
        left++;
    }

    while(right<=end){
        temp.push_back(arr[right]);
        right++;
    }

    for(int i=start; i<=end; i++){
        arr[i] = temp[i-start];
    }
}


void mergeSort(vector<int> &arr, int start, int end){
    if(end - start + 1 <= 1){
        return;
    }

    int mid = start + (end-start)/2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid+1, end);
    merge(arr, start, mid, end);
}




void mergeSortParallel(vector<int> &arr, int start, int end){
    if(end - start + 1 <= 1){
        return;
    }

    int mid = start + (end-start)/2;

    #pragma omp parallel sections
    {
        #pragma omp section
        mergeSortParallel(arr, start, mid);

        #pragma omp section
        mergeSortParallel(arr, mid+1, end);
    }
    
    merge(arr, start, mid, end);
}


void printArr(vector<int> &arr){
    for(auto num : arr) cout << num << " ";
    cout << "\n";
}


int main() {
    // int n;
    // cout << "Enter size of array: ";
    // cin >> n;

    // vector<int> arr (n);
    // cout << "Enter elements of array: ";
    // for(int i=0; i<n; i++) cin >> arr[i];


    int n = 12;
    vector<int> arr(n);
    for(int i=0; i<n; i++) arr[i] = 50-i+1;

    cout << "Input array: ";
    printArr(arr);


    vector<int> temp1 (arr.begin(), arr.end());
    cout << "\n-----------\nSequential bubble sort \n";
    auto start = chrono::high_resolution_clock().now();
    bubbleSort(temp1);
    auto stop = chrono::high_resolution_clock().now();
    cout << "Sorted array: ";
    printArr(temp1);
    cout << "Time taken by sequential bubble sort = " << chrono::duration_cast<chrono::microseconds> (stop - start).count() << " ms\n";



    vector<int> temp2 (arr.begin(), arr.end());
    cout << "\n-----------\nParallel bubble sort \n";
    start = chrono::high_resolution_clock().now();
    bubbleSortParallel(temp2);
    stop = chrono::high_resolution_clock().now();
    cout << "Sorted array: ";
    printArr(temp2);
    cout << "Time taken by parallel bubble sort = " << chrono::duration_cast<chrono::microseconds> (stop - start).count() << " ms\n";



    vector<int> temp3 (arr.begin(), arr.end());
    cout << "\n-----------\nSequential merge sort \n";
    start = chrono::high_resolution_clock().now();
    mergeSort(temp3, 0, n-1);
    stop = chrono::high_resolution_clock().now();
    cout << "Sorted array: ";
    printArr(temp3);
    cout << "Time taken by sequential merge sort = " << chrono::duration_cast<chrono::microseconds> (stop - start).count() << " ms\n";
    


    vector<int> temp4 (arr.begin(), arr.end());
    cout << "\n-----------\nParallel merge sort \n";
    start = chrono::high_resolution_clock().now();
    mergeSortParallel(temp4, 0, n-1);
    stop = chrono::high_resolution_clock().now();
    cout << "Sorted array: ";
    printArr(temp4);
    cout << "Time taken by parallel merge sort = " << chrono::duration_cast<chrono::microseconds> (stop - start).count() << " ms\n";


    return 0;
}


// g++ -fopenmp code.cpp -o output
// ./output 


// Input array: 51 50 49 48 47 46 45 44 43 42 41 40 

// -----------
// Sequential bubble sort 
// Sorted array: 40 41 42 43 44 45 46 47 48 49 50 51 
// Time taken by sequential bubble sort = 1 ms

// -----------
// Parallel bubble sort 
// Sorted array: 40 41 42 43 44 45 46 47 48 49 50 51 
// Time taken by parallel bubble sort = 1 ms

// -----------
// Sequential merge sort 
// Sorted array: 40 41 42 43 44 45 46 47 48 49 50 51 
// Time taken by sequential merge sort = 10 ms

// -----------
// Parallel merge sort 
// Sorted array: 40 41 42 43 44 45 46 47 48 49 50 51 
// Time taken by parallel merge sort = 7 ms
