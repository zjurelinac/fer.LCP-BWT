#ifndef _ALGORITHMS_HPP_
#define _ALGORITHMS_HPP_

#include "base.hpp"
#include "alphabet.hpp"

namespace lb {
    //alphabet build_alphabet(const sequence& in);
    sequence build_bwt(const sequence& in);
    wtree build_wtree(const sequence& bwt);
    intervals get_intervals(interval start, lb::alphabet& a, lb::wtree& wtree);
}

#endif  // _ALGORITHMS_HPP_