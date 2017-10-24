#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <sdsl/wavelet_trees.hpp>
#include "sais.hpp"

using namespace std;

string parse_input(char* input_file) {

}

void output_results(char* output_file, int* lcp_array, int N) {

}

int main(int argc, char* argv[]){
    int *SA = new int[13];
    string T = parse_input(argv[1]);
    string BWT;
    BWT.resize(T.size());

    saisxx((const char*) (T.c_str()), SA, (int) T.size());

    /*for (int i = 0; i < 6; ++i)
        cout << SA[i] << " " << T.substr(SA[i]) << "\n";
    cout << "\n";*/

    for (auto i = 0; i < T.size(); ++i)
        BWT[i] = SA[i] ? T[SA[i] - 1] : '$';

    cout << BWT << "\n";

    sdsl::wt_blcd<> wt;
    construct_im(wt, BWT, 1);

    for (size_t i=0; i < wt.size() and wt[i]!='\n'; ++i)
        cout << wt[i];
    cout << "\n";

    output_results(argv[1], );

    delete[] SA;
}