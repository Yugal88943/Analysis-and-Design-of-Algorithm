#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node *createNode(int x)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to find the height of the tree
int getHeight(struct Node *root, int h)
{
    if (root == NULL)
        return h - 1;
    int leftHeight = getHeight(root->left, h + 1);
    int rightHeight = getHeight(root->right, h + 1);
    return (leftHeight > rightHeight) ? leftHeight : rightHeight;
}

// Queue structure for level order traversal
struct QueueNode
{
    struct Node *node;
    int level;
};

struct Queue
{
    struct QueueNode arr[100];
    int front, rear;
};

// Initialize queue
void initQueue(struct Queue *q)
{
    q->front = 0;
    q->rear = 0;
}

// Enqueue
void enqueue(struct Queue *q, struct Node *node, int level)
{
    q->arr[q->rear].node = node;
    q->arr[q->rear].level = level;
    q->rear++;
}

// Dequeue
struct QueueNode dequeue(struct Queue *q)
{
    return q->arr[q->front++];
}

// Check if queue is empty
int isEmpty(struct Queue *q)
{
    return q->front == q->rear;
}

// Function to print Level Order Traversal
void levelOrder(struct Node *root)
{
    if (root == NULL)
        return;

    struct Queue q;
    initQueue(&q);
    enqueue(&q, root, 0);

    int lastLevel = 0;

    // function to get height of the tree
    int height = getHeight(root, 0);

    // printing level order of the tree
    while (!isEmpty(&q))
    {
        struct QueueNode temp = dequeue(&q);
        struct Node *node = temp.node;
        int lvl = temp.level;

        if (lvl > lastLevel)
        {
            printf("\n");
            lastLevel = lvl;
        }

        // all levels are printed
        if (lvl > height)
            break;

        // Printing null nodes
        if (node->data != -1)
            printf("%d ", node->data);
        else
            printf("N ");

        // null node has no children
        if (node->data == -1)
            continue;

        if (node->left == NULL)
            enqueue(&q, createNode(-1), lvl + 1);
        else
            enqueue(&q, node->left, lvl + 1);

        if (node->right == NULL)
            enqueue(&q, createNode(-1), lvl + 1);
        else
            enqueue(&q, node->right, lvl + 1);
    }
}

// the inorder successor (smallest in right subtree)
struct Node *getSuccessor(struct Node *curr)
{
    curr = curr->right;
    while (curr != NULL && curr->left != NULL)
        curr = curr->left;
    return curr;
}

// Function to delete a node with value x from BST
struct Node *delNode(struct Node *root, int x)
{
    if (root == NULL)
        return root;

    if (root->data > x)
        root->left = delNode(root->left, x);
    else if (root->data < x)
        root->right = delNode(root->right, x);

    else
    {
        // Node with 0 or 1 child
        if (root->left == NULL)
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL)
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        // Node with 2 children
        struct Node *succ = getSuccessor(root);
        root->data = succ->data;
        root->right = delNode(root->right, succ->data);
    }
    return root;
}

int main()
{
    struct Node *root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->right->left = createNode(12);
    root->right->right = createNode(18);

    int x = 15;

    root = delNode(root, x);
    levelOrder(root);

    return 0;
}