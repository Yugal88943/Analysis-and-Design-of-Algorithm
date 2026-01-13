#include <stdio.h>
#include <stdlib.h>

// Node definition
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

// Print linked list
void printList(struct Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Compare function for qsort
int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int k, n, i, j, total = 0;
    printf("Enter number of linked lists: ");
    scanf("%d", &k);

    int* arr = (int*)malloc(1000 * sizeof(int)); // large buffer

    // Read lists
    for (i = 0; i < k; i++) {
        printf("Enter number of nodes in list %d: ", i + 1);
        scanf("%d", &n);
        printf("Enter %d values: ", n);
        for (j = 0; j < n; j++) {
            scanf("%d", &arr[total]);
            total++;
        }
    }

    // Sort array
    qsort(arr, total, sizeof(int), cmp);

    // Build linked list
    struct Node* head = NULL, *tail = NULL;
    for (i = 0; i < total; i++) {
        struct Node* temp = newNode(arr[i]);
        if (!head) head = tail = temp;
        else {
            tail->next = temp;
            tail = temp;
        }
    }

    printf("Merged Sorted Linked List: ");
    printList(head);

    free(arr);
    return 0;
}
