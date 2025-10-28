//Protection.
#ifndef COMPRESSOR_H
#define COMPRESSOR_H

//Necessary Libraries.
#include <iostream>
#include <fstream>
#include <unordered_map>

//Prototype function declarations.
void compress(ifstream& infile, ofstream& outfile)
void decompress(ifstream& infile, ofstream& outfile)
int charCount(std::unordered_map<char, int>& charMap)
void generateCode()

#endif
