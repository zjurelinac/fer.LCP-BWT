#include "fast_bitvector.hpp"
#include "base.hpp"
#include <algorithm>
#include <iterator>


lb::fast_bitvector::fast_bitvector() {}

lb::fast_bitvector::fast_bitvector(const fast_bitvector &fbv) : bv(fbv.bv), cs(fbv.cs) {}

void lb::fast_bitvector::push_back(const bool& val) {
	if (bv.size() % BUCKET_SIZE == 0)
	    cs.push_back(cs.size() ? cs[cs.size() - 1] : 0);
	if (val)
	    ++cs[cs.size() - 1];
    bv.push_back(val);
}

lb::size_t lb::fast_bitvector::size() const {
    return bv.size();
}

lb::size_t lb::fast_bitvector::rank(const lb::size_t index, const bool bit) const {
    no_checked_buckets = floor(index / BUCKET_SIZE) - 1;
    rank = cs[ no_checked_buckets];
    base = (no_checked_buckets + 1) * BUCKET_SIZE;
    rank += count_bits( cs[ no_checked_buckets + 1], index - base);
    

}

lb::size_t lb::fast_bitvector::count_bits(bucket, index){


}


