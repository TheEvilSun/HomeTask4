#pragma once

#include <type_traits>
#include <vector>
#include <list>
#include <tuple>
#include <limits>
#include <string>

/*!
\brief Метафункции для работы с контейнерами <i>std::vector</i>, <i>std::list</i>, <i>std::tuple</i>
\author Алексей Волков
\version 1.0
\date Январь 2024

Метафункци, которые определяют, является ли рассматриваемый тип <i>std::vector</i>, <i>std::list</i> или <i>std::tuple</i>. Есть возможность проверить соответствие типа элементов <i>std::tuple</i> целочисленным типам(<i>int8_t</i>, <i>uint8_t</i>, ...)
*/

namespace meta {
/*!
Проверяет является ли указанный тип <b>T</b> контейнером
\param T проверяемый тип
\return <i>true</i> для <i>std::vector</i>, <i>std::list</i>. <i>false</i> для остальных типов
*/
template<typename T>
struct is_container : std::false_type {};

/*!
Перегрузка <i>is_container</i> для <i>std::list</i>
\param T проверяемый тип
\return <i>true</i> для <i>std::list</i>. <i>false</i> для остальных типов
*/
template <typename... Ts>
struct is_container< std::list<Ts...> > : std::true_type{};

/*!
Перегрузка <i>is_container</i> для <i>std::vector</i>
\param T проверяемый тип
\return <i>true</i> для <i>std::vector</i>. <i>false</i> для остальных типов
*/
template <typename... Ts>
struct is_container< std::vector<Ts...> > : std::true_type{};

template <typename... Ts>
inline constexpr bool is_container_v = is_container<Ts...>::value;

/*!
Проверяет является ли указанный тип <b>T</b> <i>std::tuple</i>
\param T проверяемый тип
\return <i>true</i> для <i>std::tuple</i>. <i>false</i> для остальных типов
*/
template<typename T>
struct is_tuple : std::false_type {};

/*!
Перегрузка <i>is_tuple</i> для <i>std::tuple</i>
\param T проверяемый тип
\return <i>true</i> для <i>std::tuple</i>. <i>tuple</i> для остальных типов
*/
template <typename... Ts>
struct is_tuple< std::tuple<Ts...> > : std::true_type {};

template <typename... Ts>
inline constexpr bool is_tuple_v = is_tuple<Ts...>::value;

/*!
Представляет <i>std::tuple</i> в виде строки из его элементов, соединенных символом <i>separator</i>
\param Tuple тип <i>std::tuple</i>
\param tuple <i>std::tuple</i>
\param separator разделитель
\return <i>std::string</i>
*/
template <typename Tuple, std::size_t I = 0>
std::string tuple_to_string(const Tuple& tuple, const char& separator = '.') {
    if constexpr (I == std::tuple_size_v<Tuple> - 1) {
        return std::to_string(std::get<I>(tuple));
    }
    else if constexpr (I < std::tuple_size_v<Tuple>) {
        return std::to_string(std::get<I>(tuple)) + separator + tuple_to_string<Tuple, I + 1>(tuple, separator);
    }
}

/*!
Проверяет на этапе компиляции являеются ли типы элементов <i>std::tuple</i> целочисленными
\param Tuple тип <i>std::tuple</i>
*/
template <typename Tuple, std::size_t I = 0>
void check_integer_tuple_type() {
    if constexpr (I < std::tuple_size_v<Tuple>) {
        static_assert(std::numeric_limits< std::tuple_element_t<I, Tuple> >::is_integer, "Tuple element must be integer");
        check_integer_tuple_type<Tuple, I + 1>();
    }
}

}
