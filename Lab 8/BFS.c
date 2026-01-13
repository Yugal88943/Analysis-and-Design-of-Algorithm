#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* createNode(int v) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->vertex = v;
    n->next = NULL;
    return n;
}

void addEdge(Node* adj[], int u, int v) {
    Node* n = createNode(v);
    n->next = adj[u];
    adj[u] = n;
}

void BFS(Node* adj[], int n, int start) {
    bool visited[n];
    for (int i = 0; i < n; i++) visited[i] = false;

    int queue[n];
    int front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    while (front != rear) {
        int u = queue[front++];

        printf("%d ", u);

        Node* temp = adj[u];
        while (temp != NULL) {
            int v = temp->vertex;
            if (!visited[v]) {
                visited[v] = true;
                queue[rear++] = v;
            }
            temp = temp->next;
        }
    }
}

int main() {
    int n = 5;  // number of nodes
    Node* adj[5] = {NULL};

    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 2, 4);

    BFS(adj, n, 0); 

    return 0;
}
