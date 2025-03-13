#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    vector<bool> vis(n, 0);
    previous.resize(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({source, 0});
    distance[source] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (vis[u]) continue;
        vis[u] = 1;

        for (const Edge& neighbor: G[u]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;


            if (!vis[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> path;
    if (distances[destination == INF]) return path;

    for (int i = destination; i != -1; i = previous[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
    cout << "\nTotal cost is " << total << "\n";
}