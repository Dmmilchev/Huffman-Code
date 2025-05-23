#pragma once
#include <iostream>
#include <cstdint>
#include <vector>

class BitStack {
private:

    u_int64_t bit_count;
    std::vector<u_int8_t> data;

public:

    BitStack();

    void push_bit(bool bit);

    bool pop_bit();

    u_int64_t getBitCount() const;

    bool isEmpty();
};