#ifndef _WAVELET_TREE_HPP_
#define _WAVELET_TREE_HPP_

#include <vector>

#include "base.hpp"
#include "alphabet.hpp"

namespace lb {
    class wavelet_tree {
    public:
        wavelet_tree();
        wavelet_tree(const lb::sequence& in, const lb::alphabet& a);
        wavelet_tree(const wavelet_tree& wt);
        wavelet_tree(wavelet_tree&& wt);                        // TODO: @Tonko
        symbol_type operator[](lb::size_t index) const;         // TODO: @Tonko
        lb::interval node_rank(lb::size_t node, lb::interval range, bool bit = false) const;
        lb::size_t rank(lb::size_t index, symbol_type symbol) const;
        lb::size_t select(lb::size_t num, symbol_type symbol) const;   // TODO: @Tonko
        lb::size_t size() const;
        //void show() const;
    private:
        const lb::alphabet& a;
        lb::size_t sz;
        std::vector<bitvector> nodes;
    };

    using wtree = wavelet_tree;
}

#endif  // _WAVELET_TREE_HPP_