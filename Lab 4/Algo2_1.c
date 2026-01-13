//Insertion in BST - Using Iteration
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

struct Node* insertIterative(struct Node* root, int key) {
    struct Node* node = newNode(key);

    if (root == NULL)
        return node;

    struct Node* parent = NULL;
    struct Node* current = root;

    while (current != NULL) {
        parent = current;
        if (key < current->data)
            current = current->left;
        else if (key > current->data)
            current = current->right;
        else
            return root;  // duplicate keys ignored
    }

    if (key < parent->data)
        parent->left = node;
    else
        parent->right = node;

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

    root = insertIterative(root, 22);
    root = insertIterative(root, 12);
    root = insertIterative(root, 30);
    // root = insertIterative(root, 8);
    // root = insertIterative(root, 20);
    // root = insertIterative(root, 15);

    printf("Inorder Traversal: ");
    inorder(root);
    return 0;
}
