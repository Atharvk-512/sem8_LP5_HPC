// parallel reductions
// min, max, sum, avg

#include <bits/stdc++.h>
#include <chrono>
#include <omp.h>
using namespace std;



void findMinimumSequential(vector<int> &arr){
    int n = arr.size();
    int mini = arr[0];

    auto start = chrono::high_resolution_clock().now();

    for(int i=1; i<n; i++){
        if(arr[i] < mini) mini = arr[i];
    }

    auto stop = chrono::high_resolution_clock().now();

    cout << "Sequential\n";
    cout << "Min value = " << mini << "\n";
    cout << "Runtime = " << (stop - start).count() << "\n";
}



void findMinimumParallel(vector<int> &arr){
    int n = arr.size();
    int mini = arr[0];

    auto start = chrono::high_resolution_clock().now();
    
    #pragma omp parallel for reduction(min : mini)
    for(int i=1; i<n; i++){
        if(arr[i] < mini) mini = arr[i];
    }

    auto stop = chrono::high_resolution_clock().now();

    cout << "Parallel Reduction\n";
    cout << "Min value = " << mini << "\n";
    cout << "Runtime = " << (stop - start).count() << "\n";
}




void findMaximumSequential(vector<int> &arr){
    int n = arr.size();
    int maxi = arr[0];

    auto start = chrono::high_resolution_clock().now();

    for(int i=1; i<n; i++){
        if(arr[i] > maxi) maxi = arr[i];
    }

    auto stop = chrono::high_resolution_clock().now();

    cout << "Sequential\n";
    cout << "Max value = " << maxi << "\n";
    cout << "Runtime = " << (stop - start).count() << "\n";
}




void findMaximumParallel(vector<int> &arr){
    int n = arr.size();
    int maxi = arr[0];

    auto start = chrono::high_resolution_clock().now();
    
    #pragma omp parallel for reduction(max : maxi)
    for(int i=1; i<n; i++){
        if(arr[i] > maxi) maxi = arr[i];
    }

    auto stop = chrono::high_resolution_clock().now();

    cout << "Parallel Reduction\n";
    cout << "Max value = " << maxi << "\n";
    cout << "Runtime = " << (stop - start).count() << "\n";
}





void findSumSequential(vector<int> &arr){
    int n = arr.size();
    int sum = 0;

    auto start = chrono::high_resolution_clock().now();

    for(int i=0; i<n; i++){
        sum += arr[i];
    }

    auto stop = chrono::high_resolution_clock().now();

    cout << "Sequential\n";
    cout << "Sum = " << sum << "\n";
    cout << "Runtime = " << (stop - start).count() << "\n";
}




void findSumParallel(vector<int> &arr){
    int n = arr.size();
    int sum = 0;

    auto start = chrono::high_resolution_clock().now();
    
    #pragma omp parallel for reduction(+ : sum)
    for(int i=0; i<n; i++){
        sum += arr[i];
    }

    auto stop = chrono::high_resolution_clock().now();

    cout << "Parallel Reduction\n";
    cout << "Sum = " << sum << "\n";
    cout << "Runtime = " << (stop - start).count() << "\n";
}





void findAvgSequential(vector<int> &arr){
    int n = arr.size();
    int sum = 0;

    auto start = chrono::high_resolution_clock().now();

    for(int i=0; i<n; i++){
        sum += arr[i];
    }
    double avg = sum / n;

    auto stop = chrono::high_resolution_clock().now();

    cout << "Sequential\n";
    cout << "Avg = " << avg << "\n";
    cout << "Runtime = " << (stop - start).count() << "\n";
}




void findAvgParallel(vector<int> &arr){
    int n = arr.size();
    int sum = 0;

    auto start = chrono::high_resolution_clock().now();
    
    #pragma omp parallel for reduction(+ : sum)
    for(int i=0; i<n; i++){
        sum += arr[i];
    }
    double avg = sum / n;
    
    auto stop = chrono::high_resolution_clock().now();

    cout << "Parallel Reduction\n";
    cout << "Avg = " << avg << "\n";
    cout << "Runtime = " << (stop - start).count() << "\n";
}





int main() {
    // int n;
    // cout << "Enter size of array: ";
    // cin >> n;

    // vector<int> arr (n);
    // cout << "Enter elements of array: ";
    // for(int i=0; i<n; i++) cin >> arr[i];



    int n = 10000;
    vector<int> arr(n);
    for(int i=0; i<n; i++) arr[i] = rand() % 10000 + 1;


    cout << "---------- Find Minimum ----------\n";
    findMinimumSequential(arr);
    findMinimumParallel(arr);

    cout << "---------- Find Maximum ----------\n";
    findMaximumSequential(arr);
    findMaximumParallel(arr);

    cout << "---------- Find Sum ----------\n";
    findSumSequential(arr);
    findSumParallel(arr);


    cout << "---------- Find Average ----------\n";
    findAvgSequential(arr);
    findAvgParallel(arr);



    return 0;
}




//  g++ -fopenmp code.cpp -o output
// ./output 


// ---------- Find Minimum ----------
// Sequential
// Min value = 1
// Runtime = 32929
// Parallel Reduction
// Min value = 1
// Runtime = 222629
// ---------- Find Maximum ----------
// Sequential
// Max value = 10000
// Runtime = 45957
// Parallel Reduction
// Max value = 10000
// Runtime = 12265
// ---------- Find Sum ----------
// Sequential
// Sum = 49975211
// Runtime = 45322
// Parallel Reduction
// Sum = 49975211
// Runtime = 12360
// ---------- Find Average ----------
// Sequential
// Avg = 4997
// Runtime = 45812
// Parallel Reduction
// Avg = 4997
// Runtime = 12117
