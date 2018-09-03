#pragma once
#include <tuple>

template <class T>
std::tuple<T, T, T> egcd(T a, T b) {
    std::pair<T, T> ra(1, 0), rb(0, 1);
    while (b) {
        T q = a / b, r = a % b;
        std::pair<T, T> tmp = {ra.first - q * rb.first, ra.second - q * rb.second};
        ra = rb;
        rb = tmp;
        std::tie(a, b) = {b, r};
    }
    return {a, ra.first, ra.second};
}
