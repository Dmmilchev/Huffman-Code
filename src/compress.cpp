#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "huffman_tree.h"
#include "bit_stack.h"
#include "utils.h"

namespace Compress {
    
    std::unordered_map<char, size_t> count_occurrences(std::string text) {
        std::unordered_map<char, size_t> res;

        for (char c : text)
            res[c]++;
        
        return res;
    }

    void compress(const char* toCompress, const char* compressed) {
        std::string text = Utils::readFile(toCompress);
        std::unordered_map<char, size_t> occurrences = count_occurrences(text);

        HuffmanTree tree(occurrences);
        Encodings encodings = tree.getEncodings();

        BitStack bitstack;
        for (char c : text) 
            for (bool bit : encodings[c]) 
                bitstack.push_bit(bit);
        
        std::ofstream output_file(compressed, std::ios::binary | std::ios::out);
        Utils::saveHashmap(output_file, occurrences);
        Utils::saveBitStack(output_file, bitstack);
        output_file.close();
    }

    std::string decompress(const char* compressed, const char* nonCompressed) {
        std::ifstream file(compressed, std::ios::binary | std::ios::in);
        std::unordered_map<char, size_t>  map = Utils::loadHashmap(file);
        BitStack bitstack = Utils::loadBitStack(file);
        file.close();

        HuffmanTree tree(map);
        Encodings encodings = tree.getEncodings();

        std::string result = tree.decode(bitstack, encodings);

        return result;
    }


}