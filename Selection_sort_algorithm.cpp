#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm> // For min
using namespace std;
// Function to perform Selection Sort on an array
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
        }
    }
}
// Function to generate N random integers
vector<int> generateRandomNumbers(int N) {
    vector<int> arr(N);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 100); // Range: 0 to 100
    for (int i = 0; i < N; i++) {
        arr[i] = dist(gen);
    }
    return arr;
}
// Function to print the array (entire if N <= 20, else first and last 5 elements)
void printArray(const vector<int>& arr, const string& label) {
    cout << label << ":\n";
    if (arr.size() <= 20) {
        for (int num : arr) {
            cout << num << " ";
        }
        cout << "\n";
    } else {
        cout << "Array is too large to display entirely. Showing first and last 5 elements.\n";
        int printCount = 5;
        cout << "First " << printCount << " elements: ";
        for (int i = 0; i < printCount; i++) {
            cout << arr[i] << " ";
        }
        cout << "\nLast " << printCount << " elements: ";
        for (int i = arr.size() - printCount; i < arr.size(); i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
}
int main() {
    int choice;
    vector<int> arr;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Set N and generate random numbers\n";
        cout << "2. Sort using Selection Sort\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                int N;
                cout << "Enter N (positive integer): ";
                cin >> N;
                if (N <= 0) {
                    cout << "N must be positive.\n";
                    break;
                }
                arr = generateRandomNumbers(N);
                cout << "Generated " << N << " random numbers.\n";
                printArray(arr, "Unsorted array"); // Show unsorted numbers
                break;
            }
            case 2: {
                if (arr.empty()) {
                    cout << "Please generate numbers first.\n";
                    break;
                }
                // Measure sorting time
                auto start = chrono::high_resolution_clock::now();
                selectionSort(arr);
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> elapsed = end - start;
                // Display results
                cout << "Selection Sort took " << elapsed.count() << " ms.\n";
                printArray(arr, "Sorted array"); // Show sorted numbers
                break;
            }
            case 3: {
                cout << "Exiting.\n";
                return 0;
            }
            default: {
                cout << "Invalid choice.\n";
            }
        }
    }
    return 0;
}
