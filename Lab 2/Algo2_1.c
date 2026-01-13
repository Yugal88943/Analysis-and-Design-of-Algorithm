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

// Merge two sorted lists
struct Node* mergeTwo(struct Node* a, struct Node* b) {
    struct Node dummy; 
    struct Node* tail = &dummy;
    dummy.next = NULL;

    while (a && b) {
        if (a->data <= b->data) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = (a ? a : b);
    return dummy.next;
}

// Split linked list into two halves
void splitList(struct Node* source, struct Node** front, struct Node** back) {
    if (!source || !source->next) {
        *front = source;
        *back = NULL;
        return;
    }
    struct Node* slow = source;
    struct Node* fast = source->next;
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

// Merge sort for linked list
struct Node* mergeSortList(struct Node* head) {
    if (!head || !head->next) return head;
    struct Node* a; 
    struct Node* b;
    splitList(head, &a, &b);
    a = mergeSortList(a);
    b = mergeSortList(b);
    return mergeTwo(a, b);
}

// Merge K lists using divide and conquer
struct Node* mergeKLists(struct Node** lists, int k) {
    if (k == 0) return NULL;
    for (int interval = 1; interval < k; interval *= 2) {
        for (int i = 0; i + interval < k; i += interval * 2) {
            lists[i] = mergeTwo(lists[i], lists[i + interval]);
        }
    }
    return lists[0];
}

int main() {
    int k;
    printf("Enter number of linked lists: ");
    scanf("%d", &k);

    struct Node* lists[k];

    for (int i = 0; i < k; i++) {
        int n;
        printf("Enter number of nodes in list %d: ", i + 1);
        scanf("%d", &n);

        struct Node* head = NULL, *tail = NULL;
        printf("Enter %d values: ", n);
        for (int j = 0; j < n; j++) {
            int val;
            scanf("%d", &val);
            struct Node* temp = newNode(val);
            if (!head) head = tail = temp;
            else {
                tail->next = temp;
                tail = temp;
            }
        }
        // Sort each list first
        lists[i] = mergeSortList(head);
    }

    // Merge all lists
    struct Node* merged = mergeKLists(lists, k);

    printf("Merged Sorted Linked List: ");
    printList(merged);
    return 0;
}
    