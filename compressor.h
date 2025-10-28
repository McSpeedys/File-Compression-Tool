//Protection.
#ifndef COMPRESSOR_H
#define COMPRESSOR_H

//Necessary Libraries.
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

//Prototype function declarations and our node structure.
void compress(ifstream&, ofstream&);
void decompress(ifstream&, ofstream&);
void charCount(std::unordered_map<char, int>&);
void generateCode(Node&, std::string, std::unordered_map<char, int>&);
struct Node;

#endif
