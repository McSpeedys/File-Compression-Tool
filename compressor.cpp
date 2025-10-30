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
    static Node* incFreq(){
      this->frequency = frequency + 1;
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

void charCount(std::unordered_map& hmap, std::string target){}

std::string generateCode(Node* root, std::unordered_map<char, int>& tree){}

void compress(std::ifstream& infile, std::ofstream& outfile){
  Node root = new Node()
}

void decompress(std::ifstream& infile, std::ofstream& outfile){}
