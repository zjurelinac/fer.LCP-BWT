#ifndef _ALGORITHMS_HPP_
#define _ALGORITHMS_HPP_

#ifndef USE_SDSL_WTREE
    #include "wavelet_tree.hpp"
#endif

#include "base.hpp"
#include "alphabet.hpp"

namespace lb {
    sequence build_bwt(const sequence& in);
    wtree build_wtree(const sequence& bwt, const alphabet& a);
    lcp_array build_lcp(const wtree& wt);           // TODO: @Zivec
    intervals get_intervals(interval start, const alphabet& a, const wtree& wt);
}

#endif  // _ALGORITHMS_HPP_