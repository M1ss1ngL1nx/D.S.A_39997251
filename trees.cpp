#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node dummy = {-1, &dummy, &dummy}; // sentinel node

Node* createNode(int value) {
    Node* n = new Node;
    n->data = value;
    n->left = &dummy;
    n->right = &dummy;
    return n;
}

void inorder(Node* root) {
    if (root == &dummy) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    Node* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);

    inorder(root);
} 
