#pragma once

#include <type_traits>
#include <vector>
#include <list>
#include <tuple>
#include <limits>
#include <string>

namespace meta {
template<typename T>
struct is_container : std::false_type {};

template <typename... Ts>
struct is_container< std::list<Ts...> > : std::true_type{};

template <typename... Ts>
struct is_container< std::vector<Ts...> > : std::true_type{};

template <typename... Ts>
inline constexpr bool is_container_v = is_container<Ts...>::value;

template<typename T>
struct is_tuple : std::false_type {};

template <typename... Ts>
struct is_tuple< std::tuple<Ts...> > : std::true_type {};

template <typename... Ts>
inline constexpr bool is_tuple_v = is_tuple<Ts...>::value;

template <typename Tuple, std::size_t I = 0>
std::string tuple_to_string(const Tuple& tuple, const char& separator = '.') {
    if constexpr (I == std::tuple_size_v<Tuple> - 1) {
        return std::to_string(std::get<I>(tuple));
    }
    else if constexpr (I < std::tuple_size_v<Tuple>) {
        return std::to_string(std::get<I>(tuple)) + separator + tuple_to_string<Tuple, I + 1>(tuple, separator);
    }
}

template <typename Tuple, std::size_t I = 0>
void check_integer_tuple_type() {
    if constexpr (I < std::tuple_size_v<Tuple>) {
        static_assert(std::numeric_limits< std::tuple_element_t<I, Tuple> >::is_integer, "Tuple element must be integer");
        check_integer_tuple_type<Tuple, I + 1>();
    }
}

}
