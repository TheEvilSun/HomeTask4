#pragma once

#include <iostream>
#include <MetaFunctions.h>
#include <sstream>

/*!
\brief Функции парсинга и печати условного IP-адреса
\author Алексей Волков
\version 1.0
\date Январь 2024

Функци, которые которые парсят и печают на стандартный ввывод условный IP-адрес. Работают с целочисленными типами, <i>std::string</i>, <i>std::list</i>, <i>std::vector</i>, <i>std::tuple</i>
*/
namespace parse {

/*!
Прасит строку IP-адреса, строка возвращается неизменной
\param ip строковый IP-адрес
\param separator разделитель
\return <i>std::string</i>
*/
template<typename String, std::enable_if_t<std::is_same_v<String, std::string>, bool> = true>
std::string parse_ip(const String& ip, const char& separator = '.'){
    return ip;
}

/*!
Прасит целочисленный IP-адрес, возращает строку из значений байтов, соединенных <i>separator</i>, начиная со старшего байта
\param ip целочисленный IP-адрес
\param separator разделитель
\return <i>std::string</i>
*/
template<typename Integer, std::enable_if_t<std::numeric_limits<Integer>::is_integer, bool> = true>
std::string parse_ip(const Integer& ip, const char& separator = '.'){
    std::make_unsigned_t<Integer> mask;

    switch(sizeof(Integer)) {
    case 1: {
        mask = 0xFF;
        break;
    }
    case 2: {
        mask = 0xFF00;
        break;
    }
    case 4: {
        mask = 0xFF000000;
        break;
    }
    case 8:
        mask = 0xFF00000000000000;
        break;
    }

    std::ostringstream stream("", std::ios::out);

    auto byte = static_cast<u_int16_t>((ip & mask) >> ((sizeof(ip) - 1) * 8));
    mask = mask >> 8;

    stream << byte;

    for(size_t i = 1; i < sizeof(ip); i++, mask = mask >> 8) {
        byte = static_cast<u_int16_t>((ip & mask) >> ((sizeof(ip) - i - 1) * 8));
        stream << separator << byte;
    }

    return stream.str();
}

/*!
Прасит контейнер <i>std::list</i> или <i>std::vector</i> с IP-адресом, возращает строку из значений контейнера, соединенных <i>separator</i>
\param ip контейнер с IP-адресом
\param separator разделитель
\return <i>std::string</i>
*/
template<typename Container, std::enable_if_t<meta::is_container_v<Container>, bool> = true>
std::string parse_ip(const Container& ip, const char& separator = '.'){

    static_assert(std::numeric_limits<typename Container::value_type>::is_integer, "Container type must be integer");

    if(ip.empty()) {
        return {};
    }

    std::ostringstream stream("", std::ios::out);

    auto iter = ip.begin();
    stream << *iter;
    iter++;

    for(; iter != ip.end(); iter++) {
        stream << separator << *iter;
    }

    return stream.str();
}

/*!
Прасит <i>std::tuple</i> с IP-адресом, возращает строку из значений <i>std::tuple</i>, соединенных <i>separator</i>
\param ip контейнер с IP-адресом
\param separator разделитель
\warning Элементы <i>std::tuple</i> должны быть целочислеными, в противном случае будет ошибка на этапе компиляции
\return <i>std::string</i>
*/
template<typename Tuple, std::enable_if_t<meta::is_tuple_v<Tuple>, bool> = true>
std::string parse_ip(const Tuple& ip, const char& separator = '.') {
    if(std::tuple_size_v<Tuple> == 0) {
        return {};
    }

    meta::check_integer_tuple_type<Tuple>();

    return meta::tuple_to_string<Tuple>(ip, separator);
}

/*!
Печатает на стандартный вывод распарсенный IP-адрес
\param ip IP-адрес
\param separator разделитель
*/
template<typename T>
void print_ip(const T& ip, const char& separator = '.') {
    std::cout << parse_ip(ip, separator) << std::endl;
}

}
