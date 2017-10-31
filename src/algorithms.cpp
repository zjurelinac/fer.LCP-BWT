#include <map>
#include <queue>
#include <tuple>

#include "sais.hpp"
#include "algorithms.hpp"


lb::sequence lb::build_bwt(const lb::sequence& in) {
    sequence bwt;
    int *sa = new int[in.size()];
    saisxx((const char*) (in.c_str()), sa, (int) in.size());

    bwt.resize(in.size());
    for (auto i = 0u; i < in.size(); ++i)
        bwt[i] = sa[i] ? in[sa[i] - 1] : '$';

    return bwt;
}

#ifdef USE_SDSL_WTREE

lb::wtree lb::build_wtree(const lb::sequence& bwt, const lb::alphabet &a) {
    wtree wt;
    sdsl::construct_im(wt, bwt, 1);
    return wt;
}

static lb::interval range_rank(lb::interval range, lb::alpha_interval alpha, const lb::alphabet& a, const lb::wtree& wt) {
    lb::interval ranks = {0, 0};
    std::size_t k;
    std::vector<unsigned char> symbols(a.size());
    std::vector<std::size_t> i_ranks(a.size()), j_ranks(a.size());
    wt.interval_symbols(range.first, range.second + 1, k, symbols, i_ranks, j_ranks);

    std::cout << "\tRanging [" << alpha << "] " << range << ":" << "\n\t\t" << symbols << "\t\t" << i_ranks << "\t\t" << j_ranks;

    for (auto i = 0u; i < k; ++i) {
        auto c = a[(lb::symbol_type) symbols[i]];
        if (c >= alpha.first && c <= alpha.second) {
            ranks.first += i_ranks[i];
            ranks.second += j_ranks[i];
        }
    }

    return ranks;
}

lb::intervals lb::get_intervals(lb::interval start, const lb::alphabet& a, const lb::wtree& wt) {
    using tmp_node = std::pair<interval, alpha_interval>;
    intervals list;

    std::queue<tmp_node> workspace;
    workspace.push(tmp_node(start, alpha_interval(0, a.size() - 1)));

    while (!workspace.empty()) {
        auto curr = workspace.front(); workspace.pop();
        auto range = curr.first;
        auto alpha = curr.second;

        std::cout << "Investigating node " << curr << "; list so far: " << list;

        if (alpha.first == alpha.second) {
            auto C = a.csum(alpha.first);
            std::cout << "Found interval cw (c = " << a[(lb::size_t)alpha.first] << "): " << interval(C + range.first, C + range.second) << "\n";
            list.push_back(interval(C + range.first, C + range.second));
        } else {
            auto m = (alpha.first + alpha.second) / 2;
            auto ranks = range_rank(range, alpha_interval(alpha.first, m), a, wt);

            auto a0 = ranks.first;
            auto b0 = ranks.second;
            auto a1 = range.first - a0;
            auto b1 = range.second + 1 - b0;

            std::cout << "\tCounts: " << a0 << " " << b0 << ", " << a1 << " " << b1 << "\n";

            if (b0 > a0)
                workspace.push(tmp_node(interval(a0, b0 - 1), alpha_interval(alpha.first, m)));
            if (b1 > a1)
                workspace.push(tmp_node(interval(a1, b1 - 1), alpha_interval(m + 1, alpha.second)));
        }
    }

    return list;
}

#else

lb::wtree lb::build_wtree(const lb::sequence& bwt, const lb::alphabet &a) {
    wtree wt(bwt, a);
    return wt;
}

lb::intervals lb::get_intervals(lb::interval start, const lb::alphabet& a, const lb::wtree& wt) {
    using tmp_node = std::tuple<size_t, interval, alpha_interval>;
    intervals list;

    std::queue<tmp_node> workspace;
    workspace.push(tmp_node(0, start, alpha_interval(0, a.size() - 1)));

    while (!workspace.empty()) {
        auto curr = workspace.front(); workspace.pop();
        auto node = std::get<0>(curr);
        auto range = std::get<1>(curr);
        auto alpha = std::get<2>(curr);

        std::cout << "Investigating node " << curr << "; list so far: " << list;

        if (alpha.first == alpha.second) {
            auto C = a.csum(alpha.first);
            std::cout << "Found interval cw (c = " << a[(lb::size_t)alpha.first] << "): " << interval(C + range.first, C + range.second) << "\n";
            list.push_back(interval(C + range.first, C + range.second));
        } else {
            auto m = (alpha.first + alpha.second) / 2;
            auto ranks = wt.node_rank(node, range);

            auto a0 = ranks.first;
            auto b0 = ranks.second;
            auto a1 = range.first - a0;
            auto b1 = range.second + 1 - b0;

            std::cout << "\tCounts: " << a0 << " " << b0 << ", " << a1 << " " << b1 << "\n";

            if (b0 > a0)
                workspace.push(tmp_node(2*node + 1, interval(a0, b0 - 1), alpha_interval(alpha.first, m)));
            if (b1 > a1)
                workspace.push(tmp_node(2*node + 2, interval(a1, b1 - 1), alpha_interval(m + 1, alpha.second)));
        }
    }

    return list;
}

#endif

lb::lcp_array lb::build_lcp(const wtree& wt) {
    const int size = wt.size();
    lcp_array lcp(size, -10);
    // TODO: @Zivec
    lb::alphabet alphabet = lb::alphabet();
    lcp[0] = -1;
    lcp[size] = -1;
    queue<pair<intervals, int>> queue;
    queue.push(make_pair(make_pair(1, size), 0));

    while(!queue.empty()){
        auto dequeue_element = queue.front();
        queue.pop();
        intervals list = get_intervals(dequeue_element.first(), alphabet, wt);
        for(auto interval : list){
            if(lcp[interval.second()] == -10){
                queue.push(make_pair(interval, dequeue_element.second()+1);
                lcp[interval.second()+1] = dequeue_element.second();
            }
        }
    }
    return lcp;
}
