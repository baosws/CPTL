#pragma once
#include <vector>
#include <queue>

template <class dist_type = int,
         class graph_type = std::vector<std::vector<std::pair<int, int>>>>
std::vector<dist_type> dijkstra(graph_type& adj, int s, int t) {
    int n = adj.size();
    std::vector<dist_type> dist(n, INF);
    dist[s] = 0;
    typedef std::pair<dist_type, int> node_type;
    std::priority_queue<node_type, std::vector<node_type>, std::greater<node_type>> pq;
    pq.emplace(0, s);
    while (pq.size()) {
        auto [du, u] = pq.top();
        pq.pop();
        if (du != dist[u]) {
            continue;
        }
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}
