#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <limits>
 
using namespace std;
  
class SearchApplication {
private:
    vector<int> numbers;
 
    // Function to generate N random integers
    void generateRandomNumbers(int N) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 1000);
 
        numbers.clear();
        for (int i = 0; i < N; ++i) {
            numbers.push_back(distrib(gen));
        }
    }
 
    // Binary search implementation
    int binarySearch(const vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;
 
        while (left <= right) {
            int mid = left + (right - left) / 2;
 
            if (arr[mid] == target) {
                return mid;
            }
 
            if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
 
        return -1;
    }
 
    // Performance analysis method
    void performBinarySearchAnalysis() {
        ofstream outputFile("binary_search_analysis.csv");
        outputFile << "Input Size,Best Case (ns),Average Case (ns),Worst Case (ns),Theoretical Log2(N)" << endl;
 
        vector<int> inputSizes = {100, 500, 1000, 5000, 10000, 50000, 100000};
 
        for (int N : inputSizes) {
            // Generate and sort numbers
            vector<int> analysisNumbers;
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(1, 100000);
 
            analysisNumbers.reserve(N);
            for (int i = 0; i < N; ++i) {
                analysisNumbers.push_back(distrib(gen));
            }
            sort(analysisNumbers.begin(), analysisNumbers.end());
 
            // Best Case: Middle element
            int bestCaseTarget = analysisNumbers[analysisNumbers.size() / 2];
            
            // Average Case: Random element
            uniform_int_distribution<> indexDistrib(0, analysisNumbers.size() - 1);
            int averageCaseTarget = analysisNumbers[indexDistrib(gen)];
            
            // Worst Case: Element not in array
            int worstCaseTarget = analysisNumbers.back() + 1;
 
            // Measure runtime for best case
            auto startBest = chrono::high_resolution_clock::now();
            binarySearch(analysisNumbers, bestCaseTarget);
            auto endBest = chrono::high_resolution_clock::now();
            auto bestCaseDuration = chrono::duration_cast<chrono::nanoseconds>(endBest - startBest).count();
 
            // Measure runtime for average case
            auto startAverage = chrono::high_resolution_clock::now();
            binarySearch(analysisNumbers, averageCaseTarget);
            auto endAverage = chrono::high_resolution_clock::now();
            auto averageCaseDuration = chrono::duration_cast<chrono::nanoseconds>(endAverage - startAverage).count();
 
            // Measure runtime for worst case
            auto startWorst = chrono::high_resolution_clock::now();
            binarySearch(analysisNumbers, worstCaseTarget);
            auto endWorst = chrono::high_resolution_clock::now();
            auto worstCaseDuration = chrono::duration_cast<chrono::nanoseconds>(endWorst - startWorst).count();
 
            // Log results
            outputFile << N << ","
                       << bestCaseDuration << ","
                       << averageCaseDuration << ","
                       << worstCaseDuration << ","
                       << log2(N) << endl;
        }
 
        outputFile.close();
        cout << "Binary Search Performance Analysis Complete." << endl;
        cout << "Results saved to binary_search_analysis.csv" << endl;
    }
 
public:
    // Function to perform search operation
    void performSearch() {
        int N, searchElement;
 
        // Get number of elements from user
        cout << "Enter the number of random integers to generate: ";
        cin >> N;
 
        // Validate input
        while (N <= 0) {
            cout << "Please enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> N;
        }
 
        // Generate random numbers
        generateRandomNumbers(N);
 
        // Sort the array (required for binary search)
        sort(numbers.begin(), numbers.end());
 
        // Print the sorted array
        cout << "Sorted Array: ";
        for (int num : numbers) {
            cout << num << " ";
        }
        cout << endl;
 
        // Get search element from user
        cout << "Enter the element to search: ";
        cin >> searchElement;
 
        // Perform binary search
        int result = binarySearch(numbers, searchElement);
 
        // Display search result
        if (result != -1) {
            cout << "Element " << searchElement 
                 << " found at index " << result << endl;
        } else {
            cout << "Element " << searchElement 
                 << " not found in the array." << endl;
        }
    }
 
    // New method to trigger performance analysis
    void runPerformanceAnalysis() {
        performBinarySearchAnalysis();
    }
};
 
int main() {
    SearchApplication searchApp;
    
    char choice;
    do { 
        cout << "\nMenu:\n";
        cout << "1. Perform Search\n";
        cout << "2. Run Performance Analysis\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
 
        switch(choice) {
            case '1':
                searchApp.performSearch();
                break;
            case '2':
                searchApp.runPerformanceAnalysis();
                break;
            case '3':
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '3');
 
    return 0;
}
