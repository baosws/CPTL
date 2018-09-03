#pragma once
#include <vector>
struct ddsu {
    std::vector<int> par, rank, cnt;
    ddsu(int n = 0) {
        par.resize(n);
        rank.resize(n, 1);
        cnt.resize(n, 1);
        for (int i = 0; i < n; ++i) {
            par[i] = i;
        }
    }
    int size() const {
        return par.size();
    }
    void resize(int n) {
        par.resize(n);
        rank.resize(n, 1);
        cnt.resize(n, 1);
    }
    int root(int u) {
        return u == par[u] ? u : par[u] = root(par[u]);
    }
    int root(int u) const {
        return u == par[u] ? u : root(par[u]);
    }
    void join(int u, int v) {
        u = root(u);
        v = root(v);
        if (rank[u] >= rank[v]) {
            par[v] = u;
            cnt[u] += cnt[v];
            rank[u] = std::max(rank[u], rank[v] + 1);
        }
        else {
            par[u] = v;
            cnt[v] += cnt[u];
        }
    }
    bool is_joint(int u, int v) {
        return root(u) == root(v);
    }
    bool is_joint(int u, int v) const {
        return root(u) == root(v);
    }
};
