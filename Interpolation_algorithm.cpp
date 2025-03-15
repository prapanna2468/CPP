#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Interpolation search function
int interpolationSearch(const vector<int>& arr, int key) {
    int low = 0, high = arr.size() - 1;
    
    while (low <= high && key >= arr[low] && key <= arr[high]) {
        // Avoid division by zero
        if (arr[low] == arr[high]) {
            if (arr[low] == key) return low;
            else return -1;
        }
        
        // Probing position formula
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (key - arr[low]));

        // If found
        if (arr[pos] == key)
            return pos;

        // If key is larger, move right
        if (arr[pos] < key)
            low = pos + 1;
        else  // Move left
            high = pos - 1;
    }
    return -1; // Not found
}

int main() {
    srand(time(0));
    
    int N;
    cout << "Enter the number of random integers: ";
    cin >> N;

    vector<int> numbers(N);

    // Generate random numbers
    cout << "Generated numbers: ";
    for (int i = 0; i < N; i++) {
        numbers[i] = rand() % 100; // Numbers between 0 and 99
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Sorting the numbers
    sort(numbers.begin(), numbers.end());
    cout << "Sorted numbers: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // Searching for an element
    int searchKey;
    cout << "Enter a number to search: ";
    cin >> searchKey;

    int index = interpolationSearch(numbers, searchKey);
    if (index != -1)
        cout << "Element found at index: " << index << endl;
    else
        cout << "Element not found!" << endl;

    return 0;
}

