#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
using namespace std;

// ============================================================================
// SEARCHING ALGORITHMS
// ============================================================================

// ============================================================================
// 1. LINEAR SEARCH (Sequential Search)
// ============================================================================
// Description: Scan array from beginning to end until element found.
//              Works on unsorted arrays.
// Time: O(n) - must check each element in worst case
// Space: O(1)
// When to use: Unsorted arrays, small datasets, LinkedLists
// Best case: O(1) - element at first position
// Worst case: O(n) - element at last position or not present
// ============================================================================

int linearSearch(const vector<int>& arr, int target) {
    // Check each element sequentially
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i;  // Element found
        }
    }
    return -1;  // Element not found
}

// ============================================================================
// 2. BINARY SEARCH
// ============================================================================
// Description: Divide and conquer on sorted array. Compare middle element
//              with target, eliminate half the search space each iteration.
// Time: O(log n) - reduces search space by half each time
// Space: O(1) iterative, O(log n) recursive (call stack)
// When to use: Sorted arrays, large datasets
// Requirements: Array MUST be sorted
// Best case: O(1) - element at middle
// Worst case: O(log n)
// ============================================================================

// Iterative version
int binarySearchIterative(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;  // Avoid overflow
        
        if (arr[mid] == target) {
            return mid;  // Element found
        } else if (arr[mid] < target) {
            // Target is in right half
            left = mid + 1;
        } else {
            // Target is in left half
            right = mid - 1;
        }
    }
    
    return -1;  // Element not found
}

// Recursive version
int binarySearchRecursive(const vector<int>& arr, int target, int left, int right) {
    if (left > right) {
        return -1;  // Base case: not found
    }
    
    int mid = left + (right - left) / 2;
    
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        // Recursively search right half
        return binarySearchRecursive(arr, target, mid + 1, right);
    } else {
        // Recursively search left half
        return binarySearchRecursive(arr, target, left, mid - 1);
    }
}

int binarySearch(const vector<int>& arr, int target) {
    return binarySearchIterative(arr, target);
}

// Find leftmost occurrence (first occurrence)
int binarySearchLeftmost(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;  // Continue searching left
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Find rightmost occurrence (last occurrence)
int binarySearchRightmost(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1;  // Continue searching right
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// ============================================================================
// 3. JUMP SEARCH
// ============================================================================
// Description: Like binary search but uses fixed-size jumps instead of
//              halving. Jump m steps, when target passed, linear search back.
// Time: O(√n) - optimal jump size is √n
// Space: O(1)
// When to use: When binary search not available, linked lists with jumping
// ============================================================================

int jumpSearch(const vector<int>& arr, int target) {
    int n = arr.size();
    int step = sqrt(n);  // Optimal jump size
    int prev = 0;
    
    // Jump to find range containing target
    while (arr[min(step, n) - 1] < target) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1;  // Element not in array
        }
    }
    
    // Linear search in the range [prev, min(step, n))
    while (arr[prev] < target) {
        prev++;
        if (prev == min(step, n)) {
            return -1;
        }
    }
    
    // Check if element is found
    if (arr[prev] == target) {
        return prev;
    }
    
    return -1;
}

// ============================================================================
// 4. EXPONENTIAL SEARCH
// ============================================================================
// Description: Find range by exponentially increasing power of 2,
//              then apply binary search in that range.
// Time: O(log n)
// Space: O(1)
// When to use: Unbounded arrays, when target likely near beginning
// ============================================================================

int exponentialSearch(const vector<int>& arr, int target) {
    int n = arr.size();
    
    // If first element is target
    if (arr[0] == target) {
        return 0;
    }
    
    // Find range by exponentially increasing powers
    int i = 1;
    while (i < n && arr[i] < target) {
        i *= 2;
    }
    
    // Binary search in range [i/2, min(i, n))
    int left = i / 2;
    int right = min(i, n - 1);
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// ============================================================================
// 5. TERNARY SEARCH
// ============================================================================
// Description: Similar to binary search but divides array into 3 parts.
// Time: O(log₃ n) - slightly better than log₂ n, but rarely faster in practice
// Space: O(1) iterative
// When to use: Educational purposes, rarely used in production
// ============================================================================

int ternarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        
        if (arr[mid1] == target) {
            return mid1;
        } else if (arr[mid2] == target) {
            return mid2;
        } else if (target < arr[mid1]) {
            // Target in first third
            right = mid1 - 1;
        } else if (target > arr[mid2]) {
            // Target in third third
            left = mid2 + 1;
        } else {
            // Target in middle third
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }
    
    return -1;
}

// ============================================================================
// 6. INTERPOLATION SEARCH
// ============================================================================
// Description: Estimate position based on value distribution.
//              Works like looking up in a phone book - jump to estimated position.
// Time: O(log log n) best case, O(n) worst case (non-uniform distribution)
// Space: O(1)
// When to use: Uniformly distributed arrays, dictionary-like searches
// ============================================================================

int interpolationSearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right && target >= arr[left] && target <= arr[right]) {
        // Estimate position based on value distribution
        int pos = left + (double)(right - left) / (arr[right] - arr[left]) * 
                          (target - arr[left]);
        
        if (arr[pos] == target) {
            return pos;
        } else if (arr[pos] < target) {
            left = pos + 1;
        } else {
            right = pos - 1;
        }
    }
    
    return -1;
}

