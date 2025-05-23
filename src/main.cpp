#include <iostream>
#include <string>
#include "utils.h"
#include "compress.h"
#include <unordered_map>
#include "huffman_tree.h"
#include "bit_stack.h"
#include <algorithm>

int main() {
    const char* input_file1 = "/home/deyan/Desktop/huffman code compressor/data/words.txt";
    const char* output_file1 = "/home/deyan/Desktop/huffman code compressor/data/words.cmpr";

    const char* input_file2 = "/home/deyan/Desktop/huffman code compressor/data/random.txt";
    const char* output_file2 = "/home/deyan/Desktop/huffman code compressor/data/random.cmpr";

    const char* input_file3 = "/home/deyan/Desktop/huffman code compressor/data/random_ascii.txt";
    const char* output_file3 = "/home/deyan/Desktop/huffman code compressor/data/random_ascii.cmpr";

    Compress::compress(input_file3, output_file3);
    std::string result = Compress::decompress(output_file2, input_file2);
    std::cout << result;
    
    return 0;
}
