#include "../../src/include/containers.hpp"

#include <cstdio>

int main() {
    lb::fastqueue<int> fq;
    for (int i = 0; i < 50; ++i)
        fq.push(i);

    for (int i = 0; i < 50; ++i)
        printf("%d ", fq.pop());

    printf("\nempty? %d", fq.empty());
}