#ifndef FAST_BITVECTOR_HPP
#define FAST_BITVECTOR_HPP

#include <vector>

#include "base.hpp"

namespace lb {
    class fast_bitvector {
    public:
	fast_bitvector(const lb::bitvector& bitv);
        size_t rank(size_t index, bool bit = false);
        void push_back(const bool& val);
        size_t size();
    private:
        std::vector<bool> bv;
        std::vector<size_t> cs;
    };
}

#endif
