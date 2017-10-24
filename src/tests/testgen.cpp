#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int lineSize = 80;

std::string parse_input(char* input_file);


void output_results(char* output_file, int* LCP, int N)
{
    ofstream outputFile;
    outputFile.open (output_file);
    outputFile << "LCP result\n";

    for (auto i = 0; i < N; ++i)
        outputFile << LCP[i] << " ";
    outputFile << "\n";
    outputFile.close();
}

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        std::cout << "Wrong number of parameters\n"  
        "Usage: ./testgen num in_file out_file\n";
        return -1;
    }

    ofstream inFile;
    //ofstream outFile;

    inFile.open (argv[2]);
    //outFile.open (argv[3]);

    if(inFile.fail() )//|| outFile.fail())
    {
        std::cout << "Files failed to open correctly" << std::endl;
        return -1;
    }

    int seqLen(atoi(argv[1]));
    int currentLen(0);
    int genNum;

    srand(time(NULL));

    inFile << ">E.coli test case length " << seqLen << std::endl;

    while(currentLen < seqLen)
    {
        genNum = rand() % 4 + 1;

        switch (genNum){
            case 1: inFile << "A";
                break;
            case 2: inFile << "T";
                break;
            case 3: inFile << "G";
                break;      
            case 4: inFile << "C";
                break;
        }
        ++currentLen;
        if(currentLen % lineSize == 0)
            inFile << std::endl;
    }
    inFile.close();
    //outFile.close();

}