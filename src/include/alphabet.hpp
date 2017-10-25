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
        alphabet(const lb::sequence& text);
        std::size_t size();
        int operator[](int index) const;
    private:
        std::unordered_map<symbol_type, int> csum;
    };
}

#endif  // _ALPHABET_HPP