#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = NULL;

/* Insert at end */
void insert(int value) {
    Node* newNode = new Node;
    newNode->data = value;

    if (head == NULL) {
        head = newNode;
        newNode->next = head; // circular link
        return;
    }

    Node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->next = head;
}

//Function to 

/* Display list */
void display() {
    if (head == NULL) {
        cout << "List is empty\n";
        return;
    }

    Node* temp = head;
    do {
        cout << temp->data << " -> ";
        temp = temp->next;
    } while (temp != head);

    cout << "(back to head)\n";
}

int main() {
    insert(10);
    insert(20);
    insert(30);

    display();
    return 0;
}
