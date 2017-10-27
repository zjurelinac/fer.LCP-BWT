#ifndef _WAVELET_TREE_HPP_
#define _WAVELET_TREE_HPP_

#include <vector>

#include "base.hpp"
#include "alphabet.hpp"

namespace lb {
    class wavelet_tree {
    public:
        wavelet_tree(const lb::sequence& in, const lb::alphabet& a);
        int rank();
    private:
        alphabet a;
        std::vector<bitvector> nodes;
    };

#ifndef USE_SDSL_WTREE
    using wtree = wavelet_tree;
#endif
}

#endif  // _WAVELET_TREE_HPP_