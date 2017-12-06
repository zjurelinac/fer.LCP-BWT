#include "../../src/include/containers.hpp"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>

using par = std::pair<int, int>;

int main() {
    //lb::fastqueue<par> fq;
    //std::queue<par> q;

    lb::fastqueue<int> fq;
    std::queue<int> q;

    srand(1);

    /*for (int i = 0; i < 10000; ++i) {
        int x = rand() % 100;
        fq.push(par(x, 1));
        q.push(par(x, 1));
    }

    for (int i = 0; i < 10000; ++i) {
        auto x = fq.pop(), y = q.front(); q.pop();
        if (x.first != y.first) 
            printf("ERROR: items differ at %d: %d <> %d\n", i, x.first, y.first);
    }*/
    const int N = 100;

    for (int i = 0; i < N; ++i) {
        auto op = rand() % 2 == 0;
        if (q.empty() != fq.empty())
            printf("ERROR: empty difference: %d <> %d\n", q.empty(), fq.empty());
        if (op) { // push
            int x = rand() % 100;
            printf("%d :: Pushing %d\n", i, x);
            q.push(x); fq.push(x);
        } else { // pop
            if (!q.empty()) {
                auto x = fq.pop(), y = q.front(); q.pop();
                if (x != y)
                    printf("ERROR: pop difference: %d <> %d\n", x, y);
                else
                    printf("%d :: Popping %d\n", i, x);
            }
        }
    }

    /*for (int i = 0; i < 50; ++i)
        fq.push(i);

    for (int i = 0; i < 50; ++i)
        std::cout << fq.pop() << " ";

    std::cout << "\nempty? " << fq.empty() << std::endl;*/
}