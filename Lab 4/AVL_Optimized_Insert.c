#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

// Utility to get max of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to get height
int height(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to create a new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // New node is initially leaf
    return node;
}

// Right rotation
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights only for affected nodes
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // New root
}

// Left rotation
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights only for affected nodes
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // New root
}

// Get balance factor
int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Optimized AVL insertion
struct Node* insertAVL(struct Node* root, int key) {
    // Step 1: Normal BST insertion
    if (root == NULL)
        return newNode(key);

    if (key < root->key)
        root->left = insertAVL(root->left, key);
    else if (key > root->key)
        root->right = insertAVL(root->right, key);
    else
        return root; // duplicates not allowed

    // Step 2: Update height of this ancestor
    root->height = 1 + max(height(root->left), height(root->right));

    // Step 3: Check balance factor
    int balance = getBalance(root);

    // Step 4: If unbalanced, fix it
    // LL Case
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // RR Case
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // LR Case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Return the (unchanged) node pointer
    return root;
}

// Inorder traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    struct Node* root = NULL;

    root = insertAVL(root, 50);
    root = insertAVL(root, 20);
    root = insertAVL(root, 70);
    root = insertAVL(root, 10);
    root = insertAVL(root, 30);
    root = insertAVL(root, 60);
    root = insertAVL(root, 80);

    printf("Inorder Traversal of Optimized AVL Tree:\n");
    inorder(root);

    return 0;
}

