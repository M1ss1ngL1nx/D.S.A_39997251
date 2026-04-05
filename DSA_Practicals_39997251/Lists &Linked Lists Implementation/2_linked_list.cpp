#include <iostream>
#include <stdexcept>
using namespace std;

// ============================================================================
// ABSTRACT DATA TYPE: SINGLY LINKED LIST
// ============================================================================
// A Linked List is a linear data structure where elements (nodes) are connected
// via pointers. Unlike arrays, it doesn't require contiguous memory.
// Time Complexity:
//   - Access: O(n)
//   - Insert at beginning: O(1)
//   - Insert at position: O(n)
//   - Delete: O(n)
//   - Search: O(n)
// Space: O(n)
// ============================================================================

template <typename T>
class Node {
public:
    T data;           // Value stored in the node
    Node* next;       // Pointer to the next node
    
    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;    // Pointer to the first node (head) of the list

public:
    // Constructor: Initialize empty list
    LinkedList() : head(nullptr) {}

    // Destructor: Free all allocated nodes
    ~LinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Insert element at the beginning
    void insertAtBeginning(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
    }

    // Insert element at the end
    void insertAtEnd(T value) {
        Node<T>* newNode = new Node<T>(value);
        
        // If list is empty, new node becomes head
        if (head == nullptr) {
            head = newNode;
            return;
        }
        
        // Traverse to find the last node
        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        
        // Insert new node at the end
        current->next = newNode;
    }

    // Insert element at specific position (0-indexed)
    void insertAtPosition(int position, T value) {
        if (position < 0) {
            throw out_of_range("Position cannot be negative");
        }
        
        if (position == 0) {
            insertAtBeginning(value);
            return;
        }
        
        Node<T>* current = head;
        int count = 0;
        
        // Traverse to find the node before the insertion position
        while (current != nullptr && count < position - 1) {
            current = current->next;
            count++;
        }
        
        if (current == nullptr) {
            throw out_of_range("Position out of bounds");
        }
        
        Node<T>* newNode = new Node<T>(value);
        newNode->next = current->next;
        current->next = newNode;
    }

    // Delete element at specific position
    void deleteAt(int position) {
        if (head == nullptr || position < 0) {
            throw out_of_range("Invalid position");
        }
        
        // Delete from beginning
        if (position == 0) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        
        // Find node before the one to delete
        Node<T>* current = head;
        int count = 0;
        
        while (current != nullptr && count < position - 1) {
            current = current->next;
            count++;
        }
        
        if (current == nullptr || current->next == nullptr) {
            throw out_of_range("Position out of bounds");
        }
        
        // Delete the node
        Node<T>* temp = current->next;
        current->next = temp->next;
        delete temp;
    }

    // Search for a value in the list
    int search(T value) {
        Node<T>* current = head;
        int position = 0;
        
        while (current != nullptr) {
            if (current->data == value) {
                return position;
            }
            current = current->next;
            position++;
        }
        
        return -1;  // Not found
    }

    // Get element at specific position
    T get(int position) {
        if (position < 0) {
            throw out_of_range("Position cannot be negative");
        }
        
        Node<T>* current = head;
        int count = 0;
        
        while (current != nullptr && count < position) {
            current = current->next;
            count++;
        }
        
        if (current == nullptr) {
            throw out_of_range("Position out of bounds");
        }
        
        return current->data;
    }

    // Check if list is empty
    bool isEmpty() {
        return head == nullptr;
    }

    // Print all elements
    void print() {
        cout << "[";
        Node<T>* current = head;
        
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " -> ";
            }
            current = current->next;
        }
        
        cout << "]" << endl;
    }

    // Get the size of the list
    int getSize() {
        int count = 0;
        Node<T>* current = head;
        
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        
        return count;
    }
};

// ============================================================================
// DEMONSTRATION
// ============================================================================
int main() {
    cout << "=== SINGLY LINKED LIST ADT ===" << endl;
    
    LinkedList<int> list;
    
    // Insert elements
    cout << "\nInserting 10, 20, 30 at the end:" << endl;
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.print();
    
    // Insert at beginning
    cout << "\nInserting 5 at the beginning:" << endl;
    list.insertAtBeginning(5);
    list.print();
    
    // Insert at position
    cout << "\nInserting 15 at position 2:" << endl;
    list.insertAtPosition(2, 15);
    list.print();
    
    // Search
    cout << "\nSearching for 20: Position " << list.search(20) << endl;
    cout << "Searching for 40: Position " << list.search(40) << endl;
    
    // Delete
    cout << "\nDeleting element at position 1:" << endl;
    list.deleteAt(1);
    list.print();
    
    // Get element
    cout << "\nElement at position 0: " << list.get(0) << endl;
    
    // Size
    cout << "\nSize of list: " << list.getSize() << endl;
    
    return 0;
}
