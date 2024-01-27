#include <catch2/catch_test_macros.hpp>
#include <MetaFunctions.h>
#include <PrintIP.h>
#include <map>

TEST_CASE("Meta functions test") {
    std::vector<int> v1;
    std::list<double> l1;
    std::tuple<double, int, std::string> t1;

    REQUIRE_FALSE(meta::is_container_v<float>);
    REQUIRE_FALSE(meta::is_container_v<std::map<int, std::string>>);
    REQUIRE(meta::is_container_v<decltype(v1)>);
    REQUIRE(meta::is_container_v<decltype(l1)>);
    REQUIRE(meta::is_container_v<std::list<std::string>>);
    REQUIRE(meta::is_container_v<std::vector<size_t>>);
    REQUIRE(meta::is_tuple_v<decltype(t1)>);
    REQUIRE(meta::is_tuple_v<std::tuple<int, double, float>>);
}

TEST_CASE("Parse function test") {
    REQUIRE(parse::parse_ip(std::string("Test string")) == "Test string");
    REQUIRE(parse::parse_ip(int8_t{-1}) == "255");
    REQUIRE(parse::parse_ip(int32_t{0}) == "0.0.0.0");
    REQUIRE(parse::parse_ip(u_int32_t{3232235522}) == "192.168.0.2");
    REQUIRE(parse::parse_ip(u_int64_t{3232235522}) == "0.0.0.0.192.168.0.2");
    REQUIRE(parse::parse_ip(std::vector{192, 168, 0, 1}) == "192.168.0.1");
    REQUIRE(parse::parse_ip(std::list{1, 2}) == "1.2");
    REQUIRE(parse::parse_ip(std::make_tuple(-123, 587, 8, 0, 87)) == "-123.587.8.0.87");
}
