#include <algorithm>
#include <map>
#include <queue>
#include <tuple>

#include "algorithms.hpp"
#include "sais.hpp"
#include "stack.hpp"

lb::sequence lb::build_bwt(const lb::sequence& in) {
    sequence bwt;
    int *sa = new int[in.size()];
    saisxx((const char*) (in.c_str()), sa, (int) in.size());

    bwt.resize(in.size());
    for (auto i = 0u; i < in.size(); ++i)
        bwt[i] = sa[i] ? in[sa[i] - 1] : '$';

    return bwt;
}

lb::wtree lb::build_wtree(const lb::sequence& bwt, const lb::alphabet &a) {
    wtree wt(bwt, a);
    return wt;
}

lb::intervals lb::get_intervals(const lb::interval& start, const lb::alphabet& a, const lb::wtree& wt) {
    using tmp_node = std::tuple<size_t, interval, alpha_interval>;
    intervals list;

    lb::smallstack<tmp_node> work_queue;
    work_queue.push(tmp_node(0, start, alpha_interval(0, a.size() - 1)));

    while (!work_queue.empty()) {
        auto curr = work_queue.pop();
        auto node = std::get<0>(curr);
        auto range = std::get<1>(curr);
        auto alpha = std::get<2>(curr);

        if (alpha.first == alpha.second) {
            auto C = a.csum(alpha.first);
            list.push_back(interval(C + range.first, C + range.second));
        } else {
            auto m = (alpha.first + alpha.second) / 2;
            auto ranks = wt.node_rank(node, range);

            auto a0 = ranks.first;
            auto b0 = ranks.second;
            auto a1 = range.first - a0;
            auto b1 = range.second + 1 - b0;

            if (b0 > a0)
                work_queue.push(tmp_node(2*node + 1, interval(a0, b0 - 1), alpha_interval(alpha.first, m)));
            if (b1 > a1)
                work_queue.push(tmp_node(2*node + 2, interval(a1, b1 - 1), alpha_interval(m + 1, alpha.second)));
        }
    }

    return list;
}

lb::lcp_array lb::build_lcp(const wtree& wt, const alphabet& a) {
    using tmp_state = std::pair<interval, size_t>;
    const int BOTTOM = -2;

    auto N = wt.size();
    lcp_array lcp(N + 1, BOTTOM);

    lcp[0] = lcp[N] = -1;

    std::queue<tmp_state> work_queue;
    work_queue.push(tmp_state(interval(0, N-1), 0));

    while (!work_queue.empty()) {
        auto curr = work_queue.front(); work_queue.pop();

        auto list = get_intervals(curr.first, a, wt);
        for (auto &intvl : list) {
            if (lcp[intvl.second + 1] == BOTTOM) {
                work_queue.push(tmp_state(intvl, curr.second + 1));
                lcp[intvl.second + 1] = curr.second;
            }
        }
    }

    return lcp;
}
