#include "base.hpp"

#include <list>
#include <utility>

#define SMALLSTACK_SIZE 32

namespace lb {
    template <typename T>
    class smallstack {
    public:
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

    template <typename T>
    class fastqueue {
        using block_type = std::pair<T*, lb::size_t>;
    public:
        fastqueue()
            : front(), back() {}
        void push(T elem)
            { if (front) ; }
        T pop(T elem)
            {  }
        bool empty() const;
    private:
        size_t pick_size()
            { return 20; }
        void add_block()
            { auto size = pick_size(); list.emplace_back(new T[size], size); back = 0; }
        void remove_block()
            { list.pop_front(); front = 0; }
        size_t front, back;
        std::list<block_type> list;
    };
}