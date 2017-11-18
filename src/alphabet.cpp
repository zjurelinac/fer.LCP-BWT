#include "alphabet.hpp"

lb::alphabet::alphabet(const lb::sequence& text) {
    std::map<symbol_type, int> cnt;
    for (auto& c : text) ++cnt[c];

    int tsum = 0, tindex = 0;
    for (auto& it : cnt) {
        map[it.first] = tindex;
        rmap[tindex] = it.first;
        cs[tindex++] = tsum;
        tsum += it.second;
    }
}
