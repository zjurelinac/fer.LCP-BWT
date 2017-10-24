#include "algorithms.hpp"

#include <sdsl/wavelet_trees.hpp>
#include "sais.hpp"

lb::sequence lb::build_bwt(lb::sequence in) {
    sequence bwt;
    int *sa = new int[in.size()];
    saisxx((const char*) (in.c_str()), sa, (int) in.size());

    bwt.resize(in.size());
    for (auto i = 0u; i < in.size(); ++i)
        bwt[i] = sa[i] ? in[sa[i] - 1] : '$';

    return bwt;
}

lb::wtree lb::build_wtree(lb::sequence bwt) {
    wtree wt;
    sdsl::construct_im(wt, bwt, 1);
    return wt;
}