#ifndef _WAVELET_TREE_HPP_
#define _WAVELET_TREE_HPP_

#include <vector>

namespace lb {
    class wavelet_tree {
    public:
        wavelet_tree(const sequence& in, const alphabet& a);
        int rank();
    private:
        alphabet a;

    };

#ifndef USE_SDSL_WTREE
    using wtree = wavelet_tree;
#endif
}

#endif  // _WAVELET_TREE_HPP_