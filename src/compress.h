#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "bit_stack.h"

namespace Compress {
    
    std::unordered_map<char, size_t> count_occurrences(std::string text);

    void compress(const char* toCompress, const char* compressed);

    std::string decompress(const char* compressed, const char* nonCompressed);
}