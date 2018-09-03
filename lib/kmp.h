#pragma once
#include <string>
#include <vector>

struct kmp_matcher {
    typedef std::string::const_iterator iter_type;
    std::vector<int> next;
    std::string pattern;
    kmp_matcher(std::string pattern_) : pattern(pattern_) {
        int n = pattern.length();
        next.resize(n);
        next[0] = -1;
        for (int i = 1, j = -1; i < n; ++i) {
            while (j + 1 && pattern[j + 1] != pattern[i]) {
                j = next[j];
            }
            if (pattern[j + 1] == pattern[i]) {
                ++j;
            }
            next[i] = j;
        }
    }
    kmp_matcher(iter_type begin, iter_type end) : kmp_matcher(std::string(begin, end)) {}
    int match_count(iter_type begin, iter_type end) const {
        int res = 0, j = -1;
        for (iter_type it = begin; it != end; ++it) {
            while (j + 1 && pattern[j + 1] != *it) {
                j = next[j];
            }
            if (pattern[j + 1] == *it) {
                ++j;
            }
            if (j == (int)pattern.length() - 1) {
                ++res;
                j = next[j];
            }
        }
        return res;
    }
    int match_count(const std::string& text) const {
        return match_count(text.begin(), text.end());
    }
    std::vector<int> get_matches(iter_type begin, iter_type end) const {
        std::vector<int> res;
        int j = -1;
        for (iter_type it = begin; it != end; ++it) {
            while (j + 1 && pattern[j + 1] != *it) {
                j = next[j];
            }
            if (pattern[j + 1] == *it) {
                ++j;
            }
            if (j == (int)pattern.length() - 1) {
                res.push_back(it - begin - j + 1);
                j = next[j];
            }
        }
        return res;
    }
    std::vector<int> get_matches(const std::string& text) const {
        return get_matches(text.begin(), text.end());
    }
};
