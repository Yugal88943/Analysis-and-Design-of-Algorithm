#include <stdio.h>
#define INF 9999
#define N 5  // number of nodes

int main()
{
    int graph[N][N] = {
        {0, 10, 0, 30, 100},
        {0, 0, 50, 0, 0},
        {0, 0, 0, 0, 10},
        {0, 0, 20, 0, 60},
        {0, 0, 0, 0, 0}
    };

    int dist[N];
    int visited[N];

    // Step 1: Initialize distances and visited
    for(int i = 0; i < N; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
    }

    int source = 0;
    dist[source] = 0;

    // Step 2: Dijkstra
    for(int c = 0; c < N - 1; c++)
    {
        // Pick unvisited node with minimum distance
        int min = INF, u = -1;
        for(int i = 0; i < N; i++)
        {
            if(!visited[i] && dist[i] < min)
            {
                min = dist[i];
                u = i;
            }
        }

        // Mark it visited
        visited[u] = 1;

        // Update its neighbors
        for(int v = 0; v < N; v++)
        {
            if(graph[u][v] != 0 && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print result
    for(int i = 0; i < N; i++)
        printf("Shortest distance to %d = %d\n", i, dist[i]);

    return 0;
}
