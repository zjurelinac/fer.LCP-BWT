#include <map>

#include "algorithms.hpp"
#include "sais.hpp"

// lb::charnum lb::calculate_char_csum(const lb::sequence& in) {
//     charnum csum;
//     std::map<sequence::value_type, int> cnt;

//     for (auto& c : in) ++cnt[c];

//     int last = 0;
//     for (auto& it : cnt) {
//         csum[it.first] = last;
//         last += it.second;
//     }

//     return csum;
// }
static void _get_intervals(lb::interval, lb::alpha_interval, lb::intervals&, lb::alphabet&, lb::wtree&);

lb::sequence lb::build_bwt(const lb::sequence& in) {
    sequence bwt;
    int *sa = new int[in.size()];
    saisxx((const char*) (in.c_str()), sa, (int) in.size());

    bwt.resize(in.size());
    for (auto i = 0u; i < in.size(); ++i)
        bwt[i] = sa[i] ? in[sa[i] - 1] : '$';

    return bwt;
}

lb::wtree lb::build_wtree(const lb::sequence& bwt) {
    wtree wt;
    sdsl::construct_im(wt, bwt, 1);
    return wt;
}

lb::intervals lb::get_intervals(lb::interval start, lb::alphabet& a, lb::wtree& wtree) {
    intervals list;
    _get_intervals(start, alpha_interval(0, a.size() - 1), list, a, wtree);
    return list;
}

static void _get_intervals(lb::interval start, lb::alpha_interval alpha, lb::intervals& list, lb::alphabet& a, lb::wtree& wtree) {
    if (alpha.first == alpha.second) {
        //auto C = cumsum[a[ialpha.first]]; // !?!
        //list.push_back(lb::interval(C + start.first, C + start.second));
    } else {

    }
}