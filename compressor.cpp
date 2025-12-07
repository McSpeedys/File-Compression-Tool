//Necessary libraries for the implementation.
#include "compressor.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

//The node class implementation needed to create the Huffman tree.

//Custom constructor.
Node::Node(int freq, char c): frequency(freq), currChar(c), left(NULL), right(NULL){}

//Default constructor.
Node::Node(): frequency(0), currChar(' '), left(NULL), right(NULL){}

Node::~Node(){
  delete left;
  delete right;
}
  
//Public functions to be able to edit private values of nodes.
void Node::setFreq(int freq){
  this->frequency = freq;
}

void Node::setChar(char c){
  this->currChar = c;
}

void Node::setRNode(Node* n){
  this->right = n;
}
    
void Node::setLNode(Node* n){
  this->left = n;
}

int Node::getFreq(){
  return frequency;
}

char Node::getChar(){
  return currChar;
}

Node* Node::getLeft(){
  return left;
}

Node* Node::getRight(){
  return right;
}

void charCount(std::unordered_map<char, int>& hmap, std::string target){
  //Navigate through the line one by one and register them to the map.
  for(int i = 0; i < target.length(); i++){
    char currChar = target[i];
    //If a character is not already in the map put it into the map.
    //If it is already in the map increment its frequency.
    if(hmap.count(currChar) == 0){
      hmap.insert({currChar, 1});
    }
    else{
      hmap[currChar]++; 
    }
  }
}

void generateHuffTree(Node*& root, std::unordered_map<char, int>& charMap){
  std::vector<Node*> nodes;
  
  //Pushing each member of the hashmap into the vector as nodes.
  for(const auto& p: charMap){
    nodes.push_back(new Node(p.second, p.first));
  }

  //Handling edge case where only a single character was used in file.
  if(nodes.size() == 1){
    Node* single = nodes[0];
    Node* parent = new Node(single->getFreq(), ' ');

    parent->setLNode(single);
    root = parent;
    return;
  }
  
  //Combining two minimum frequency nodes until we create a whole tree in
  //one node.
  while(nodes.size() > 1){
    int min1 = -1;
    int min2 = -1;

    for(int i = 0; i < nodes.size(); i++){
      if(min1 == -1 || nodes[i]->getFreq() < nodes[min1]->getFreq()){
        min1 = i;
      }
    }

    for(int i = 0; i < nodes.size(); i++){
      //Ignore first minimum.
      if(i == min1){
        continue;
      }

      if(min2 == -1 || nodes[i]->getFreq() < nodes[min2]->getFreq()){
        min2 = i;
      }
    }
    
    //Setting up left and right nodes,
    //making sure min1 > min2 so deletion order does not
    //break vector order.
    Node* left = nodes[min1];
    Node* right = nodes[min2];
    if(min1 < min2){
      std::swap(min1, min2);
    }
    
    //Setting up parent node. 
    Node* parent = new Node(left->getFreq() + right->getFreq(), ' ');
    parent->setLNode(left);
    parent->setRNode(right);
    
    //Removing the used up nodes out of rotation.
    nodes.erase(nodes.begin() + min1);
    nodes.erase(nodes.begin() + min2);
    
    //Pushing the parent node back into the vector.
    nodes.push_back(parent);
  }
  
  //Setting root as the last node left which is the tree.
  root = nodes[0];
}

void generateCodeTable(Node* currNode, std::string currCode, std::unordered_map<char, std::string>& table){
  if(!currNode){
    return;
  }
  
  //Assigning the code if we are at a leaf node.
  if(currNode->getLeft() == NULL && currNode->getRight() == NULL){
    //Handling single char cases.
    if(currCode.empty()){
      currCode = "0";
    }

    table[currNode->getChar()] = currCode;
    return;
  }

  //If we are not in a leaf node traversing recursively
  //and adding huffman code in 0 and 1s.
  generateCodeTable(currNode->getLeft(), currCode + "0", table);
  generateCodeTable(currNode->getRight(), currCode + "1", table);
}

