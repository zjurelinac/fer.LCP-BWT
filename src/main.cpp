#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "algorithms.hpp"

#ifndef USE_SDSL_WTREE
#include "wavelet_tree.hpp"
#endif

lb::sequence parse_input(const char* input_file);
void output_results(const char* output_file, lb::lcp_array& LCP);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: lcp_bwt input_file output_file\n";
        exit(1);
    }

    lb::sequence T = parse_input(argv[1]);
    lb::alphabet A {T};
    lb::sequence BWT = lb::build_bwt(T);
    lb::wtree WT = lb::build_wtree(BWT, A);
    lb::lcp_array LCP = lb::build_lcp(WT, A);

    output_results(argv[2], LCP);
}

lb::sequence parse_input(const char* input_file) {
    lb::sequence input, temp;
    std::ifstream file(input_file);

    if (!file) {
        std::cerr << "Unable to open file: " << input_file << " \n";
        exit(1);
    }

    std::getline(file, temp);  // first line
    while (!file.eof()) {
        std::getline(file, temp);
        input += temp;
    }
    file.close();
    return input + '$';
}

void output_results(const char* output_file, lb::lcp_array& lcp) {
    std::ofstream ofs(output_file);
    ofs << "[";
    for (auto i = 0u; i < lcp.size(); ++i)
        ofs << (int) lcp[i] << ((i != lcp.size() - 1) ? "," : "");
    ofs << "]\n";
    ofs.close();
}
