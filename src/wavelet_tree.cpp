#include "wavelet_tree.hpp"

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

#include "base.hpp"

lb::wavelet_tree::wavelet_tree(const lb::sequence& in, const lb::alphabet& a) {
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
        auto chr = a[mid];
        std::stable_partition(range.first, range.second, [chr](auto x){ return x <= chr; });
        auto bound = std::upper_bound(range.first, range.second, chr);

        bitvector bv(range.second - range.first, false);
        std::transform(range.first, range.second, bv.begin(), [chr](auto x){ return x > chr; });
        nodes.push_back(bv);

        if (alpha.second - alpha.first > 1) {
            workspace.push(tmp_node(alpha_interval(alpha.first, mid), subseq(range.first, bound)));
            workspace.push(tmp_node(alpha_interval(mid + 1, alpha.second), subseq(bound, range.second)));
        }
    }
}