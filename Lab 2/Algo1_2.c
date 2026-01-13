#include <stdio.h>
#include <stdlib.h>

// Node structure
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

// Insert at end
void insertEnd(struct Node** head, int data) {
    struct Node* temp = newNode(data);
    if (*head == NULL) {
        *head = temp;
        return;
    }
    struct Node* curr = *head;
    while (curr->next) curr = curr->next;
    curr->next = temp;
}

// Print linked list
void printList(struct Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Count nodes
int countNodes(struct Node* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// Convert to array
void listToArray(struct Node* head, int arr[]) {
    int i = 0;
    while (head) {
        arr[i++] = head->data;
        head = head->next;
    }
}

// Convert array to list
struct Node* arrayToList(int arr[], int n) {
    struct Node* head = NULL;
    for (int i = 0; i < n; i++) {
        insertEnd(&head, arr[i]);
    }
    return head;
}

// Bubble sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Rearrange pattern
struct Node* rearrange(int arr[], int n) {
    int temp[n], i = 0, j = n-1, k = 0;
    while (i <= j) {
        if (i == j) temp[k++] = arr[i++];
        else {
            temp[k++] = arr[i++];
            temp[k++] = arr[j--];
        }
    }
    return arrayToList(temp, n);
}

int main() {
    int k;
    printf("Enter number of linked lists: ");
    scanf("%d", &k);

    struct Node* merged = NULL;
    for (int i = 0; i < k; i++) {
        int n, val;
        printf("Enter number of nodes in list %d: ", i+1);
        scanf("%d", &n);
        printf("Enter %d values: ", n);
        for (int j = 0; j < n; j++) {
            scanf("%d", &val);
            insertEnd(&merged, val);
        }
    }

    int n = countNodes(merged);
    int arr[n];
    listToArray(merged, arr);

    bubbleSort(arr, n);
    printf("Sorted Linked List: ");
    struct Node* sorted = arrayToList(arr, n);
    printList(sorted);

    struct Node* rearr = rearrange(arr, n);
    printf("Rearranged Linked List: ");
    printList(rearr);

    return 0;
}
