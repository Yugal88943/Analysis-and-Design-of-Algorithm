//Insertion in BST - Recursion
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int key) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = key;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node* insertRecursive(struct Node* root, int key) {
    if (root == NULL)
        return newNode(key);

    if (key < root->data)
        root->left = insertRecursive(root->left, key);
    else if (key > root->data)
        root->right = insertRecursive(root->right, key);

    return root;
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    struct Node* root = NULL;

    root = insertRecursive(root, 22);
    root = insertRecursive(root, 12);
    root = insertRecursive(root, 30);
    root = insertRecursive(root, 8);
    root = insertRecursive(root, 20);
    root = insertRecursive(root, 15);

    printf("Inorder Traversal: ");
    inorder(root);
    return 0;
}

