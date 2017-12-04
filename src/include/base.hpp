#ifndef _BASE_HPP_
#define _BASE_HPP_

#include <cstddef>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace lb {
    using int8 = signed char;
    using uint8 = unsigned char;
    using size_t = unsigned int;
    using sequence = std::string;
    using symbol_type = sequence::value_type;
    using alpha_interval = std::pair<int8, int8>;
    using interval = std::pair<lb::size_t, lb::size_t>;
    using intervals = std::vector<interval>;
    using lcp_array = std::vector<int8>;
#ifndef USE_FAST_BV
    using bitvector = std::vector<bool>;
#endif
}

#ifdef DEBUG

template <typename A, typename B>
std::ostream &operator<<(std::ostream &os, std::pair<A, B> p) {
    return os << "[" << p.first << ", " << p.second << "]";
}

template <typename A, typename B, typename C>
std::ostream &operator<<(std::ostream &os, std::tuple<A, B, C> t) {
    return os << "<" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ">";
}

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> v) {
    for (auto x : v)
        os << x << ' ';
    os << "\n";
    return os;
}

#endif

#endif  // _BASE_HPP_