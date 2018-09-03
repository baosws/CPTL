#pragma once
#include <tuple>
#include <mutex>
template <class... T>
class Tuple {
    std::tuple<T...> data;
    std::mutex mtx;
public:
    // constructors
    Tuple() {}
    Tuple(T... args) : data(std::forward<T>(args)...) {}
    Tuple(const Tuple&) = default;
    Tuple(Tuple&& p) {
        data.operator=(std::forward<std::tuple<T...>>(p));
    }
    Tuple(const std::tuple<T...>& p) {
        data = p;
    }
    Tuple(std::tuple<T...>&& p) : data(std::forward<std::tuple<T...>>(p)) {}
    
    // copy operators
    Tuple& operator=(const std::tuple<T...>& p) {
        std::lock_guard lock(mtx);
        data = p;
        return *this;
    }
    Tuple& operator=(std::tuple<T...>&& p) {
        std::lock_guard lock(mtx);
        data.operator=(std::forward<std::tuple<T...>>(p));
        return *this;
    }

    // access method
    template <size_t i>
    decltype(std::get<i>(data)) get() {
        std::lock_guard lock(mtx);
        return std::get<i>(data);
    }
    template <size_t i>
    const decltype(std::get<i>(data)) get() const {
        std::lock_guard lock(mtx);
        return std::get<i>(data);
    }
};
