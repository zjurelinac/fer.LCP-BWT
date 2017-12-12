#ifndef _ALPHABET_HPP_
#define _ALPHABET_HPP_

#include <cstring>
#include <map>

#include "base.hpp"

//  -----------------------------------------------------------------------------
//  *****************************************************************************
//
//  Header defining alphabet class used to map input symbols.
//  © 2017 All rights reserved.
//
//  *****************************************************************************
//  -----------------------------------------------------------------------------
namespace lb {
    class alphabet {
    public:
    
        //  
        //  Default alphabet constructor.
        //  Sets alphabet size to 0.
        //  
        //  Example:
        //  
        //      lb::alphabet A;
        //  
        alphabet()
            : sz(0) {}
            
        //  
        //  Alphabet constructor.
        //  Extracts symbols from input text and creates new alphabet
        //  object from them.
        //  
        //  @param text - input sequence reference
        //  
        //  Example:
        //  
        //      lb::sequence S = "ACGACAGATT";
        //      lb::alphabet A[S};
        //  
        inline alphabet(const lb::sequence& text);

        //  
        //  Overrides operator[].
        //
        //  @param index - index of symbol in alphabet
        //  @return symbol on given index in alphabet
        //  
        //  Example:
        //  
        //      lb::sequence S = "ACGACAGATT";
        //      lb::alphabet A[S};
        //      symbol_type symbol = A[1]; //  symbol = "C"
        //  
        symbol_type operator[](lb::size_t index) const
           { return rmap[index]; }
           
        //  
        //  Overrides operator[].
        //
        //  @param symbol - symbol in alphabet
        //  @return index of given symbol in alphabet
        //  
        //  Example:
        //  
        //      lb::sequence S = "ACGACAGATT";
        //      lb::alphabet A[S};
        //      uint8 index = A["A"]; //  index = 0
        //  
        uint8 operator[](symbol_type symbol) const
            { return map[symbol]; }
            
        //  
        //  Returns sum of occurences of symbols of alphabet in input sequence
        //  before the one given by index.
        //
        //  @param index - index of symbol in alphabet
        //  @return csum
        //  
        //  Example:
        //  
        //      lb::sequence S = "ACGACAGATT";
        //      lb::alphabet A[S};
        //      uint8 csum = A.csum('G'); //  csum = 6
        //  
        int csum(lb::size_t index) const
            { return cs[index]; }
            
        //  
        //  Returns number of members in alphabet.
        //  @return size
        //  
        //  Example:
        //  
        //      lb::sequence S = "ACGACAGATT";
        //      lb::alphabet A[S};
        //      lb::site_t size = A.size(); //  size = 4
        //  
        lb::size_t size() const
            { return sz; }
    private:
        //  Array that is indexed with alphabet symbol and stores index value.
        uint8 map[256];
        //  Array that is indexed with index of symbol in alphabet and stores symbol.
        char rmap[256];
        // Stores csum of alphabet symbols.
        lb::size_t cs[256];
        // Stores size of alphabet.
        lb::size_t sz;
    };
}

lb::alphabet::alphabet(const lb::sequence& text) {
    std::map<symbol_type, int> cnt; //  Sorted map
    for (auto& c : text) ++cnt[c];

    memset(map, 0, sizeof(map));
    memset(rmap, 0, sizeof(rmap));
    memset(cs, 0, sizeof(cs));

    sz = cnt.size();

    int tsum = 0, tindex = 0;
    for (auto& it : cnt) {
        map[it.first] = tindex;
        rmap[tindex] = it.first;
        cs[tindex++] = tsum;
        tsum += it.second;
    }
}

#endif  // _ALPHABET_HPP_