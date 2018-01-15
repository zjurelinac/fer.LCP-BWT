# LCP-BWT
_Computing the LCP array based on BWT_
[Bioinformatics course](http://www.fer.unizg.hr/predmet/bio) project at **FER, University of Zagreb**

## Installation
1. Clone this repo to your computer (`git clone https://github.com/zjurelinac/LCP_BWT`), or download it as a zip archive and unpack it.
2. Open terminal in the root directory of the project (`LCP-BWT`) and run `make`.
3. If everything proceeds without error, the executable program should be located at `build/lcp-bwt`.
4. If any errors occurred in the previous step, try changing the compiler (on the first line of the `Makefile`). All modern versions of GCC and Clang should be supported (compilation requires some advanced C++ features from recent standards (C++11 and C++14)).

## Usage
To run the program, type `./build/lcp-bwt input_file output_file`. The input should be in the **FASTA** format, with only **one sequence per file**.

## Testing
To run automatic tests, position yourself in the `tests` directory, and type `./test_runner.py` (This requires Python 3 to be installed on the computer).

To generate additional tests, type `./test_runner.py -g SIZE1[,SIZE2,...] [-p]`, which will generate random DNA (or protein, if `-p` flag is given) sequences of a given length. If the size of test case is less than 25000, it will also generate the expected output file (using brute-force algorithm).
