#ifndef _ALPHABET_HPP_
#define _ALPHABET_HPP_

#include <map>
#include <unordered_map>
#include <cstdio>

#include "base.hpp"

namespace lb {
    class alphabet {
    public:
        alphabet();
        alphabet(const lb::sequence& text);
        alphabet(const alphabet& a);
        alphabet(alphabet&& a);
        symbol_type operator[](lb::size_t index) const;
        lb::size_t operator[](symbol_type symbol) const;
        int csum(lb::size_t index) const;
        lb::size_t size() const;
    private:
        std::unordered_map<symbol_type, lb::size_t> map;
        std::unordered_map<lb::size_t, symbol_type> rmap;
        std::unordered_map<symbol_type, lb::size_t> cs;
    };
}

#endif  // _ALPHABET_HPP_