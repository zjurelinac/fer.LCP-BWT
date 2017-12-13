//  -----------------------------------------------------------------------------
//  *****************************************************************************
//
//  Implementation of algorithms to compute LCP with BWT transform.
//  © 2017 All rights reserved.
//
//  *****************************************************************************
//  -----------------------------------------------------------------------------

#include <algorithm>
#include <map>
#include <queue>
#include <tuple>

#include "algorithms.hpp"
#include "containers.hpp"
#include "sais.hpp"

//  
//  Function that transforms input sequence into BWT sequence.
//  
//  BWT[i] = S[SA[i] - 1]   , for SA[i] != 1
//  BWT[i] = '$'            , otherwise
//  
//  @param in - S[1..n]
//  @return BWT[1..n]
//  
//  Example:
//      lb::sequence S = "ACGCAT$";
//      lb::sequence bwt_s = lb::build_bwt(S);  // bwt_s = "T$CGACA";
//
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

//  
//  Function implements Algorithm 1 from
//  http://www.sciencedirect.com/science/article/pii/S1570866712001104#fg0040
//  
//  For an ω-interval [i..j], the function call getIntervals([i..j]) returns 
//  the list of all cω-intervals. 
//
//  For further details check website.
//  
//  @param start - ω-interval
//  @param a - alphabet
//  @param wt - wavelet tree
//  @return list of all cω-intervals
//  
//  Example:
//      lb::sequence S = "ACGCAT$";
//      lb::alphabet A{S};
//      lb::sequence bwt_s = lb::build_bwt(S);
//      lb::wtree wt = lb::build_wtree(bwt_s, A);
//      lb::interval interval(0, S.size() -1);
//      lb::inervals intervals = lb::get_intervals(interval, A, wt);
//
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

//  
//  Function implements Algorithm 2 from
//  http://www.sciencedirect.com/science/article/pii/S1570866712001104#fg0040
//  
//  Algorithm 2 computes LCP-array in O(nlog σ) time. 
//  It uses only the wavelet tree of the BWT of S, a queue to store the ω-intervals and the LCP-array.
//
//  For further details check website.
//  
//  @param wt - wavelet tree
//  @param a - alphabet
//  @return LCP array
//  
//  Example:
//      lb::sequence S = "ACGCAT$";
//      lb::alphabet A{S};
//      lb::sequence bwt_s = lb::build_bwt(S);
//      lb::wtree wt = lb::build_wtree(bwt_s, A);
//      lb::lcp_array LCP = lb::build_lcp(wt, A);
//
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
