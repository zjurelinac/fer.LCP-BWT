#include "fast_bitvector.hpp"
#include "base.hpp"
#include <algorithm>
#include <iterator>


lb::fast_bitvector::fast_bitvector() : bv() {}

lb::fast_bitvector::fast_bitvector(const fast_bitvector &fbv) : bv(fbv.bv), cs(fbv.cs) {}

void lb::fast_bitvector::push_back(const bool& val) {
    return bv.push_back(val);
}

lb::size_t lb::fast_bitvector::size() const {
    return bv.size();
}

lb::size_t lb::fast_bitvector::rank(const lb::size_t index, const bool bit) const {
    return std::count(bv.begin(), bv.begin() + index, bit);
}


