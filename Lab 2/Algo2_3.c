#include <stdio.h>
#include <stdlib.h>

// Linked list node
struct Node {
    int data;
    struct Node* next;
};

// Create new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Recursive reversal in groups
struct Node* reverseInGroupsRecursive(struct Node* head, int k) {
    struct Node* curr = head;
    struct Node* prev = NULL;
    struct Node* next = NULL;
    int count = 0;

    // Reverse first k nodes
    while (curr != NULL && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }

    // Recurse for remaining list
    if (next != NULL)
        head->next = reverseInGroupsRecursive(next, k);

    return prev;
}

// Print list with group separators
void printList(struct Node* head, int k) {
    int count = 0;
    while (head != NULL) {
        printf("%d ", head->data);
        count++;
        head = head->next;
        if (count % k == 0) printf("| "); // separator
    }
    printf("\n");
}

int main() {
    int n, k, val;
    struct Node* head = NULL;
    struct Node* tail = NULL;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter %d values: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        struct Node* node = newNode(val);
        if (head == NULL) head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
    }

    printf("Enter group size k: ");
    scanf("%d", &k);

    head = reverseInGroupsRecursive(head, k);

    printf("Reversed in Groups: ");
    printList(head, k);

    return 0;
}
