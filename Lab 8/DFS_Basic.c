#include <stdio.h>
#include <stdbool.h>

#define MAX 10

bool visited[MAX];

void DFS_Visit(int graph[MAX][MAX], int n, int u) {
    visited[u] = true;
    printf("%d ", u);

    // BAD: scans all vertices every time (O(V²))
    for (int v = 0; v < n; v++) {
        if (graph[u][v] == 1 && !visited[v]) {
            DFS_Visit(graph, n, v);
        }
    }
}

void DFS(int graph[MAX][MAX], int n, int start) {
    for (int i = 0; i < n; i++)
        visited[i] = false;

    DFS_Visit(graph, n, start);
}

int main() {
    int n = 5;
    int graph[MAX][MAX] = {
        {0,1,1,0,0},
        {1,0,0,1,0},
        {1,0,0,0,1},
        {0,1,0,0,0},
        {0,0,1,0,0}
    };

    DFS(graph, n, 0);

    return 0;
}
