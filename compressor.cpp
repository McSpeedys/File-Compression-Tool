//Necessary libraries for the implementation.
#include "compressor.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

//The node class needed to create the Huffman tree.
class Node{
  private:
    int frequency;
    char currChar;

    Node* left;
    Node* right;
  
  public:
    //Custom constructor.
    Node(int freq, char c): frequency(freq), currChar(c), left(NULL), right(NULL){}

    //Default constructor.
    Node(): frequency(0), currChar(' '), left(NULL), right(NULL){}
    
    //Public functions to be able to edit private values of nodes.
    void setFreq(int freq){
      this->frequency = freq;
    }

    void setChar(char c){
      this->currChar = c;
    }

    void setRNode(Node* n){
      this->right = n;
    }
    
    void setLNode(Node* n){
      this->left = n;
    }

    int getFreq(){
      return frequency;
    }

    char getChar(){
      return currChar;
    }

    Node* getLeft(){
      return left;
    }

    Node* getRight(){
      return right;
    }
};

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

void generateHuffTree(Node* root, std::unordered_map<char, int>& charMap){
  std::vector<Node*> nodes;
  
  //Pushing each member of the hashmap into the vector as nodes.
  for(const auto& p: charMap){
    nodes.push_back(new Node(p.second, p.first));
  }

  //Handling edge case where only a single character was used in file.
  if(nodes.size() == 1){
    Node* single = nodes[0];
    Node* parent = new Node(only->getFreq(), ' ');

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
    
    //Pushing the parent node back into the vector.
    nodes.push_back(parent);
  }
  
  //Setting root as the last node left which is the tree.
  root = nodes[0];
}

std::string generateCode(Node* root, std::unordered_map<char, int>& charMap, std::string target){

}

void compress(std::ifstream& infile, std::ofstream& outfile){
  Node* root = new Node();
  std::string currLine;
  std::unordered_map<char, int> hmap;

  //Go through the file once to set up a hashmap with each character and their frequencies.
  while(std::getline(infile, currLine)){
    charCount(hmap, currLine);
  }

  generateHuffTree(root, hmap);
  
  //Clear the input stream of any potential errors and set it back up to the beginning.
  infile.clear();
  infile.seekg(0, std::ios::beg);
  
  //Go through the file a second time to generate Huffman codes for each line 
  //and output them into a new file.
  while(std::getline(infile, currLine)){
    std::string huffCode = generateCode(root, hmap, currLine);
    outfile << huffCode;
  } 
  
  //Close the files.
  infile.close();
  outfile.close();
}

void decompress(std::ifstream& infile, std::ofstream& outfile){}
