#pragma once
#include <vector>

template <bool bidirect = true>
struct Graph {
    int _n = 0;
    
    template <typename W = int>
    struct Node {
        typedef W weight_type;
        int tar;
        W w;
        Node(int tar, W w = 0) : tar(tar), w(w) {}
    };

    template <typename W = int>
    struct Edge {
        typedef W weight_type;
        int src, tar;
        W w;
        Edge(int src, int tar, W w = 0): src(src), tar(tar), w(w) {}
    };

    virtual size_t n() const {
        return _n;
    }
};

template <bool Bi = true,
          typename Node = Graph<>::Node<>,
          typename Adj = std::vector<Node>>
struct AdjGraph: virtual Graph<Bi> {
    std::vector<Adj> adj;

    typedef Node node_type;
    typedef Adj adj_type;
    static constexpr bool is_bidirected = Bi;
    
    AdjGraph(size_t n): adj(n) {
        this->_n = n;
    }
    
    virtual void add_edge(int u, int v, typename node_type::weight_type w = 0) {
        adj[u].emplace_back(v, w);
        if (Bi) {
            adj[v].emplace_back(u, w);
        }
    }

    Adj& operator[](int i) {
        return adj[i];
    }
};

template <bool Bi = true,
          typename Edge = Graph<>::Edge<>>
class EdgeGraph: virtual Graph<Bi> {
protected:
    std::vector<Edge> edges;

public:
    typedef Edge edge_type;
    static constexpr bool is_bidirected = Bi;

    EdgeGraph(size_t n) {
        this->_n = n;
    }
    
    virtual void add_edge(int u, int v, typename edge_type::weight_type w = 0) {
        edges.emplace_back(u, v, w);
        if (Bi) {
            edges.emplace_back(v, u, w);
        }
    }

    typename std::vector<Edge>::const_iterator begin() const {
        return edges.begin();
    }
    typename std::vector<Edge>::const_iterator end() const {
        return edges.end();
    }
};
