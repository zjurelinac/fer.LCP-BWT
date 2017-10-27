#ifndef _BASE_HPP_
#define _BASE_HPP_

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#ifdef USE_SDSL_WTREE
    #include <sdsl/wavelet_trees.hpp>
#endif

namespace lb {
    using bitvector = std::vector<bool>;
    using sequence = std::string;
    using alpha_interval = std::pair<short, short>;
    using interval = std::pair<int, int>;
    using intervals = std::vector<interval>;
    using lcp_array = std::vector<int>;
#ifdef USE_SDSL_WTREE
    using wtree = sdsl::wt_blcd<>;
#endif
}

#ifdef DEBUG

template <typename A, typename B>
std::ostream &operator<<(std::ostream &os, std::pair<A, B> p) {
    return os << "<" << p.first << ", " << p.second << ">";
}

#endif

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> v) {
    for (auto x : v)
        os << x << ' ';
    os << "\n";
    return os;
}

#endif  // _BASE_HPP_