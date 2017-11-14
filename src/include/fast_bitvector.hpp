#ifndef _FAST_BITVECTOR_HPP_
#define _FAST_BITVECTOR_HPP_

#include <vector>
#include <iterator>

#include "base.hpp"

namespace lb {
    class fast_bitvector {
        using base_bitvector = std::vector<bool>;
    public:
	    using value_type = bool;
	    fast_bitvector();
	    fast_bitvector(const fast_bitvector& fbv);
        fast_bitvector(fast_bitvector&& fbv);
        size_t rank(size_t index, bool bit = false) const;
        void push_back(const bool& val);
        size_t size() const;
    private:
        base_bitvector bv;
        std::vector<size_t> cs;
    };
#ifdef USE_FAST_BV
    using bitvector = fast_bitvector;
#endif
}

#endif  // _FAST_BITVECTOR_HPP_
