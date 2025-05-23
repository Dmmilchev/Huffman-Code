#pragma once
#include <iostream>
#include <unordered_map>
#include "bit_stack.h"

using Encodings = std::unordered_map<char, std::vector<bool>>;

struct Node {
    // in tree nodes have c == '\0'
    // in tree nodes' count has the sum of all occurrences of the leaves that are children to the node.
    
    char c;
    size_t count;
    Node* left;
    Node* right;

    Node(size_t count, Node* left, Node* right);
    Node(char c, size_t count, Node* left, Node* right);

};

struct CompareNode {
    bool operator()(Node* a, Node* b);
};

class HuffmanTree {
private:

    Node* root;

    void printTreeHelper(Node* root) const;
    
    void getEncodingsHelper(Node* root, std::vector<bool>& path, Encodings& encodings);
    
public:

    HuffmanTree(const std::unordered_map<char, size_t>& occurrences);

    Encodings getEncodings();

    std::string decode(BitStack& bitstack, Encodings& encodings);  // bad design encodings must be part of the class
                                                                  // might be best to hide the encodings at all from the user

    void printTree() const;
    
};