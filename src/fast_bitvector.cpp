#include "fast_bitvector.hpp"
#include "base.hpp"
#include <iostream>
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <iterator>

lb::fast_bitvector::fast_bitvector(std::vector<bool> bv) : bv(bv) {

}

lb::fast_bitvector::fast_bitvector(){
	bv = std::vector<bool>();
}
void lb::fast_bitvector::push_back(const bool& val){
	return bv.push_back(val);
}

lb::size_t lb::fast_bitvector::size(){
	return bv.size();
}


lb::size_t lb::fast_bitvector::rank(lb::size_t index, bool bit){
	return std::count(bv.begin(), bv.begin() + index, bit);

}

std::vector<bool>::iterator lb::fast_bitvector::begin() {
	return bv.begin();
}


