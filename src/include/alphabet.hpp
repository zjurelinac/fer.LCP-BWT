#ifndef _ALPHABET_HPP_
#define _ALPHABET_HPP_

#include <cstddef>
#include <map>
#include <unordered_map>
#include <cstdio>

#include "base.hpp"

namespace lb {
    class alphabet {
        using symbol_type = lb::sequence::value_type;
    public:
        alphabet();
        alphabet(const lb::sequence& text);
        alphabet(const alphabet& a);
        alphabet(alphabet&& a);
        symbol_type operator[](std::size_t index) const;
        std::size_t operator[](symbol_type symbol) const;
        int csum(std::size_t index) const;
        std::size_t size() const;
    private:
        std::unordered_map<symbol_type, std::size_t> map;
        std::unordered_map<std::size_t, symbol_type> rmap;
        std::unordered_map<symbol_type, std::size_t> cs;
    };
}

#endif  // _ALPHABET_HPP_