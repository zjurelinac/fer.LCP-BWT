#include "base.hpp"

#define SMALLSTACK_SIZE 32

namespace lb {
    template <typename T>
    class smallstack {
    public:
        using base_type = T;

        smallstack()
            : pos(-1) {}
        void push(T elem)
            { stack[++pos] = elem; }
        T pop()
            { return stack[pos--]; }
        bool empty() const
            { return pos == -1; }
    private:
        T stack[SMALLSTACK_SIZE];
        int pos;
    };
}