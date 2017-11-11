#include "wavelet_tree.hpp"

#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

#include "base.hpp"


static inline lb::size_t binary_rank(const lb::bitvector& bv, lb::bitvector::value_type bit, lb::size_t index) {
    return std::count(bv.begin(), bv.begin() + index, bit);
}

lb::wavelet_tree::wavelet_tree(const lb::sequence& in, const lb::alphabet& a) : a(a), sz(in.size()) {
    using subseq = std::pair<sequence::iterator, sequence::iterator>;
    using tmp_node = std::pair<alpha_interval, subseq>;

    sequence in_copy = in;
    std::queue<tmp_node> workspace;
    workspace.push(tmp_node(alpha_interval(0, a.size() - 1), subseq(in_copy.begin(), in_copy.end())));

    while (!workspace.empty()) {
        auto curr = workspace.front(); workspace.pop();
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
            workspace.push(tmp_node(alpha_interval(alpha.first, mid), subseq(range.first, bound)));
            workspace.push(tmp_node(alpha_interval(mid + 1, alpha.second), subseq(bound, range.second)));
        }
    }
}

lb::wavelet_tree::wavelet_tree(const wavelet_tree& wt) : a(wt.a), sz(wt.sz), nodes(wt.nodes) {}

lb::interval lb::wavelet_tree::node_rank(lb::size_t node, lb::interval range, bool bit) const {
    auto left = range.first > 0 ? binary_rank(nodes[node], bit, range.first) : 0;
    auto right = binary_rank(nodes[node], bit, range.second + 1);
    return interval(left, right);
}

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

lb::size_t lb::wavelet_tree::size() const {
    return sz;
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
