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

bool visited[100];

void DFS_Visit(Node* adj[], int u) {
    visited[u] = true;
    printf("%d ", u);

    Node* temp = adj[u];
    while (temp != NULL) {
        int v = temp->vertex;
        if (!visited[v])
            DFS_Visit(adj, v);
        temp = temp->next;
    }
}

void DFS(Node* adj[], int n, int start) {
    for (int i = 0; i < n; i++)
        visited[i] = false;

    DFS_Visit(adj, start);
}

int main() {
    int n = 5;
    Node* adj[5] = {NULL};

    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 2, 4);

    DFS(adj, n, 0);

    return 0;
}
