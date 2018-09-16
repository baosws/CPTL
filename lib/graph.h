#pragma once
#include <vector>

template <typename graph_type = std::vector<std::vector<int>>>
struct Graph {
    graph_type adj;
    std::vector<int> par;
    Graph(int n): adj(n), par(n) {}

    template <bool bidirect = true>
    void add_edge(int u, int v) {
        if (u != v) {
            adj[u].push_back(v);
#if bidirect
            adj[v].push_back(u);
#endif
        }
    }
};
