#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "bit_stack.h"

namespace Utils {

    std::string readFile(const char* filename);
    
    void saveHashmap(std::ofstream& file, const std::unordered_map<char, size_t>& map);

    std::unordered_map<char, size_t> loadHashmap(std::ifstream& file);

    void saveBitStack(std::ofstream& file, BitStack& bitstack);

    BitStack loadBitStack(std::ifstream& file);

}