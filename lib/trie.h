#pragma once
#include <unordered_map>

template <class T>
struct trie {
    struct node {
        int value;
        std::unordered_map<T, node*> child;
        ~node() {
            for (auto it : child) {
                delete it;
            }
        }
    }* root;
public:
    template <class RandomAccessIterator>
    void push(RandomAccessIterator first, RandomAccessIterator last) {
        node* p = root;
        for (RandomAccessIterator it = first; it != last; ++it) {
            if (p->child.find(*it) == p->child.end()) {
                p->child[*it] = new node();
            }
            p = p->child[*it];
        }
    }
    int get() {
        // ...
    }
    ~trie() {
        delete root;
    }
};
