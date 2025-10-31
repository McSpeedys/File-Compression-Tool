//Necessary libraries for the implementation.
#include "compressor.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

//The node structure needed to create the Huffman tree.
class Node{
  private:
    int frequency;
    char currChar;

    Node* left;
    Node* right;
  
  public:
    //Custom constructor.
    Node(int freq, char c): frequency(freq), currChar(c) left(NULL) right(NULL){}

    //Default constructor.
    Node(): frequency(0), currChar(''), left(NULL), right(NULL){}
    
    //Public functions to be able to edit private values of nodes.
    static Node* setFreq(int freq){
      this->frequency = freq;
    }

    static Node* setChar(char c){
      this->currChar = c;
    }

    static Node* setRNode(Node* n){
      this->right = n;
    }
    
    static Node* setLNode(Node* n){
      this->left = n;
    }
};

void charCount(std::unordered_map<char, int>& hmap, std::string target){}

std::string generateCode(Node* root, std::unordered_map<char, int>& tree, std::string target){}

void compress(std::ifstream& infile, std::ofstream& outfile){
  Node* root = new Node();
  std::string currLine;
  std::unordered_map<char, int> hmap;

  //Go through the file once to set up a hashmap with each character and their frequencies.
  while(infile >> currLine){
    charCount(hmap, currLine);
  }
  
  //Clear the input stream of any potential errors and set it back up to the beginning.
  infile.clear();
  infile.seekg(0, std::ios::beg);
  
  //Go through the file a second time to generate Huffman codes for each line 
  //and output them into a new file.
  while(infile >> currLine){
    std::string huffCode = generateCode(root, hmap, currLine);
    outfile << huffCode;
  } 
  
  //Close the files.
  infile.close();
  outfile.close();
}

void decompress(std::ifstream& infile, std::ofstream& outfile){}
