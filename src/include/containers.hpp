#include "base.hpp"

#include <list>
#include <utility>

#define SMALLSTACK_SIZE 32
#define FASTQUEUE_OPT_SIZE 4096
#define FASTQUEUE_START_SIZE 32

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
            : front(0), back(0), size(0) {}
        inline void push(T elem);

        inline T pop();

        bool empty() const
            { return size == 0; }
    private:
        size_t new_block_size()
            { return size ? 16 : FASTQUEUE_START_SIZE; }
        void add_block(size_t size)
            { printf("Adding block of size %u\n", size); list.emplace_front(new T[size], size); front = size; }
        void remove_block()
            { printf("Removing block of size %u\n", list.back().second); delete[] list.back().first; list.pop_back(); back = list.back().second; }
        size_t front, back, size;
        std::list<block_type> list;
    };
}

template <typename T>
void lb::fastqueue<T>::push(T elem) {
    if (size == 0 || front == 0)
        add_block(new_block_size());
    if (!size)
        back = FASTQUEUE_START_SIZE;
    (list.front().first)[--front] = elem;
    ++size;
}

template <typename T>
T lb::fastqueue<T>::pop() {
    if (back == 0)
        remove_block();
    --size;
    return (list.back().first)[--back];
}
