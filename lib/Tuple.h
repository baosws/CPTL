#pragma once
#include <tuple>
#include <mutex>

template <class... T>
class Tuple : public std::tuple<T...> {
    std::tuple<T...>& __this = *this;
public:
    using std::tuple<T...>::tuple;
    Tuple(const std::tuple<T...>& other) : std::tuple<T...>(other) {}
    Tuple(std::tuple<T...>&& other) : std::tuple<T...>(std::move(other)) {}
    
    // access method
    template <size_t i>
    decltype(std::get<i>(__this)) get() {
        return std::get<i>(__this);
    }
    
    template <size_t i>
    const decltype(std::get<i>(__this)) get() const {
        return std::get<i>(__this);
    }
};
