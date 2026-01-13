#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1000000000;

struct Edge { int u, v, w; };

// Bellman–Ford
bool bellmanFord(int n, vector<Edge>& edges, vector<int>& h)
{
    h.assign(n, INF);
    h[n-1] = 0;  // q node is last (n-1)

    for(int i = 0; i < n - 1; i++){
        for(auto &e : edges){
            if(h[e.u] < INF && h[e.u] + e.w < h[e.v])
                h[e.v] = h[e.u] + e.w;
        }
    }

    // negative cycle check
    for(auto &e : edges)
        if(h[e.u] < INF && h[e.u] + e.w < h[e.v])
            return false;

    return true;
}

// Dijkstra using adjacency list
vector<int> dijkstra(int n, vector<vector<pair<int,int>>>& adj, int src)
{
    vector<int> dist(n, INF);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while(!pq.empty())
    {
        auto [d, u] = pq.top(); pq.pop();
        if(d != dist[u]) continue;

        for(auto &p : adj[u])
        {
            int v = p.first, w = p.second;
            if(dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// Johnson's Algorithm
vector<vector<int>> johnson(int n, vector<Edge>& edges)
{
    // Step 1: Add q node (index n), edges q->v weight 0
    vector<Edge> newEdges = edges;
    for(int v = 0; v < n; v++)
        newEdges.push_back({n, v, 0});

    // Run Bellman–Ford
    vector<int> h;  
    if(!bellmanFord(n + 1, newEdges, h)){
        cout << "Negative cycle detected\n";
        return {};
    }

    // Step 2: Reweight edges
    vector<vector<pair<int,int>>> adj(n);
    for(auto &e : edges){
        int w2 = e.w + h[e.u] - h[e.v];
        adj[e.u].push_back({e.v, w2});
    }

    // Step 3: Run Dijkstra from each node
    vector<vector<int>> result(n, vector<int>(n, INF));
    for(int s = 0; s < n; s++){
        vector<int> dist_r = dijkstra(n, adj, s);

        // Convert back to original weights
        for(int v = 0; v < n; v++){
            if(dist_r[v] < INF)
                result[s][v] = dist_r[v] + h[v] - h[s];
        }
    }

    return result;
}

// --------------------------
int main()
{
    int n = 5;
    vector<Edge> edges = {
        {0,1,10}, {0,3,30}, {0,4,100},
        {1,2,50}, {2,4,10},
        {3,2,20}, {3,4,60}
    };

    vector<vector<int>> ans = johnson(n, edges);

    cout << "All-pairs shortest paths:\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cout << (ans[i][j] == INF ? -1 : ans[i][j]) << " ";
        cout << endl;
    }
    return 0;
}
