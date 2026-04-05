#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <chrono>
using namespace std;

// ============================================================================
// SORTING ALGORITHMS - ADVANCED SORTS (Divide & Conquer)
// ============================================================================

// ============================================================================
// 1. MERGE SORT
// ============================================================================
// Description: Divide-and-conquer algorithm. Divides array in half,
//              recursively sorts both halves, then merges them together.
// Time: O(n log n) best/average/worst - very consistent
// Space: O(n) - requires temporary array for merging
// Stable: YES - preserves relative order of equal elements
// When to use: When consistent O(n log n) is needed, external sorting
// Advantages: Guaranteed performance, stable, works well with linked lists
// Disadvantages: Requires O(n) extra space
// ============================================================================

void merge(vector<int>& arr, int left, int mid, int right) {
    // Create temporary arrays for left and right subarrays
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);
    
    int i = 0;      // Index for left subarray
    int j = 0;      // Index for right subarray
    int k = left;   // Index for main array
    
    // Merge the two subarrays, comparing elements
    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    
    // Copy remaining elements from left subarray
    while (i < leftArr.size()) {
        arr[k++] = leftArr[i++];
    }
    
    // Copy remaining elements from right subarray
    while (j < rightArr.size()) {
        arr[k++] = rightArr[j++];
    }
}

void mergeSortHelper(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // Avoid overflow
        
        // Recursively sort left half
        mergeSortHelper(arr, left, mid);
        
        // Recursively sort right half
        mergeSortHelper(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

void mergeSort(vector<int>& arr) {
    if (!arr.empty()) {
        mergeSortHelper(arr, 0, arr.size() - 1);
    }
}

// ============================================================================
// 2. QUICK SORT
// ============================================================================
// Description: Divide-and-conquer using partitioning. Select pivot,
//              partition around it, recursively sort both partitions.
// Time: O(n log n) average, O(n²) worst case (bad pivot selection)
// Space: O(log n) average - recursive call stack
// Stable: NO (basic version; stable variants exist)
// When to use: General-purpose sorting, in-place sorting preferred
// Advantages: Very fast in practice, minimal extra space, good cache locality
// Disadvantages: Worst case O(n²), unstable, complex partition logic
// Note: Random pivot selection greatly improves average case
// ============================================================================

int partition(vector<int>& arr, int low, int high) {
    // Choose rightmost element as pivot
    int pivot = arr[high];
    
    // i points to position where elements smaller than pivot should go
    int i = low - 1;
    
    // Partition: move smaller elements to left, larger to right
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    // Place pivot in its final sorted position
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Partition and get pivot index
        int pi = partition(arr, low, high);
        
        // Recursively sort elements before and after partition
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(vector<int>& arr) {
    if (!arr.empty()) {
        quickSortHelper(arr, 0, arr.size() - 1);
    }
}

// Randomized Quick Sort (better average case)
int randomPartition(vector<int>& arr, int low, int high) {
    // Choose random pivot to avoid O(n²) on sorted data
    int randomIdx = low + rand() % (high - low + 1);
    swap(arr[randomIdx], arr[high]);
    return partition(arr, low, high);
}

void quickSortRandomHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = randomPartition(arr, low, high);
        quickSortRandomHelper(arr, low, pi - 1);
        quickSortRandomHelper(arr, pi + 1, high);
    }
}

void quickSortRandom(vector<int>& arr) {
    if (!arr.empty()) {
        quickSortRandomHelper(arr, 0, arr.size() - 1);
    }
}

// ============================================================================
// 3. HEAP SORT
// ============================================================================
// Description: Uses max heap to sort. Build max heap, extract max
//              repeatedly and place at end. Essentially selection sort
//              with efficient heap data structure.
// Time: O(n log n) best/average/worst - very consistent
// Space: O(1) - sorts in place (if not using extra heap)
// Stable: NO - heap structure breaks stability
// When to use: When O(n log n) worst-case and O(1) space needed
// Advantages: O(n log n) guaranteed, in-place, good for memory-constrained systems
// Disadvantages: Slower in practice than Quick Sort, unstable
// ============================================================================

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;      // Left child
    int right = 2 * i + 2;     // Right child
    
    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    // If right child is larger than current largest
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    // If largest is not root, swap and recursively heapify
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Build max heap from array
    // Start from last non-leaf node: n/2 - 1
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root (largest) to end
        swap(arr[0], arr[i]);
        
        // Heapify reduced heap
        heapify(arr, i, 0);
    }
}

// ============================================================================
// 4. COUNTING SORT (Non-Comparison Sort)
// ============================================================================
// Description: Count occurrences of each value, then reconstruct result.
//              Works only for integers in known range.
// Time: O(n + k) where k is range of input
// Space: O(k) - counting array
// Stable: YES (if implemented preserving order)
// When to use: Small range of integers, need stable sort
// Advantages: Linear time, stable, simple
// Disadvantages: Only for integers, high space if large range, inefficient for sparse ranges
// ============================================================================

