//  -----------------------------------------------------------------------------
//  *****************************************************************************
//
//  Header declaring wavelet tree interface.
//  © 2017 All rights reserved.
//
//  *****************************************************************************
//  -----------------------------------------------------------------------------

#ifndef _WAVELET_TREE_HPP_
#define _WAVELET_TREE_HPP_

#include <vector>

#include "base.hpp"
#include "alphabet.hpp"

#ifdef USE_FAST_BV
#include "fast_bitvector.hpp"
#endif

namespace lb {
    class wavelet_tree {
    public:
        //
        //  Copy wavelet tree constructor.
        //
        //  @param wt - wavelet tree reference
        //
        //  Example:
        //      wavelet_tree wt1;
        //      wavelet_tree wt2(wt1);
        //
        wavelet_tree(const wavelet_tree& wt)
            : a(wt.a), sz(wt.sz), nodes(wt.nodes) {}

        //
        //  Move wavelet tree constructor.
        //
        //  @param wt - wavelet tree reference
        //
        //  Example:
        //      wavelet_tree wt1;
        //      wavelet_tree wt2(std::move(wt1));
        //
        wavelet_tree(wavelet_tree&& wt)
            : a(std::move(wt.a)), sz(std::move(wt.sz)), nodes(std::move(wt.nodes)) {}

        //
        //  Wavelet tree constructor from input sequence and alphabet.
        //
        //  @param in - input lb::sequence
        //  @param a - lb::alphabet
        //
        //  Example:
        //      lb::sequence s = "ACGCAT";
        //      lb::alphabet A {s};
        //      lb::wavelet_tree wt{s, A};
        //
        wavelet_tree(const lb::sequence& in, const lb::alphabet& a);

        //
        //  Operator[] override.
        //
        //  @param index
        //  @param symbol on given index in wavelet tree
        //
        symbol_type operator[](lb::size_t index) const;         // TODO: @Tonko

        //
        //  @return wavelet tree size
        //
        lb::size_t size() const
           { return sz; }

        //
        //  Returns node rank interval.
        //
        //  @param node
        //  @param range
        //  @param bit
        //  @return interval
        //
        lb::interval node_rank(lb::size_t node, lb::interval range, bool bit = false) const;
        lb::size_t rank(lb::size_t index, symbol_type symbol) const;
        lb::size_t select(lb::size_t num, symbol_type symbol) const;   // TODO: @Tonko
    private:
        const lb::alphabet& a;
        lb::size_t sz;
        std::vector<bitvector> nodes;
    };

    using wtree = wavelet_tree;
}

#endif  // _WAVELET_TREE_HPP_
