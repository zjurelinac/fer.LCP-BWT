#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const int max_line_size = 80;

int common_prefix(const char* a, const char* b);
void output_results(char* output_file, std::vector<int> LCP);

int main(int argc, char* argv[]) {
    if(argc != 4) {
        std::cout << "Wrong number of parameters\n"
        "Usage: ./testgen test_size input_file output_file\n";
        return -1;
    }

    // Generating random input file
    int N = atoi(argv[1]);
    char alpha[] = "ACGT";
    std::string genome;
    genome.resize(N + 1);
    genome[N] = '$';
    
    std::ofstream ifs(argv[2], std::ofstream::out);    
    
    ifs << ">Ex. temere, genome length = " << N;

    srand(time(NULL));
    for (auto i = 0; i < N; ++i) {
        if (i % max_line_size == 0)
            ifs << std::endl;
        ifs << (genome[i] = alpha[rand() % 4]);
    }
    
    ifs.close();

    // Generating expected output file
    std::vector<int> sa;
    for (auto i = 0; i < N + 1; ++i)
        sa.push_back(i);

    std::sort(sa.begin(), sa.end(), [genome](auto i, auto j) {return genome.substr(i) < genome.substr(j);});

    std::vector<int> lcp;
    lcp.push_back(-1);
    for (auto i = 1; i < N + 1; ++i)
        lcp.push_back(common_prefix(genome.substr(sa[i]).c_str(), genome.substr(sa[i - 1]).c_str()));
    
    output_results(argv[3], lcp);
}

int common_prefix(const char* a, const char* b) {
    int i = 0;
    while (*a != '\0' && *b != '\0' && *a == *b) {++a; ++b; ++i;}
    return i;
}

void output_results(char* output_file, std::vector<int> lcp) {
    std::ofstream ofs(output_file, std::ofstream::out);
    ofs << "[";
    for (auto i = 0; i < lcp.size(); ++i)
        ofs << lcp[i] << ((i != lcp.size() - 1) ? "," : "");
    ofs << "]\n";
    ofs.close();
}