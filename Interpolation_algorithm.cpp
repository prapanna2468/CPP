#include <iostream>
#include <vector>
#include <chrono> // For measuring runtime
#include <cstdlib> // For rand() and srand()
#include <ctime> // For seeding rand()

using namespace std;
using namespace std::chrono;

// Function to generate random sorted array
vector<int> generateSortedArray(int size) {
    vector<int> arr(size);
    srand(time(0));
    arr[0] = rand() % 10; // First element
    for (int i = 1; i < size; i++) {
        arr[i] = arr[i - 1] + (rand() % 10 + 1); // Ensure ascending order
    }
    return arr;
}

// Interpolation Search algorithm
int interpolationSearch(vector<int>& arr, int key) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high && key >= arr[low] && key <= arr[high]) {
        if (low == high) {
            if (arr[low] == key) return low;
            return -1;
        }

        // Interpolation formula
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (key - arr[low]));

        if (arr[pos] == key) return pos;
        if (arr[pos] < key) low = pos + 1;
        else high = pos - 1;
    }
    return -1; // Key not found
}

// Function to measure runtime and perform search
void runInterpolationSearch(int size, int key) {
    vector<int> arr = generateSortedArray(size);

    cout << "\nGenerated Sorted Array (Size " << size << "): ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "\nSearching for: " << key << endl;

    auto start = high_resolution_clock::now(); // Start time
    int result = interpolationSearch(arr, key);
    auto stop = high_resolution_clock::now(); // End time
    auto duration = duration_cast<microseconds>(stop - start); // Runtime in microseconds

    if (result != -1)
        cout << "Element found at index: " << result << endl;
    else
        cout << "Element not found!" << endl;

    cout << "Actual Runtime: " << duration.count() << " microseconds" << endl;
}

int main() {
    int key;
    cout << "Enter the element to search: ";
    cin >> key;

    // Test with multiple input sizes
    int sizes[] = {10, 50, 100, 500, 1000};
    for (int size : sizes) {
        runInterpolationSearch(size, key);
    }

    return 0;
}
