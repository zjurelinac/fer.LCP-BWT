//  -----------------------------------------------------------------------------
//  *****************************************************************************
//
//  Main program file implementing computation of LCP array based on
//  the Burrows-Wheeler transform.
//  © 2017 All rights reserved.
//
//  *****************************************************************************
//  -----------------------------------------------------------------------------

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

//  
//  Function that parses input file into lb::sequence.
//  
//  @param input_file - input file name
//  @return parsed input file without first line + '$' on the end
//  
//  Example:
//      char* file_name{"data.txt"};
//      lb::sequence s = parse_input(file_name);
//
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

//  
//  Function that ouputs computed LCP array to file.
//  
//  @param output_file - output file name
//  @param lcp - array that will be written to file
//  
//  Example:
//      char* file_name{"output.txt"};
//      lb::lcp:array array{1, 2, 5, 3, 12, 9};
//      output_results(file_name, array);  //  file contains "[1,2,5,3,12,9]"
//
void output_results(const char* output_file, lb::lcp_array& lcp) {
    std::ofstream ofs(output_file);
    ofs << "[";
    for (auto i = 0u; i < lcp.size(); ++i)
        ofs << (int) lcp[i] << ((i != lcp.size() - 1) ? "," : "");
    ofs << "]\n";
    ofs.close();
}
