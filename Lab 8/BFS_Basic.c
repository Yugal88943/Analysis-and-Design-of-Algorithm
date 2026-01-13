#include <stdio.h>
#include <stdbool.h>

#define MAX 10

void BFS(int graph[MAX][MAX], int n, int start) {
    bool visited[MAX] = {false};
    int queue[MAX];
    int front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    while (front != rear) {
        int u = queue[front++];

        printf("%d ", u);

        // BAD: scanning all vertices every time
        for (int v = 0; v < n; v++) {
            if (graph[u][v] == 1 && !visited[v]) {
                visited[v] = true;
                queue[rear++] = v;
            }
        }
    }
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

    BFS(graph, n, 0);

    return 0;
}
