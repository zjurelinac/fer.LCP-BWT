#ifndef _ALPHABET_HPP_
#define _ALPHABET_HPP_

#include <cstddef>
#include <map>
#include <unordered_map>

#include "base.hpp"

namespace lb {
    class alphabet {
        using symbol_type = lb::sequence::value_type;
    public:
        alphabet();
        alphabet(const lb::sequence& text);
        alphabet(const alphabet& a);
        char operator[](int index) const;
        int csum(int index) const;
        std::size_t size() const;
    private:
        std::unordered_map<symbol_type, int> mapping;
        std::unordered_map<symbol_type, int> cs;
    };
}

#endif  // _ALPHABET_HPP_