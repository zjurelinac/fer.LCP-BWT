#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "algorithms.hpp"

#ifndef USE_SDSL_WTREE
#include "wavelet_tree.hpp"
#endif

std::string parse_input(char* input_file);
void output_results(char* output_file, std::vector<int> LCP);

int main(int argc, char* argv[]) {
    lb::sequence T {"ananas$"};
    lb::alphabet A {T};

    for (auto i = 0; i < A.size(); ++i)
        std::cout << A[i];
    std::cout << "\n";

    lb::sequence BWT = lb::build_bwt(T);

    std::cout << BWT << "\n";

    lb::wtree WT = lb::build_wtree(BWT, A);
}

void output_results(char* output_file, std::vector<int> LCP) {
    std::ofstream ofs(output_file, std::ofstream::out);
    ofs << "[";
    for (auto& x : LCP)
        ofs << x << ',';
    ofs << "]\n";
    ofs.close();
}