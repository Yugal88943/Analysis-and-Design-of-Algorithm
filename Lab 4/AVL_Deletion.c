#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

// Utility function to get height of node
int height(struct Node* n) {
    return (n == NULL) ? 0 : n->height;
}

// Utility to get max of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;  // new node initially added at leaf
    return node;
}

// Right rotation
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    // Return new root
    return x;
}

// Left rotation
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    // Return new root
    return y;
}

// Get balance factor
int getBalance(struct Node* n) {
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

// Find node with minimum key (used in deletion)
struct Node* getMinValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Insert (used to build tree for demo)
struct Node* insert(struct Node* node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // No duplicates

    // Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Get balance
    int balance = getBalance(node);

    // Balancing cases
    if (balance > 1 && key < node->left->key)  // LL
        return rightRotate(node);

    if (balance < -1 && key > node->right->key) // RR
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) { // LR
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) { // RL
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Delete node from AVL Tree
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    // Step 1: Perform BST delete
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node found
        if (root->left == NULL || root->right == NULL) {
            struct Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp; // Copy contents
            }

            free(temp);
        } else {
            struct Node* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If tree had only one node
    if (root == NULL)
        return root;

    // Step 2: Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // Step 3: Get balance
    int balance = getBalance(root);

    // Step 4: Rebalance if needed
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);  // LL

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);  // LR
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);   // RR

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);   // RL
    }

    return root;
}

// Preorder traversal for output
void preOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Driver Code
int main() {
    struct Node* root = NULL;

    // Build tree
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    printf("Preorder before deletion:\n");
    preOrder(root);

    root = deleteNode(root, 10);

    printf("\nPreorder after deletion of 10:\n");
    preOrder(root);

    return 0;
}