void countingSort(vector<int>& arr) {
    if (arr.empty()) return;
    
    // Find min and max to determine range
    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;
    
    // Create count array for each value in range
    vector<int> count(range, 0);
    
    // Count occurrences
    for (int num : arr) {
        count[num - minVal]++;
    }
    
    // Modify count array: count[i] now contains positions
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    
    // Build result array from back to maintain stability
    vector<int> result(arr.size());
    for (int i = arr.size() - 1; i >= 0; i--) {
        int index = count[arr[i] - minVal] - 1;
        result[index] = arr[i];
        count[arr[i] - minVal]--;
    }
    
    // Copy result back to original array
    arr = result;
}

// ============================================================================
// 5. RADIX SORT (Non-Comparison Sort)
// ============================================================================
// Description: Sort by processing individual digits. Uses counting sort
//              as subroutine for each digit position.
// Time: O(nk) where k is number of digits
// Space: O(n + 10) - output array and digit buckets
// Stable: YES (if digit sort is stable)
// When to use: Fixed-width integers (phone numbers, credit cards)
// Advantages: Linear time for fixed-width data, stable, no comparisons
// Disadvantages: Only for fixed-width data, more complex code
// ============================================================================

void countingSortForRadix(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);  // Count array for digits 0-9
    
    // Count occurrences of each digit at this position
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }
    
    // Modify count array to contain actual positions
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    // Build output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    // Copy to original array
    arr = output;
}

void radixSort(vector<int>& arr) {
    if (arr.empty()) return;
    
    // Find maximum to determine number of digits
    int maxVal = *max_element(arr.begin(), arr.end());
    
    // Sort by each digit position: ones, tens, hundreds, etc.
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortForRadix(arr, exp);
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
    cout << "=== ADVANCED SORTING ALGORITHMS ===" << endl;
    
    vector<int> originalArray = {64, 34, 25, 12, 22, 11, 90, 88, 5, 77, 42, 18};
    
    // ========== MERGE SORT ==========
    cout << "\n1. MERGE SORT" << endl;
    cout << "Time: O(n log n) | Space: O(n) | Stable: YES" << endl;
    vector<int> arr = originalArray;
    printArray(arr, "Before");
    mergeSort(arr);
    printArray(arr, "After");
    
    // ========== QUICK SORT ==========
    cout << "\n2. QUICK SORT" << endl;
    cout << "Time: O(n log n) avg, O(n²) worst | Space: O(log n) | Stable: NO" << endl;
    arr = originalArray;
    printArray(arr, "Before");
    quickSort(arr);
    printArray(arr, "After");
    
    // ========== QUICK SORT RANDOMIZED ==========
    cout << "\n2b. QUICK SORT (Randomized Pivot)" << endl;
    cout << "Better average case with random pivot selection" << endl;
    arr = originalArray;
    quickSortRandom(arr);
    cout << "Sorted: YES (randomized pivot)" << endl;
    
    // ========== HEAP SORT ==========
    cout << "\n3. HEAP SORT" << endl;
    cout << "Time: O(n log n) | Space: O(1) | Stable: NO" << endl;
    arr = originalArray;
    printArray(arr, "Before");
    heapSort(arr);
    printArray(arr, "After");
    
    // ========== COUNTING SORT ==========
    cout << "\n4. COUNTING SORT" << endl;
    cout << "Time: O(n + k) | Space: O(k) | Stable: YES" << endl;
    arr = originalArray;
    printArray(arr, "Before");
    countingSort(arr);
    printArray(arr, "After");
    
    // ========== RADIX SORT ==========
    cout << "\n5. RADIX SORT" << endl;
    cout << "Time: O(nk) | Space: O(n+10) | Stable: YES" << endl;
    arr = originalArray;
    printArray(arr, "Before");
    radixSort(arr);
    printArray(arr, "After");
    
    // ========== PERFORMANCE COMPARISON ==========
    cout << "\n=== PERFORMANCE COMPARISON (10000 random elements) ===" << endl;
    
    int testSize = 10000;
    vector<int> testArray(testSize);
    
    srand(time(0));
    for (int i = 0; i < testSize; i++) {
        testArray[i] = rand() % 10000;
    }
    
    // Merge Sort
    auto start = chrono::high_resolution_clock::now();
    arr = testArray;
    mergeSort(arr);
    auto end = chrono::high_resolution_clock::now();
    cout << "Merge Sort: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
    // Quick Sort
    start = chrono::high_resolution_clock::now();
    arr = testArray;
    quickSort(arr);
    end = chrono::high_resolution_clock::now();
    cout << "Quick Sort: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
    // Heap Sort
    start = chrono::high_resolution_clock::now();
    arr = testArray;
    heapSort(arr);
    end = chrono::high_resolution_clock::now();
    cout << "Heap Sort: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
    // Counting Sort
    start = chrono::high_resolution_clock::now();
    arr = testArray;
    countingSort(arr);
    end = chrono::high_resolution_clock::now();
    cout << "Counting Sort: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
    // Radix Sort
    start = chrono::high_resolution_clock::now();
    arr = testArray;
    radixSort(arr);
    end = chrono::high_resolution_clock::now();
    cout << "Radix Sort: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
    return 0;
}
