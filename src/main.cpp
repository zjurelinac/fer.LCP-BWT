#include <iostream>
#include <string>

#include "algorithms.hpp"

std::string parse_input(char* input_file);
void output_results(char* output_file, int* LCP, int N);

int main(int argc, char* argv[]) {
    lb::sequence T {"ananas$"};
    lb::sequence BWT = lb::build_bwt(T);
    lb::wtree WT = lb::build_wtree(BWT);

    for (auto i = 0u; i < T.size(); ++i)
        std::cout << WT[i];
    std::cout << "\n";
}