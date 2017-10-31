#include "alphabet.hpp"

lb::alphabet::alphabet() {}

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

lb::alphabet::alphabet(const lb::alphabet& a) : map(a.map), rmap(a.rmap), cs(a.cs) {}

lb::alphabet::alphabet(alphabet&& a) : map(std::move(a.map)), rmap(std::move(a.rmap)), cs(std::move(a.cs)) {}

lb::symbol_type lb::alphabet::operator[](lb::size_t index) const {
    return rmap.find(index)->second;
}

lb::size_t lb::alphabet::operator[](lb::symbol_type symbol) const {
    return map.find(symbol)->second;
}

int lb::alphabet::csum(lb::size_t index) const {
    return cs.find(index)->second;
}

lb::size_t lb::alphabet::size() const {
    return map.size();
}