#include "dijkstras.h"
#include <algorithm>


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    vector<bool> vis(n, 0);
    previous.assign(n, -1);

    using Node = pair<int, int>;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({0, source});
    distance[source] = 0;

    while (!pq.empty()) {
        auto [curDist, u] = pq.top();
        pq.pop();

        if (vis[u]) continue;
        vis[u] = 1;

        for (auto &edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

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
    if ((destination < 0) || (destination >= (int)distances.size()) || (distances[destination] == INF)) return {};
    vector<int> path;

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