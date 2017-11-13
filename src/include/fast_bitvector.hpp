#ifndef FAST_BITVECTOR_HPP
#define FAST_BITVECTOR_HPP

#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <iterator>
#include "base.hpp"

namespace lb { 
    class fast_bitvector {
    public:
	typedef bool value_type;
	fast_bitvector();
	fast_bitvector(std::vector<bool> bv);
        size_t rank(size_t index, bool bit = false);
        void push_back(const bool& val);
        size_t size();
	std::vector<bool>::iterator begin() ;
    private:
        std::vector<bool> bv;
        std::vector<size_t> cs;
    };
    using bitvector = fast_bitvector;
}

#endif
