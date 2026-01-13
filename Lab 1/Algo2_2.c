/* Floyd's cycle detection
   - Builds list from user input same as above
   - Uses two pointers to detect cycle
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int val) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = val;
    p->next = NULL;
    return p;
}

int hasCycleFloyd(Node* head) {
    if (head == NULL) return 0;
    Node* slow = head;
    Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return 1; // cycle found
    }
    return 0; // no cycle
}

int main() {
    int n, i, val, pos;
    printf("Enter number of nodes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 0;
    }

    Node** nodes = (Node**)malloc(sizeof(Node*) * n);
    Node *head = NULL, *last = NULL;

    for (i = 0; i < n; ++i) {
        printf("Enter data for node %d: ", i+1);
        scanf("%d", &val);
        nodes[i] = createNode(val);
        if (head == NULL) {
            head = last = nodes[i];
        } else {
            last->next = nodes[i];
            last = nodes[i];
        }
    }

    printf("Enter position (1..%d) that last node should point to (0 for NULL): ", n);
    scanf("%d", &pos);
    if (pos < 0 || pos > n) {
        printf("Invalid position. Exiting.\n");
        for (i = 0; i < n; ++i) free(nodes[i]);
        free(nodes);
        return 0;
    }
    if (pos == 0) last->next = NULL;
    else last->next = nodes[pos - 1];

    if (hasCycleFloyd(head)) printf("Cycle detected.\n");
    else printf("No cycle.\n");

    // free nodes safely via array (avoid double-free)
    for (i = 0; i < n; ++i) free(nodes[i]);
    free(nodes);

    return 0;
}
