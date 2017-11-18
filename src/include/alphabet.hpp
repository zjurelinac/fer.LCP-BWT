#ifndef _ALPHABET_HPP_
#define _ALPHABET_HPP_

#include <map>
#include <unordered_map>
#include <cstdio>

#include "base.hpp"

namespace lb {
    class alphabet {
    public:
        alphabet() {}

        alphabet(const alphabet& a)
            : map(a.map), rmap(a.rmap), cs(a.cs) {}
        alphabet(alphabet&& a)
            : map(std::move(a.map)), rmap(std::move(a.rmap)), cs(std::move(a.cs)) {}
        alphabet(const lb::sequence& text);
        symbol_type operator[](lb::size_t index) const
           { return rmap.find(index)->second; }
        lb::size_t operator[](symbol_type symbol) const
            { return map.find(symbol)->second; }
        int csum(lb::size_t index) const
            { return cs.find(index)->second; }
        lb::size_t size() const
            { return map.size(); }
    private:
        std::unordered_map<symbol_type, lb::size_t> map;
        std::unordered_map<lb::size_t, symbol_type> rmap;
        std::unordered_map<symbol_type, lb::size_t> cs;
    };
}

#endif  // _ALPHABET_HPP_