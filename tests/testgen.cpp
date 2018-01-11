#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const int max_line_size = 80;

std::string generate_input(const char* input_file, unsigned int N, bool protein_test = false);
void output_results(const char* output_file, std::vector<int> LCP);
int common_prefix(const char* a, const char* b);
std::vector<int> calc_lcp(std::string genome, unsigned int N);

int main(int argc, char* argv[]) {
    if(argc < 4) {
        std::cout << "Usage: testgen test_size input_file (output_file | --no-output) [--protein-test]\n";
        return -1;
    }
    // Should generate output - allows skipping bruteforce output generating for large cases
    bool gen_out = std::string(argv[3]) != "--no-output";
    bool protein_test = argc > 4 ? std::string(argv[4]) == "--protein-test" : false;

    // Generating random input file
    unsigned int N = atoi(argv[1]);
    std::string genome = generate_input(argv[2], N, protein_test);

    if (gen_out)
        // Generating expected output file
        output_results(argv[3], calc_lcp(genome, genome.size()));
}

int common_prefix(const char* a, const char* b) {
    int i = 0;
    while (*a != '\0' && *b != '\0' && *a == *b) {++a; ++b; ++i;}
    return i;
}

std::vector<int> calc_lcp(std::string genome, unsigned int N) {
    std::vector<int> sa(N, 0);
    for (auto i = 0u; i < N; ++i)
        sa[i] = i;

    std::sort(sa.begin(), sa.end(), [genome](auto i, auto j) {return genome.substr(i) < genome.substr(j);});

    std::vector<int> lcp(N + 1, -1);
    for (auto i = 1u; i < N; ++i)
        lcp[i] = common_prefix(genome.substr(sa[i]).c_str(), genome.substr(sa[i - 1]).c_str());

    return lcp;
}

std::string generate_input(const char* input_file, unsigned int N, bool protein_test) {
    std::ofstream ifs(input_file);
    std::string genome(N + 1, '\0');
    std::string alpha = protein_test ? "GALMFWKQESPVICYHRNDT" : "ACGT";

    srand(time(NULL));

    ifs << ">Ex. temere, " << (protein_test ? "aminoacid" : "genome") << " sequence length = " << N;
    for (auto i = 0; i < N; ++i) {
        if (i % max_line_size == 0)
            ifs << std::endl;
        ifs << (genome[i] = alpha[rand() % alpha.size()]);
    }
    ifs.close();

    genome[N] = '$';
    return genome;
}

void output_results(const char* output_file, std::vector<int> lcp) {
    std::ofstream ofs(output_file);
    ofs << "[";
    for (auto i = 0; i < lcp.size(); ++i)
        ofs << lcp[i] << ((i != lcp.size() - 1) ? "," : "");
    ofs << "]\n";
    ofs.close();
}