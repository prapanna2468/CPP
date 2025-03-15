#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

// Merge function for Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

// Merge Sort function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Binary Search function
int binarySearch(const vector<int>& arr, int key) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main() {
    srand(time(0));
    int N;
    cout << "Enter the number of random integers: ";
    cin >> N;
    
    vector<int> arr(N);
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 1000; // Generating random numbers in range 0-999
    
    cout << "\nOriginal Array: ";
    for (int num : arr)
        cout << num << " ";
    cout << "\n";
    
    // Measure time taken for Merge Sort
    auto start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, N - 1);
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = stop - start;
    
    cout << "\nSorted Array: ";
    for (int num : arr)
        cout << num << " ";
    cout << "\nMerge Sort Time: " << duration.count() << " ms\n";
    
    // Searching
    int key;
    cout << "\nEnter an element to search: ";
    cin >> key;
    
    start = chrono::high_resolution_clock::now();
    int index = binarySearch(arr, key);
    stop = chrono::high_resolution_clock::now();
    duration = stop - start;
    
    if (index != -1)
        cout << "Element found at index: " << index << "\n";
    else
        cout << "Element not found.\n";
    
    cout << "Binary Search Time: " << duration.count() << " ms\n";
    return 0;
}