std::string generateCode(Node* root, std::unordered_map<char, int>& charMap, std::string target){
  std::unordered_map<char, std::string> table;
  
  //Build the table.
  generateCodeTable(root, "", table);
  
  std::string code;

  //Convert each char to huffman code.
  for(char c: target){
    code += table[c];
  }

  return code;
}

void packBits(std::ofstream& outfile, std::string& code){
  unsigned char byte = 0;
  int bitCount = 0;

  for(char bit: code){
    //Shift left and add new bit.
    byte = (byte << 1) | (bit - '0');
    bitCount++;

    if(bitCount == 8){
      outfile.write(reinterpret_cast<char*>(&byte), 1);

      byte = 0;
      bitCount = 0;
    }
  }

  //Handling padding.
  if(bitCount > 0){
    //Padding with 0s.
    byte = byte << (8 - bitCount);
    outfile.write(reinterpret_cast<char*>(&byte), 1);
  }
}

void writeHeader(std::ofstream& outfile, std::unordered_map<char, int>& charMap, int padding){
  //Write the number of unique characters.
  int uniqueChars = charMap.size();
  outfile.write(reinterpret_cast<char*>(&uniqueChars), sizeof(int));

  //Write each character and its frequency.
  for(const auto& pair: charMap){
    outfile.write(&pair.first, sizeof(char));
    outfile.write(reinterpret_cast<const char*>(&pair.second), sizeof(int));
  }

  //Write the padding bits.
  outfile.write(reinterpret_cast<char*>(&padding), sizeof(int));
}

void compress(std::ifstream& infile, std::ofstream& outfile){
  Node* root = new Node();
  std::string currLine;
  std::string entireText;
  std::unordered_map<char, int> hmap;

  //Go through the file once to set up a hashmap with each character and their frequencies.
  while(std::getline(infile, currLine)){
    //Adding back the newline that we removed in getLine.
    currLine += '\n';
    charCount(hmap, currLine);
    entireText += currLine;
  }
  
  //Generate the tree.
  generateHuffTree(root, hmap);
  
  //Generate the Huffman code.
  std::string huffcode = generateCode(root, hmap, entireText);
  
  //Calculate the padding amount.
  int padding = (8 - (huffcode.length() % 8)) % 8;

  //Write header.
  writeHeader(outfile, hmap, padding);

  //Write the packed bits,
  packBits(outfile, huffcode);

  
  //Close the files.
  infile.close();
  outfile.close();
  //Free memory.
  delete root;
}

void decompress(std::ifstream& infile, std::ofstream& outfile){
  //Read the header off the file.
  int uniqueChars;
  infile.read(reinterpret_cast<char*>(&uniqueChars), sizeof(int));
  
  //Load the characters and their frequency
  //into a hashmap.
  std::unordered_map<char, int> charMap;
  for(int i = 0; i < uniqueChars; i++){
    char currChar;
    int freq;
    infile.read(&currChar, sizeof(char));
    infile.read(reinterpret_cast<char*>(&freq), sizeof(int));
    charMap[currChar] = freq;
  }
  
  //Calculate the padding.
  int padding;
  infile.read(reinterpret_cast<char*>(&padding), sizeof(int));

  //Rebuild the huffman tree.
  Node* root = new Node();
  generateHuffTree(root, charMap);

  //Read and unpack bits one by one.
  Node* currNode = root;
  unsigned char byte;
  while(infile.read(reinterpret_cast<char*>(&byte), 1)){
    for(int i = 7; i >= 0; i--){
      //Check if current bit is 0 or 1.
      bool bit = (byte >> i) & 1;
      //If bit is 1 check right branch, if bit is 0 
      //check left branch.
      currNode = bit ? currNode->getRight(): currNode->getLeft();
      //Once we hit a leaf node write it into the file and 
      //go back to the root of the tree.
      if(currNode->getLeft() == NULL && currNode->getRight() == NULL){
        outfile << currNode->getChar();
        currNode = root;
      }
    }
  }

  //Close the files.
  infile.close();
  outfile.close();
  //Free memory.
  delete root;
}
