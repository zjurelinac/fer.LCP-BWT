#ifndef _ALGORITHMS_HPP_
#define _ALGORITHMS_HPP_

#include "base.hpp"
#include "alphabet.hpp"

namespace lb {
    sequence build_bwt(const sequence& in);
    wtree build_wtree(const sequence& bwt, const alphabet& a);
    intervals get_intervals(interval start, alphabet& a, wtree& wtree);
}

#endif  // _ALGORITHMS_HPP_