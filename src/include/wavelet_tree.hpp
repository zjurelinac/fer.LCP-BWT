#ifndef _WAVELET_TREE_HPP_
#define _WAVELET_TREE_HPP_

#include <cstddef>
#include <vector>

#include "base.hpp"
#include "alphabet.hpp"

namespace lb {
    class wavelet_tree {
        using symbol_type = lb::sequence::value_type;
    public:
        wavelet_tree();
        wavelet_tree(const lb::sequence& in, const lb::alphabet& a);
        wavelet_tree(const wavelet_tree& wt);
        wavelet_tree(wavelet_tree&& wt);                        // TODO: @Tonko
        symbol_type operator[](std::size_t index) const;        // TODO: @Tonko
        int rank(std::size_t index, symbol_type symbol) const;
        int select(std::size_t num, symbol_type symbol) const;  // TODO: @Tonko
        std::size_t size() const;
        void show() const;
    private:
        const lb::alphabet& a;
        std::size_t sz;
        std::vector<bitvector> nodes;
    };

#ifndef USE_SDSL_WTREE
    using wtree = wavelet_tree;
#endif
}

#endif  // _WAVELET_TREE_HPP_