// ============================================================================
// DEMONSTRATION & PERFORMANCE COMPARISON
// ============================================================================

int main() {
    cout << "=== SEARCHING ALGORITHMS ===" << endl;
    
    // Test array (MUST BE SORTED for binary search variants)
    vector<int> sortedArray = {5, 11, 12, 18, 22, 25, 34, 42, 64, 77, 88, 90};
    vector<int> unsortedArray = {64, 34, 25, 12, 22, 11, 90, 88, 5, 77, 42, 18};
    
    int target = 42;
    
    cout << "\n--- Searching for: " << target << " ---\n" << endl;
    
    // ========== LINEAR SEARCH ==========
    cout << "1. LINEAR SEARCH" << endl;
    cout << "Time: O(n) | Works on: Unsorted arrays" << endl;
    int result = linearSearch(unsortedArray, target);
    cout << "Result: " << (result != -1 ? "Found at index " + to_string(result) : "Not found") << endl;
    
    // ========== BINARY SEARCH ==========
    cout << "\n2. BINARY SEARCH" << endl;
    cout << "Time: O(log n) | Works on: Sorted arrays ONLY" << endl;
    result = binarySearch(sortedArray, target);
    cout << "Result: " << (result != -1 ? "Found at index " + to_string(result) : "Not found") << endl;
    
    // ========== LEFTMOST/RIGHTMOST BINARY SEARCH ==========
    cout << "\n2b. BINARY SEARCH - Leftmost & Rightmost" << endl;
    vector<int> arrayWithDuplicates = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4};
    cout << "Array with duplicates: [1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4]" << endl;
    cout << "Leftmost 3: " << binarySearchLeftmost(arrayWithDuplicates, 3) << endl;
    cout << "Rightmost 3: " << binarySearchRightmost(arrayWithDuplicates, 3) << endl;
    
    // ========== JUMP SEARCH ==========
    cout << "\n3. JUMP SEARCH" << endl;
    cout << "Time: O(√n) | Works on: Sorted arrays" << endl;
    result = jumpSearch(sortedArray, target);
    cout << "Result: " << (result != -1 ? "Found at index " + to_string(result) : "Not found") << endl;
    
    // ========== EXPONENTIAL SEARCH ==========
    cout << "\n4. EXPONENTIAL SEARCH" << endl;
    cout << "Time: O(log n) | Works on: Sorted arrays" << endl;
    result = exponentialSearch(sortedArray, target);
    cout << "Result: " << (result != -1 ? "Found at index " + to_string(result) : "Not found") << endl;
    
    // ========== TERNARY SEARCH ==========
    cout << "\n5. TERNARY SEARCH" << endl;
    cout << "Time: O(log₃ n) | Works on: Sorted arrays" << endl;
    result = ternarySearch(sortedArray, target);
    cout << "Result: " << (result != -1 ? "Found at index " + to_string(result) : "Not found") << endl;
    
    // ========== INTERPOLATION SEARCH ==========
    cout << "\n6. INTERPOLATION SEARCH" << endl;
    cout << "Time: O(log log n) avg, O(n) worst | Works on: Sorted uniformly distributed arrays" << endl;
    result = interpolationSearch(sortedArray, target);
    cout << "Result: " << (result != -1 ? "Found at index " + to_string(result) : "Not found") << endl;
    
    // ========== NOT FOUND CASE ==========
    cout << "\n--- Searching for: 100 (Not in array) ---\n" << endl;
    target = 100;
    
    cout << "Linear Search: " << (linearSearch(unsortedArray, target) != -1 ? "Found" : "Not Found") << endl;
    cout << "Binary Search: " << (binarySearch(sortedArray, target) != -1 ? "Found" : "Not Found") << endl;
    cout << "Jump Search: " << (jumpSearch(sortedArray, target) != -1 ? "Found" : "Not Found") << endl;
    
    // ========== PERFORMANCE COMPARISON ==========
    cout << "\n\n=== PERFORMANCE COMPARISON (100,000 elements) ===" << endl;
    
    int testSize = 100000;
    vector<int> largeArray(testSize);
    
    for (int i = 0; i < testSize; i++) {
        largeArray[i] = i;
    }
    
    int searchTarget = 75000;
    
    // Linear Search
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++) {
        linearSearch(largeArray, searchTarget);
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Linear Search (100 iterations): " 
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
    // Binary Search
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; i++) {
        binarySearch(largeArray, searchTarget);
    }
    end = chrono::high_resolution_clock::now();
    cout << "Binary Search (1,000,000 iterations): " 
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
    // Jump Search
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        jumpSearch(largeArray, searchTarget);
    }
    end = chrono::high_resolution_clock::now();
    cout << "Jump Search (100,000 iterations): " 
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
    // Exponential Search
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        exponentialSearch(largeArray, searchTarget);
    }
    end = chrono::high_resolution_clock::now();
    cout << "Exponential Search (100,000 iterations): " 
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
    // Ternary Search
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        ternarySearch(largeArray, searchTarget);
    }
    end = chrono::high_resolution_clock::now();
    cout << "Ternary Search (100,000 iterations): " 
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
    // Interpolation Search
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; i++) {
        interpolationSearch(largeArray, searchTarget);
    }
    end = chrono::high_resolution_clock::now();
    cout << "Interpolation Search (1,000,000 iterations): " 
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
    return 0;
}
