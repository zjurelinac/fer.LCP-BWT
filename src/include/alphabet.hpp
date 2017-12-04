#ifndef _ALPHABET_HPP_
#define _ALPHABET_HPP_

#include <cstring>
#include <map>

#include "base.hpp"

namespace lb {
    class alphabet {
    public:
        alphabet()
            : sz(0) {}
        inline alphabet(const lb::sequence& text);

        symbol_type operator[](lb::size_t index) const
           { return rmap[index]; }
        uint8 operator[](symbol_type symbol) const
            { return map[symbol]; }
        int csum(lb::size_t index) const
            { return cs[index]; }
        lb::size_t size() const
            { return sz; }
    private:
        uint8 map[256];
        char rmap[256];
        lb::size_t cs[256];
        lb::size_t sz;
    };
}

lb::alphabet::alphabet(const lb::sequence& text) {
    std::map<symbol_type, int> cnt;
    for (auto& c : text) ++cnt[c];

    memset(map, 0, sizeof(map));
    memset(rmap, 0, sizeof(rmap));
    memset(cs, 0, sizeof(cs));

    sz = cnt.size();

    int tsum = 0, tindex = 0;
    for (auto& it : cnt) {
        map[it.first] = tindex;
        rmap[tindex] = it.first;
        cs[tindex++] = tsum;
        tsum += it.second;
    }
}

#endif  // _ALPHABET_HPP_