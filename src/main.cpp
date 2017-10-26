#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "algorithms.hpp"

std::string parse_input(char* input_file);
void output_results(char* output_file, std::vector<int> LCP);

int main(int argc, char* argv[]) {
    lb::sequence T {"ananas$"};
    lb::alphabet A {T};
    lb::sequence BWT = lb::build_bwt(T);
    lb::wtree WT = lb::build_wtree(BWT, A);

    for (int i = 0; i < A.size(); ++i)
        std::cout << A[i] << " " << A.csum(i) << "\n";
    std::cout << "\n";

    for (auto i = 0u; i < T.size(); ++i)
        std::cout << WT[i];
    std::cout << "\n";
}

void output_results(char* output_file, std::vector<int> LCP) {
    std::ofstream ofs(output_file, std::ofstream::out);
    ofs << "[";
    for (auto& x : LCP)
        ofs << x << ',';
    ofs << "]\n";
    ofs.close();
}