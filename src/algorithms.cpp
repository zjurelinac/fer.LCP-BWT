#include <map>

#include "sais.hpp"
#include "algorithms.hpp"


static void get_intervals_(lb::interval start, lb::alpha_interval alpha, lb::intervals& list, const lb::alphabet& a, const lb::wtree& wtree) {
    if (alpha.first == alpha.second) {
        auto C = a.csum(alpha.first);
        list.push_back(lb::interval(C + start.first, C + start.second));
    } else {

    }
}

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

#else

lb::wtree lb::build_wtree(const lb::sequence& bwt, const lb::alphabet &a) {
    wtree wt(bwt, a);
    return wt;
}

#endif

lb::intervals lb::get_intervals(lb::interval start, const lb::alphabet& a, const lb::wtree& wt) {
    intervals list;
    get_intervals_(start, alpha_interval(0, a.size() - 1), list, a, wt);
    return list;
}

lb::lcp_array lb::build_lcp(const wtree& wt) {
    lcp_array lcp(wt.size(), -1);
    // TODO: @Zivec

    return lcp;
}
