#ifndef _FAST_BITVECTOR_HPP_
#define _FAST_BITVECTOR_HPP_

#include <vector>

#include "base.hpp"

constexpr unsigned int clog2(unsigned int x) {
    auto l = 0u;
    for (; (1u << l) < x; ++l);
    return l;
}

constexpr unsigned int cmodmask(unsigned int x) {
    return (1 << clog2(x)) - 1;
}

template <int BLOCK_SIZE, typename base_type>
struct pc {
    static std::size_t popcount(base_type x) { return __builtin_popcount(x); };
};

template <typename base_type>
struct pc<64, base_type>{
    static std::size_t popcount(base_type x) { return __builtin_popcountll(x); }
};

template <typename T>
class bitvector {
public:
    using base_type = T;
    using block_index = unsigned char;

    const static std::size_t BLOCK_SIZE = 8 * sizeof(T);
    const static std::size_t LOG_BLOCK_SIZE = clog2(8 * sizeof(T));
    const static std::size_t MASK_BLOCK_SIZE = cmodmask(8 * sizeof(T));

    bitvector()
        : bi(0), sz(0) {}
    bitvector(const bitvector& bv)
        : store(bv.store), bi(bv.bi), sz(bv.sz) {}
    bitvector(bitvector&& bv)
        : store(std::move(bv.store)), bi(std::move(bv.bi)), sz(bv.sz) {}
    bool operator[](size_t index) const
        { return (store[index >> LOG_BLOCK_SIZE] & (1ULL << (index & MASK_BLOCK_SIZE))) != 0ULL; }
    std::size_t size() const
        { return sz; }
    base_type block(size_t block_index) const
        { return store[block_index]; }
    size_t block_count(size_t block_index) const
        { return pc<BLOCK_SIZE, base_type>::popcount(block(block_index)); }
    size_t block_count(size_t block_index, size_t bits) const
        { return pc<BLOCK_SIZE, base_type>::popcount(block(block_index) & ((1ULL << bits) - 1ULL)); }
    void push_back(const bool& val);

private:
    std::vector<base_type> store;
    block_index bi;
    std::size_t sz;
};


namespace lb {
    template<unsigned int bucket_size = 256>
    class fast_bitvector {
        using base_bitvector = bitvector<unsigned long long>;

        const static unsigned int BUCKET_SIZE = bucket_size;
        const static std::size_t LOG_BUCKET_SIZE = clog2(BUCKET_SIZE);
        const static std::size_t MASK_BUCKET_SIZE = cmodmask(BUCKET_SIZE);
    public:
        using value_type = bool;

        fast_bitvector()
            { cs.push_back(0); };
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
        base_bitvector bv;
    private:
        std::vector<size_t> cs;

        size_t count_bits(size_t start_pos, size_t count) const;
    };
#ifdef USE_FAST_BV
    using bitvector = fast_bitvector<>;
#endif
}

template <typename T>
void bitvector<T>::push_back(const bool& val) {
    if (!bi)
        store.push_back(0);
    store[store.size() - 1] |= ((base_type) val) << bi;
    bi = (bi + 1) & MASK_BLOCK_SIZE;
    ++sz;
}

template <unsigned int bucket_size>
inline lb::size_t lb::fast_bitvector<bucket_size>::count_bits(size_t start_pos, size_t count) const {
    lb::size_t result = 0;

    while (count >= base_bitvector::BLOCK_SIZE) {
        result += bv.block_count(start_pos >> base_bitvector::LOG_BLOCK_SIZE);
        start_pos += base_bitvector::BLOCK_SIZE;
        count -= base_bitvector::BLOCK_SIZE;
    }

    if (count > 0)
        result += bv.block_count(start_pos >> base_bitvector::LOG_BLOCK_SIZE, count);
    return result;
}

template <unsigned int bucket_size>
void lb::fast_bitvector<bucket_size>::push_back(const bool& val) {
	if (!(bv.size() & MASK_BUCKET_SIZE))
        cs.push_back(cs[cs.size() - 1] + val);
	else if (val)
	    ++cs[cs.size() - 1];
    bv.push_back(val);
}

template <unsigned int BUCKET_SIZE>
lb::size_t lb::fast_bitvector<BUCKET_SIZE>::rank(const lb::size_t index, const bool bit) const {
    size_t bucket = index >> LOG_BUCKET_SIZE;
    size_t base = bucket << LOG_BUCKET_SIZE;
    size_t sol = cs[bucket] + count_bits(base, index - base + 1);
    return bit ? sol : index - sol + 1;
}

#endif  // _FAST_BITVECTOR_HPP_
