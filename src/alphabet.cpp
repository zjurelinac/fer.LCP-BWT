#include "alphabet.hpp"

lb::alphabet::alphabet(const lb::sequence& text) {
    std::map<symbol_type, int> cnt;
    for (auto& c : text) ++cnt[c];

    int tsum = 0, tindex = 0;
    for (auto& it : cnt) {
        mapping[tindex] = it.first;
        cs[tindex++] = tsum;
        tsum += it.second;
    }    
}

char lb::alphabet::operator[](int index) const {
    return mapping.find(index)->second;
}

int lb::alphabet::csum(int index) const {
    return cs.find(index)->second;
}

std::size_t lb::alphabet::size() const {
    return mapping.size();
}