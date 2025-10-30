//Protection.
#ifndef COMPRESSOR_H
#define COMPRESSOR_H

//Necessary Libraries.
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

//Prototype function declarations and the node structure.
void compress(std::ifstream&, std::ofstream&);
void decompress(std::ifstream&, std::ofstream&);
void charCount(std::unordered_map<char, int>&, std::string);
std::string generateCode(Node&, std::unordered_map<char, int>&);
class Node;

#endif
