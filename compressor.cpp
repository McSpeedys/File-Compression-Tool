//Necessary libraries for the implementation.
#include "compressor.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

//The node structure needed to create the Huffman tree.
struct Node{
  int freq;
  char currChar;
  Node* left;
  Node* right;


}

void charCount(std::unordered_map hmap, std::string target){}

std::string generateCode(Node& root, std::unordered_map<char, int>& tree){}

void compress(std::ifstream& infile, std::ofstream& outfile){}

void decompress(std::ifstream& infile, std::ofstream& outfile){}
