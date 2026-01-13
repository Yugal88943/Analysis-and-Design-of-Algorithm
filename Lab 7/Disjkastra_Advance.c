#include <stdio.h>
#include <stdlib.h>

#define INF 999999

struct Edge {
    int to, weight;
    struct Edge* next;
};

struct Node {
    int vertex;
    int dist;
};

struct MinHeap {
    int size;
    int capacity;
    int *pos;
    struct Node **array;
};
struct Edge* addEdge(struct Edge* head, int to, int weight) {
    struct Edge* temp = (struct Edge*)malloc(sizeof(struct Edge));
    temp->to = to;
    temp->weight = weight;
    temp->next = head;
    return temp;
}
struct Node* newNode(int v, int dist) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->vertex = v;
    temp->dist = dist;
    return temp;
}

struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    heap->pos = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (struct Node**)malloc(capacity * sizeof(struct Node*));
    return heap;
}

void swapNode(struct Node** a, struct Node** b) {
    struct Node* t = *a;
    *a = *b;
    *b = t;
}
void minHeapify(struct MinHeap* heap, int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < heap->size &&
       heap->array[left]->dist < heap->array[smallest]->dist)
        smallest = left;

    if(right < heap->size &&
       heap->array[right]->dist < heap->array[smallest]->dist)
        smallest = right;

    if(smallest != i) {
        struct Node* smallestNode = heap->array[smallest];
        struct Node* idxNode = heap->array[i];

        heap->pos[smallestNode->vertex] = i;
        heap->pos[idxNode->vertex] = smallest;

        swapNode(&heap->array[smallest], &heap->array[i]);
        minHeapify(heap, smallest);
    }
}
struct Node* extractMin(struct MinHeap* heap) {
    if(heap->size == 0)
        return NULL;

    struct Node* root = heap->array[0];
    struct Node* last = heap->array[heap->size - 1];
    heap->array[0] = last;

    heap->pos[root->vertex] = heap->size - 1;
    heap->pos[last->vertex] = 0;

    heap->size--;
    minHeapify(heap, 0);

    return root;
}
void decreaseKey(struct MinHeap* heap, int v, int dist) {
    int i = heap->pos[v];
    heap->array[i]->dist = dist;

    while(i && heap->array[i]->dist < heap->array[(i-1)/2]->dist) {
        heap->pos[heap->array[i]->vertex] = (i-1)/2;
        heap->pos[heap->array[(i-1)/2]->vertex] = i;

        swapNode(&heap->array[i], &heap->array[(i-1)/2]);
        i = (i-1)/2;
    }
}
int inMinHeap(struct MinHeap* heap, int v) {
    return (heap->pos[v] < heap->size);
}
void dijkstra(struct Edge* graph[], int n, int src)
{
    int dist[n];

    struct MinHeap* heap = createMinHeap(n);

    for(int v = 0; v < n; v++) {
        dist[v] = INF;
        heap->array[v] = newNode(v, dist[v]);
        heap->pos[v] = v;
    }

    dist[src] = 0;
    heap->array[src]->dist = 0;
    decreaseKey(heap, src, 0);
    heap->size = n;

    while(heap->size != 0)
    {
        struct Node* minNode = extractMin(heap);
        int u = minNode->vertex;

        struct Edge* temp = graph[u];
        while(temp != NULL)
        {
            int v = temp->to;

            if(inMinHeap(heap, v) &&
               dist[u] != INF &&
               dist[u] + temp->weight < dist[v])
            {
                dist[v] = dist[u] + temp->weight;
                decreaseKey(heap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    for(int i = 0; i < n; i++)
        printf("Distance to %d = %d\n", i, dist[i]);
}
int main()
{
    int n = 5;

    struct Edge* graph[5] = {NULL};

    graph[0] = addEdge(graph[0], 1, 10);
    graph[0] = addEdge(graph[0], 3, 30);
    graph[0] = addEdge(graph[0], 4, 100);

    graph[1] = addEdge(graph[1], 2, 50);
    graph[2] = addEdge(graph[2], 4, 10);

    graph[3] = addEdge(graph[3], 2, 20);
    graph[3] = addEdge(graph[3], 4, 60);

    dijkstra(graph, n, 0);

    return 0;
}
