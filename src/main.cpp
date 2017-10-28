#include <fstream>
#include <iostream>
#include <string>

#include "algorithms.hpp"

#ifndef USE_SDSL_WTREE
#include "wavelet_tree.hpp"
#endif

std::string parse_input(char* input_file);
void output_results(char* output_file, lb::lcp_array& LCP);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: lcp_bwt input_file output_file\n";
        exit(1);
    }

    lb::sequence T {"ananas$"};
    lb::alphabet A {T};
    lb::sequence BWT = lb::build_bwt(T);

    std::cout << BWT << "\n";

    lb::wtree WT = lb::build_wtree(BWT, A);
    lb::lcp_array LCP = lb::build_lcp(WT);
    output_results(argv[2], LCP);
}

std::string parse_input(char* input_file) {
    std::string input, temp;
    std::ifstream file(input_file);

    if (!file) {
        std::cerr << "Unable to open file\n";
        exit(1);
    }

    std::getline(file, temp);  // first line
    while (!file.eof()) {
        std::getline(file, temp);
        input += temp;
    }
    file.close();
    return input;
}

void output_results(char* output_file, lb::lcp_array& lcp) {
    std::ofstream ofs(output_file, std::ofstream::out);
    ofs << "[";
    for (auto i = 0u; i < lcp.size(); ++i)
        ofs << lcp[i] << ((i != lcp.size() - 1) ? "," : "");
    ofs << "]\n";
    ofs.close();
}
