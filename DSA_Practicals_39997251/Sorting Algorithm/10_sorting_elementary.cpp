#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
using namespace std;

// ============================================================================
// SORTING ALGORITHMS - ELEMENTARY SORTS
// ============================================================================

// ============================================================================
// 1. BUBBLE SORT
// ============================================================================
// Description: Repeatedly steps through list, compares adjacent elements
//              and swaps them if in wrong order. "Bubbles" largest to end.
// Time: O(n²) worst/average, O(n) best case (already sorted)
// Space: O(1) - sorts in place
// Stable: YES - maintains relative order of equal elements
// When to use: Educational purposes, nearly sorted data, small datasets
// ============================================================================

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    
    // Outer loop: number of passes
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        
        // Inner loop: compare and swap adjacent elements
        // After each pass, largest element "bubbles" to its position
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        // Optimization: if no swaps occur, array is sorted
        if (!swapped) break;
    }
}

// ============================================================================
// 2. SELECTION SORT
// ============================================================================
// Description: Divides array into sorted and unsorted parts. Repeatedly
//              selects minimum from unsorted part and adds to sorted part.
// Time: O(n²) worst/average/best - always makes n passes
// Space: O(1) - sorts in place
// Stable: NO (can be made stable with extra space)
// When to use: When memory writes are expensive, small datasets
// ============================================================================

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    
    // Outer loop: build sorted portion from left to right
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        
        // Inner loop: find minimum in remaining unsorted portion
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        
        // Swap minimum element with current position
        swap(arr[i], arr[minIdx]);
    }
}

// ============================================================================
// 3. INSERTION SORT
// ============================================================================
// Description: Builds sorted array one item at a time. For each element,
//              find its position in sorted portion and insert it.
// Time: O(n²) worst/average, O(n) best case (already sorted)
// Space: O(1) - sorts in place
// Stable: YES - preserves relative order
// When to use: Nearly sorted data, small datasets, online sorting
// Best for: Small arrays or as part of hybrid algorithms (Tim Sort)
// ============================================================================

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    
    // Start from second element (first element is trivially sorted)
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Shift elements greater than key one position right
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        // Insert key at its correct position
        arr[j + 1] = key;
    }
}

// ============================================================================
// 4. SHELL SORT (Generalization of Insertion Sort)
// ============================================================================
// Description: Insertion sort with gap sequence. First sorts elements
//              gap positions apart, then reduces gap. Fast for medium datasets.
// Time: O(n log n) to O(n²) depending on gap sequence
// Space: O(1) - sorts in place
// Stable: NO
// When to use: Medium-sized datasets, good practical performance
// ============================================================================

void shellSort(vector<int>& arr) {
    int n = arr.size();
    
    // Start with large gap, reduce by half each iteration
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Perform insertion sort on elements gap positions apart
        for (int i = gap; i < n; i++) {
            int key = arr[i];
            int j = i;
            
            // Compare with element gap positions back
            while (j >= gap && arr[j - gap] > key) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            
            arr[j] = key;
        }
    }
}

// ============================================================================
// DEMONSTRATION & PERFORMANCE COMPARISON
// ============================================================================

void printArray(const vector<int>& arr, const string& label) {
    cout << label << ": [";
    for (int i = 0; i < min(10, (int)arr.size()); i++) {
        cout << arr[i];
        if (i < min(9, (int)arr.size() - 1)) cout << ", ";
    }
    if (arr.size() > 10) cout << ", ...";
    cout << "]" << endl;
}

int main() {
    cout << "=== ELEMENTARY SORTING ALGORITHMS ===" << endl;
    
    vector<int> originalArray = {64, 34, 25, 12, 22, 11, 90, 88, 5, 77, 42, 18};
    
    // ========== BUBBLE SORT ==========
    cout << "\n1. BUBBLE SORT" << endl;
    cout << "Time: O(n²) | Space: O(1) | Stable: YES" << endl;
    vector<int> arr = originalArray;
    printArray(arr, "Before");
    bubbleSort(arr);
    printArray(arr, "After");
    
    // ========== SELECTION SORT ==========
    cout << "\n2. SELECTION SORT" << endl;
    cout << "Time: O(n²) | Space: O(1) | Stable: NO" << endl;
    arr = originalArray;
    printArray(arr, "Before");
    selectionSort(arr);
    printArray(arr, "After");
    
    // ========== INSERTION SORT ==========
    cout << "\n3. INSERTION SORT" << endl;
    cout << "Time: O(n²) avg, O(n) best | Space: O(1) | Stable: YES" << endl;
    arr = originalArray;
    printArray(arr, "Before");
    insertionSort(arr);
    printArray(arr, "After");
    
    // ========== SHELL SORT ==========
    cout << "\n4. SHELL SORT" << endl;
    cout << "Time: O(n log n) to O(n²) | Space: O(1) | Stable: NO" << endl;
    arr = originalArray;
    printArray(arr, "Before");
    shellSort(arr);
    printArray(arr, "After");
    
    // ========== PERFORMANCE COMPARISON ==========
    cout << "\n=== PERFORMANCE COMPARISON (1000 random elements) ===" << endl;
    
    int testSize = 1000;
    vector<int> testArray(testSize);
    
    // Generate random array
    srand(time(0));
    for (int i = 0; i < testSize; i++) {
        testArray[i] = rand() % 1000;
    }
    
    auto start = chrono::high_resolution_clock::now();
    
    arr = testArray;
    bubbleSort(arr);
    auto end = chrono::high_resolution_clock::now();
    cout << "Bubble Sort: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
    start = chrono::high_resolution_clock::now();
    arr = testArray;
    selectionSort(arr);
    end = chrono::high_resolution_clock::now();
    cout << "Selection Sort: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
    start = chrono::high_resolution_clock::now();
    arr = testArray;
    insertionSort(arr);
    end = chrono::high_resolution_clock::now();
    cout << "Insertion Sort: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
    start = chrono::high_resolution_clock::now();
    arr = testArray;
    shellSort(arr);
    end = chrono::high_resolution_clock::now();
    cout << "Shell Sort: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
    return 0;
}
