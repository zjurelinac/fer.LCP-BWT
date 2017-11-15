#ifndef _FAST_BITVECTOR_HPP_
#define _FAST_BITVECTOR_HPP_

#include <vector>
#include <iterator>

#include "base.hpp"

//#define BUCKET_SIZE 256
//#define LOG_BUCKET_SIZE 8

#define popcount __builtin_popcount
#define endian_convert __builtin_bswap32

constexpr unsigned int ilog2(unsigned int x) {
    auto l = 0u;
    for (; (1u << l) < x; ++l);
    return l;
}

template <typename T>
class bitvector {
public:
    using base_type = T;
    using block_index = unsigned char;

    const static std::size_t BLOCK_SIZE = sizeof(T);
    const static std::size_t LOG_BLOCK_SIZE = ilog2(sizeof(T));

    bitvector()
        : bi(0) {}
    bitvector(const bitvector& bv)
        : store(bv.store), bi(bv.bi) {}
    bitvector(bitvector&& bv)
        : store(std::move(bv.store)), bi(std::move(bv.bi)) {}
    bool operator[](size_t index) const
        { return (store[index / BLOCK_SIZE] & (1 << (index % BLOCK_SIZE))) != 0; }
    std::size_t size() const
        { return (store.size() ? store.size() - 1 : 0) * BLOCK_SIZE + bi; }
    base_type get_block(size_t block_index) const
        { return store[block_index]; }
    void push_back(const bool& val);
private:
    std::vector<base_type> store;
    block_index bi;
};


namespace lb {
    template<unsigned int BUCKET_SIZE = 256>
    class fast_bitvector {
        using base_bitvector = bitvector<unsigned int>;

        const static std::size_t LOG_BUCKET_SIZE = ilog2(BUCKET_SIZE);
    public:
        using value_type = bool;

        fast_bitvector() {};

        fast_bitvector(const fast_bitvector& fbv)
            : bv(fbv.bv), cs(fbv.cs) {}
        fast_bitvector(fast_bitvector&& fbv)
            : bv(std::move(fbv.bv)), cs(std::move(fbv.cs)) {}
        bool operator[](size_t index) const
            { return bv[index]; }
        size_t size() const
            { return bv.size(); }
        size_t rank(size_t index, bool bit = true) const;

        void push_back(const bool& val);
    private:
        base_bitvector bv;
        std::vector<size_t> cs;

        size_t count_bits(size_t start, size_t count) const;
    };
#ifdef USE_FAST_BV
    using bitvector = fast_bitvector<>;
#endif
}

template <typename T>
void bitvector<T>::push_back(const bool& val) {
    if (!bi)
        store.push_back(0);
    store[store.size() - 1] |= val << bi;
    bi = (bi + 1) % BLOCK_SIZE;
}

template <unsigned int BUCKET_SIZE>
inline lb::size_t lb::fast_bitvector<BUCKET_SIZE>::count_bits(size_t start, size_t count) const {
    lb::size_t result = 0;


    /*while (count > base_bitvector::BLOCK_SIZE) {
        result += popcount(*start);
        start += sizeof(bit_block);
        count -= base_bitvector::BLOCK_SIZE;
    }

    bit_block block = *start;

    //#ifdef LITTLE_ENDIAN
    block = endian_convert(block);
    //#endif

    result += popcount(block >> (base_bitvector::LOG_BLOCK_SIZE - count));*/
    return 0;
}

template <unsigned int BUCKET_SIZE>
void lb::fast_bitvector<BUCKET_SIZE>::push_back(const bool& val) {
	if (bv.size() % BUCKET_SIZE == 0)
	    cs.push_back(cs.size() ? cs[cs.size() - 1] : 0);
	if (val)
	    ++cs[cs.size() - 1];
    bv.push_back(val);
}

template <unsigned int BUCKET_SIZE>
lb::size_t lb::fast_bitvector<BUCKET_SIZE>::rank(const lb::size_t index, const bool bit) const {
    size_t bucket = index >> LOG_BUCKET_SIZE;
    size_t base = bucket ? (bucket - 1) << LOG_BUCKET_SIZE : 0;
    printf("Counting %d bits from %d (bucket %d)\n", index - base, base, bucket - 1);
    size_t sol = (bucket > 0 ? cs[bucket - 1] : 0) + count_bits((bit_ptr) &cs[base], index - base);
    return bit ? sol : index - sol + 1;
}

#endif  // _FAST_BITVECTOR_HPP_
