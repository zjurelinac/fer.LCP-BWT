//  -----------------------------------------------------------------------------
//  *****************************************************************************
//
//  Wavelet tree implementation
//  © 2017 All rights reserved.
//
//  *****************************************************************************
//  -----------------------------------------------------------------------------

#include "wavelet_tree.hpp"

#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

#include "base.hpp"

//
// Binary rank wrapper function.
//
// Returns the number of bits equal to `bit` within the first `index` places of bitvector
//  (ie. in range [0, index-1]). Actual function that is called depends on the type of
//  the bitvector used (it's own rank for a fast_bitvector, or a generic std::count for
//  std::vector<bool>).
//
// @param bv    - Const bitvector reference
// @param bit   - Bit value whose rank is searched (true or false)
// @param index - Search interval bound (interval = [0, index-1])
//
// Complexity: depends of actual bitvector type used, either linear or constant
//
// Example:
//      lb::bitvector bv;                       // Contains, say: 1 0 0 1 1 1 1 0
//      auto rank = binary_rank(bv, true, 4);   // rank = No. of 1s in [1 0 0 1] 1 1 1 0 = 2
//                                                                      ~~~~~~~
//
#ifdef USE_FAST_BV
static inline lb::size_t binary_rank(const lb::bitvector& bv, lb::bitvector::value_type bit, lb::size_t index) {
    return index ? bv.rank(index - 1, bit) : 0;
}
#else
static inline lb::size_t binary_rank(const lb::bitvector& bv, lb::bitvector::value_type bit, lb::size_t index) {
    return std::count(bv.begin(), bv.begin() + index, bit);
}
#endif

//
// Wavelet tree constructor from an input sequence and it's alphabet.
//
// @param in    - Input sequence whose wavelet tree is being built
// @param a     - Alphabet of symbols comprising the input sequence
//
// Complexity: O(n log σ) - linearithmic
//
// Example:
//      lb::sequence in = "T$ACGA";
//      lb::alphabet a(in);
//      lb::wavelet_tree wt(in, a);     <- Constructor call
//
lb::wavelet_tree::wavelet_tree(const lb::sequence& in, const lb::alphabet& a) : a(a), sz(in.size()) {
    using subseq = std::pair<sequence::iterator, sequence::iterator>;
    using tmp_node = std::pair<alpha_interval, subseq>;

    sequence in_copy = in;
    std::queue<tmp_node> work_queue;
    work_queue.push(tmp_node(alpha_interval(0, a.size() - 1), subseq(in_copy.begin(), in_copy.end())));

    while (!work_queue.empty()) {
        auto curr = work_queue.front(); work_queue.pop();
        auto alpha = curr.first;
        auto range = curr.second;

        auto mid = (alpha.first + alpha.second) / 2;
        auto chr = a[(lb::size_t) mid];

        bitvector bv;
        for (auto it = range.first; it != range.second; ++it)
            bv.push_back(*it > chr);

        std::stable_partition(range.first, range.second, [chr](auto x){ return x <= chr; });
        auto bound = std::upper_bound(range.first, range.second, chr);
        nodes.push_back(bv);

        if (alpha.second - alpha.first > 1) {
            work_queue.push(tmp_node(alpha_interval(alpha.first, mid), subseq(range.first, bound)));
            work_queue.push(tmp_node(alpha_interval(mid + 1, alpha.second), subseq(bound, range.second)));
        }
    }
}

// 
// Internal node binary-rank query
//
// Returns the number of occurences of `bit` in a given range of the wavelet-tree node's bitvector.
//  Method is used internally in the `get_intervals` algorithm. More precisely, it returns both the
//  number of `bit`'s in interval [0, range.start-1] and the number of `bit`'s in [0, range.end]
//  -> the difference between the two gives the actual result. 
//
// @param node      - Wavelet-tree internal node's index
// @param range     - Search range
// @param bit       - Bit value that is searched, true | false
//
// Complexity: O(C) - constant
// 
// Example:
//      lb::sequence in = "s$nnaaa";
//      lb::alphabet a(in);
//      lb::wavelet_tree wt(in, a);
//
//          // Wavelet tree looks like this:
//          //
//          //               0
//          //            s$nnaaa
//          //         /           \ 
//          //        1             2
//          //      $aaa           snn
//          //    /      \       /     \ 
//          //   3        4     5       6
//          //   $       aaa   nn       s 
//
//      auto res = wt.node_rank(1, interval(1, 2), true);   // res = [1-rank(wt.nodes[node].bv, [0, 0]), 1-rank(wt.nodes[node].bv, [0, 2])]
//          // res <= [0, 2]
//
lb::interval lb::wavelet_tree::node_rank(lb::size_t node, lb::interval range, bool bit) const {
    auto left = range.first > 0 ? binary_rank(nodes[node], bit, range.first) : 0;
    auto right = binary_rank(nodes[node], bit, range.second + 1);
    return interval(left, right);
}

//
// Wavelet tree rank query
//
// Returns the number of occurences of a given symbol up to the `index`-th place (excluded) in the 
//  input string upon which the wavelet tree was built.
//
// @param index     - Rank query boundary - method will return `symbol`-rank of [0, index-1] interval
// @param symbol    - Alphabet symbol whose rank is searched
//
// Complexity: O(log σ) - logarithmic
//
// Example:
//      lb::sequence in = "ananas$";
//      lb::alphabet a(in);
//      lb::wavelet_tree wt(in, a);
//      auto num_a = wt.rank(3, 'a');   // num_a = number of 'a' symbols
//          // num_a <= 2 
//
lb::size_t lb::wavelet_tree::rank(lb::size_t index, lb::symbol_type symbol) const {
    const int N = nodes.size();
    int curr = 0, symbol_index = a[(symbol_type)symbol];

    alpha_interval alpha = alpha_interval(0, a.size() - 1);
    while (curr < N) {
        auto mid = (alpha.first + alpha.second) / 2;
        bitvector::value_type bit = symbol_index > mid;
        index = binary_rank(nodes[curr], bit, index);
        if (!bit) {
            curr = 2*curr + 1;
            alpha = alpha_interval(alpha.first, mid);
        } else {
            curr = 2*curr + 2;
            alpha = alpha_interval(mid + 1, alpha.second);
        }
    }

    return index;
}

/*static std::string indent(int n) {
    std::string s = "";
    for (auto i = 0; i < n; ++i )
        s += " ";
    return s;
}

void lb::wavelet_tree::show() const {
    using nd = std::pair<unsigned int, unsigned int>;
    std::queue<nd> Q;
    Q.push(nd(0, 0));
    while (!Q.empty()) {
        nd c = Q.front(); Q.pop();
        if (c.first < nodes.size()) {
            Q.push(nd(2*c.first + 1, c.second + 1));
            Q.push(nd(2*c.first + 2, c.second + 1));
            std::cout << "[" << c.first << "]:" << indent(c.second * 2) << " " << nodes[c.first];
        }
    }
}*/
