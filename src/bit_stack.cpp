#pragma once
#include "bit_stack.h"
#include <iostream>
#include <cstdint>
#include <vector>
#include <cassert>

BitStack::BitStack() {
    bit_count = 0;
}

void BitStack::push_bit(bool bit) {
    if (bit_count % 8 == 0) {
        data.push_back(0);
    }

    if (bit) 
        data.back() = (data.back() << 1) | 1;
    else 
        data.back() = (data.back() << 1);

    bit_count++;  
} 

bool BitStack::pop_bit() {
    if (this->isEmpty()) {
        throw std::runtime_error("Empty stack.");
    }

    bool bit = data.back() & 1;
    data.back() = data.back() >> 1;

    bit_count--;
    if (bit_count % 8 == 0) 
        data.pop_back();

    return bit;
}

u_int64_t BitStack::getBitCount() const {
    return bit_count;
}


bool BitStack::isEmpty() {
    if (bit_count == 0) 
        assert(data.size() == 0);
    return bit_count == 0;
}