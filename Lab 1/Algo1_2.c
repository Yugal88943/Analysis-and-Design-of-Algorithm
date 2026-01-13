// Check if Linked List is Circular or Not
// Algorithm 1 Beginner (visited flag + nodes array; user-input based)

/* Beginner method:
   - Build list from user input
   - User specifies a position (1..n) that last->next points to, or 0 for NULL
   - Use a 'visited' field in each node to detect cycle
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    int visited;   // 0 = not visited, 1 = visited
} Node;

Node* createNode(int val) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = val;
    p->next = NULL;
    p->visited = 0;
    return p;
}

int main() {
    int n, i, val, pos;
    printf("Enter number of nodes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 0;
    }

    Node** nodes = (Node**)malloc(sizeof(Node*) * n); // store node pointers
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
        // free memory
        for (i = 0; i < n; ++i) free(nodes[i]);
        free(nodes);
        return 0;
    }
    if (pos == 0) last->next = NULL;
    else last->next = nodes[pos - 1];

    // Detection using visited flag
    Node* cur = head;
    int isCycle = 0;
    while (cur != NULL && cur->visited == 0) {
        cur->visited = 1;
        cur = cur->next;
    }
    if (cur != NULL && cur->visited == 1) isCycle = 1;

    if (isCycle) printf("Cycle detected.\n");
    else printf("No cycle.\n");

    // reset visited flags (use nodes array)
    for (i = 0; i < n; ++i) nodes[i]->visited = 0;

    // free memory safely via nodes array
    for (i = 0; i < n; ++i) free(nodes[i]);
    free(nodes);

    return 0;
}
