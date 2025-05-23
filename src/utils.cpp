#include "utils.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

namespace Utils {

    std::string readFile(const char* filename) {
        std::ifstream file (filename, std::ios::binary);

        if (!file) {
            throw std::runtime_error("Could'nt open file.");
        }

        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        std::string content(size, '\0');
        file.seekg(0);
        file.read(&content[0], size);

        file.close();

        return content;
    }

    void saveHashmap(std::ofstream& file, const std::unordered_map<char, size_t>& map) {
        size_t length = map.size();
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));

        for (std::pair p : map) {
            char c = p.first;
            size_t count = p.second;

            file.write(reinterpret_cast<const char*>(&c), sizeof(c));
            file.write(reinterpret_cast<const char*>(&count), sizeof(count));
        }
    }

    std::unordered_map<char, size_t> loadHashmap(std::ifstream& file) {
        size_t length;
        file.read(reinterpret_cast<char*>(&length), sizeof(length));

        std::unordered_map<char, size_t> map;
        for (size_t i = 0; i < length; ++i) {
            char c;
            size_t count;

            file.read(reinterpret_cast<char*>(&c), sizeof(c));
            file.read(reinterpret_cast<char*>(&count), sizeof(count));

            map[c] = count;
        }

        return map;
    }

    void saveBitStack(std::ofstream& file, BitStack& bitstack) {
        uint64_t wholeBytes = bitstack.getBitCount() / 8;
        uint8_t remainingBits = bitstack.getBitCount() % 8;

        file.write(reinterpret_cast<const char*> (&wholeBytes), sizeof(uint64_t));
        file.write(reinterpret_cast<const char*> (&remainingBits), sizeof(uint8_t));

        while (bitstack.getBitCount() > 0) {
            uint8_t byte = 0;
            for (int i = 0; i < 8 && bitstack.getBitCount() > 0; ++i) {
                if (bitstack.pop_bit()) 
                    byte = (byte << 1) | 1;
                else 
                    byte = (byte << 1);
            }

            if (bitstack.getBitCount() == 0 && remainingBits != 0) 
                byte <<= (8 - remainingBits);

            file.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
        }
    }

    BitStack loadBitStack(std::ifstream& file) {        
        uint64_t wholeBytes;
        uint8_t remainingBits;
        file.read(reinterpret_cast<char*>(&wholeBytes), sizeof(wholeBytes));
        file.read(reinterpret_cast<char*>(&remainingBits), sizeof(remainingBits));

        BitStack bitstack;
        for (uint64_t i = 0; i < wholeBytes; ++i) {
            uint8_t byte;
            file.read(reinterpret_cast<char*>(&byte), sizeof(byte));

            for (int j = 0; j < 8; ++j) {
                bool bit = (byte >> 7 - j) & 1;
                bitstack.push_bit(bit);
            }
        }

        uint8_t byte;
        file.read(reinterpret_cast<char*>(&byte), sizeof(byte));
        for (int i = 0; i < remainingBits; ++i) {
            bool bit = (byte >> (7 - i)) & 1;
            bitstack.push_bit(bit);
        }

        return bitstack;
    }

}