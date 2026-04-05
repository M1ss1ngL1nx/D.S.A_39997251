#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// ============================================================================
// ABSTRACT DATA TYPE: BINARY SEARCH TREE (BST)
// ============================================================================
// A Binary Search Tree is a binary tree where:
//   - Left child < Parent < Right child
// This property enables efficient searching, insertion, and deletion.
// Provides fast lookups when balanced, but can degrade to O(n) if skewed.
// Time Complexity (Average):
//   - Search: O(log n)
//   - Insert: O(log n)
//   - Delete: O(log n)
// Time Complexity (Worst - Skewed Tree):
//   - Search: O(n)
//   - Insert: O(n)
//   - Delete: O(n)
// ============================================================================

template <typename T>
class TreeNode {
public:
    T data;               // Data stored in the node
    TreeNode* left;       // Pointer to left child
    TreeNode* right;      // Pointer to right child
    
    TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;  // Root node of the tree

    // Helper function: Insert a value recursively
    TreeNode<T>* insertHelper(TreeNode<T>* node, T value) {
        if (node == nullptr) {
            return new TreeNode<T>(value);
        }
        
        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value);
        }
        // Duplicate values are typically ignored
        
        return node;
    }

    // Helper function: Search for a value recursively
    TreeNode<T>* searchHelper(TreeNode<T>* node, T value) {
        if (node == nullptr) {
            return nullptr;
        }
        
        if (value == node->data) {
            return node;
        } else if (value < node->data) {
            return searchHelper(node->left, value);
        } else {
            return searchHelper(node->right, value);
        }
    }

    // Helper function: Find the minimum value node
    TreeNode<T>* findMin(TreeNode<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }
        // Leftmost node has the minimum value
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Helper function: Delete a value recursively
    TreeNode<T>* deleteHelper(TreeNode<T>* node, T value) {
        if (node == nullptr) {
            return nullptr;
        }
        
        if (value < node->data) {
            node->left = deleteHelper(node->left, value);
        } else if (value > node->data) {
            node->right = deleteHelper(node->right, value);
        } else {
            // Node to be deleted found
            
            // Case 1: No children (leaf node)
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            
            // Case 2: One child
            if (node->left == nullptr) {
                TreeNode<T>* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr) {
                TreeNode<T>* temp = node->left;
                delete node;
                return temp;
            }
            
            // Case 3: Two children
            // Find the minimum value in the right subtree (in-order successor)
            TreeNode<T>* minNode = findMin(node->right);
            node->data = minNode->data;
            node->right = deleteHelper(node->right, minNode->data);
        }
        
        return node;
    }

    // In-order traversal: Left -> Node -> Right (sorted order)
    void inorderHelper(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }

    // Pre-order traversal: Node -> Left -> Right
    void preorderHelper(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        cout << node->data << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }

    // Post-order traversal: Left -> Right -> Node
    void postorderHelper(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << node->data << " ";
    }

    // Level-order traversal (Breadth-First)
    void levelorderHelper(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        
        queue<TreeNode<T>*> q;
        q.push(node);
        
        while (!q.empty()) {
            TreeNode<T>* temp = q.front();
            q.pop();
            cout << temp->data << " ";
            
            if (temp->left != nullptr) {
                q.push(temp->left);
            }
            if (temp->right != nullptr) {
                q.push(temp->right);
            }
        }
    }

    // Calculate height of the tree
    int heightHelper(TreeNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + max(heightHelper(node->left), heightHelper(node->right));
    }

    // Free all nodes
    void deleteTree(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    // Constructor
    BinarySearchTree() : root(nullptr) {}

    // Destructor
    ~BinarySearchTree() {
        deleteTree(root);
    }

    // Insert a value
    void insert(T value) {
        root = insertHelper(root, value);
    }

    // Search for a value
    bool search(T value) {
        return searchHelper(root, value) != nullptr;
    }

    // Delete a value
    void deleteValue(T value) {
        root = deleteHelper(root, value);
    }

    // In-order traversal (prints in sorted order)
    void inorder() {
        cout << "In-order: ";
        inorderHelper(root);
        cout << endl;
    }

    // Pre-order traversal
    void preorder() {
        cout << "Pre-order: ";
        preorderHelper(root);
        cout << endl;
    }

    // Post-order traversal
    void postorder() {
        cout << "Post-order: ";
        postorderHelper(root);
        cout << endl;
    }

    // Level-order traversal
    void levelorder() {
        cout << "Level-order: ";
        levelorderHelper(root);
        cout << endl;
    }

    // Get tree height
    int height() {
        return heightHelper(root);
    }

    // Check if tree is empty
    bool isEmpty() {
        return root == nullptr;
    }

    // Find minimum value
    T findMinValue() {
        TreeNode<T>* minNode = findMin(root);
        if (minNode == nullptr) {
            throw runtime_error("Tree is empty");
        }
        return minNode->data;
    }
};

// ============================================================================
// DEMONSTRATION
// ============================================================================
int main() {
    cout << "=== BINARY SEARCH TREE ADT ===" << endl;
    
    BinarySearchTree<int> bst;
    
    // Insert elements
    cout << "\nInserting: 50, 30, 70, 20, 40, 60, 80" << endl;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    
    // Tree traversals
    bst.inorder();    // Should print: 20 30 40 50 60 70 80
    bst.preorder();
    bst.postorder();
    bst.levelorder();
    
    // Tree height
    cout << "\nTree height: " << bst.height() << endl;
    
    // Search
    cout << "\nSearching for 40: " << (bst.search(40) ? "Found" : "Not Found") << endl;
    cout << "Searching for 100: " << (bst.search(100) ? "Found" : "Not Found") << endl;
    
    // Minimum value
    cout << "\nMinimum value: " << bst.findMinValue() << endl;
    
    // Delete operations
    cout << "\n--- Delete Operations ---" << endl;
    cout << "Deleting leaf node (20):" << endl;
    bst.deleteValue(20);
    bst.inorder();
    
    cout << "\nDeleting node with one child (30):" << endl;
    bst.deleteValue(30);
    bst.inorder();
    
    cout << "\nDeleting node with two children (50):" << endl;
    bst.deleteValue(50);
    bst.inorder();
    
    return 0;
}
