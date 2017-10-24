#ifndef _ALGORITHMS_HPP
#define _ALGORITHMS_HPP

#include <string>

#include <sdsl/wavelet_trees.hpp>

namespace lb{
    using sequence = std::string;
    using wtree = sdsl::wt_blcd<>;

    sequence build_bwt(sequence in);
    wtree build_wtree(sequence bwt);
}
#endif