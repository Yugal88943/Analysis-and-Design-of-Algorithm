#include <stdio.h>

#define INF 999999

void floydWarshall(int dist[][4], int n)
{
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}

int main()
{
    int n = 4;
    int dist[4][4] = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };

    floydWarshall(dist, n);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%7d", dist[i][j]);
        printf("\n");
    }
    return 0;
}
