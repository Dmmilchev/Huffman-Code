#pragma once
#include <iostream>
#include <unordered_map>
#include <map>
#include <queue>
#include "huffman_tree.h"
#include "bit_stack.h"
#include <cassert>

using Encodings = std::unordered_map<char, std::vector<bool>>;

Node::Node(size_t count, Node* left, Node* right) : c('\0'), count(count), left(left), right(right) {}
Node::Node(char c, size_t count, Node* left, Node* right) : c(c), count(count), left(left), right(right) {}

bool CompareNode::operator()(Node* a, Node* b) {
    return a->count > b->count;
}

HuffmanTree::HuffmanTree(const std::unordered_map<char, size_t>& occurrences) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> pq;
    std::map<char, size_t> sorted_map(occurrences.begin(), occurrences.end()); 
    // hurts my eyes, when I see the above line of code. 
    // Too inefficient, but we have to determinize the construction of the tree.
    // Might deal with it later.

    for (auto& pair : sorted_map) {
        char c = pair.first; 
        size_t count = pair.second;
        pq.push(new Node(c, count, nullptr, nullptr));
    }

    while(pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* newNode = new Node(left->count + right->count, left, right);
        pq.push(newNode);
    }
    
    assert(pq.size() == 1);

    this->root = pq.top(); pq.pop();
}  

void HuffmanTree::getEncodingsHelper(Node* root, std::vector<bool>& path, Encodings& encodings) {
    if (root->c != '\0') {
        assert(encodings.find(root->c) == encodings.end());

        encodings[root->c] = path;
        return;
    }

    path.push_back(0);
    getEncodingsHelper(root->left, path, encodings);
    path.pop_back();
    path.push_back(1);
    getEncodingsHelper(root->right, path, encodings);
    path.pop_back();
}


Encodings HuffmanTree::getEncodings() {
    Encodings encodings;
    std::vector<bool> path;
    getEncodingsHelper(root, path, encodings);
    return encodings;
}

std::string HuffmanTree::decode(BitStack& bitstack, Encodings& encodings) {
    std::string result;

    Node* iter = root;
    while (!bitstack.isEmpty()) {
        bool bit = bitstack.pop_bit();
        if (bit)
            iter = iter->right;
        else   
            iter = iter->left;

        if (iter->c != '\0') {
            result.push_back(iter->c);
            iter = root;
        }
    }

    return result;
}

void HuffmanTree::printTreeHelper(Node* root) const {
    if (!root) {
        return;
    }
    std::cout << root->c << " " << root->count << std::endl;
    printTreeHelper(root->left);
    printTreeHelper(root->right);
}    


void HuffmanTree::printTree() const {
    this->printTreeHelper(this->root);
}