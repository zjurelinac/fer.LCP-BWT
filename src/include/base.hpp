#ifndef _BASE_HPP_
#define _BASE_HPP_

#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <sdsl/wavelet_trees.hpp>

namespace lb {
    using sequence = std::string;
    using wtree = sdsl::wt_blcd<>;
    using alpha_interval = std::pair<unsigned char, unsigned char>;
    using interval = std::pair<int, int>;
    using intervals = std::vector<interval>;
}

#endif  // _BASE_HPP_ 