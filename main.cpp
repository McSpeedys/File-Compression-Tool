#include "compressor.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

int main(int argc, char** argv){
  //Using a switch to handle user input.
  switch argv[1]{
    case "-c":{
      std::ifstream infile;
      std::ofstream outfile;

      infile.open(argv[2]);
      outfile.open(argv[3]);

      //Checking if the files given exist.
      if(!(infile.is_open() && outfile.is_open())){
        std::cout << "Please input valid and existing files." << std::endl;
        return 1;
      }

      compress(infile, outfile);

      break;
    }
    case "-d":{
      std::ifstream infile;
      std::ofstream outfile;

      infile.open(argv[2]);
      outfile.open(argv[3]);

      if(!(infile.is_open() && outfile.is_open())){
        std::cout << "Please input valid and existing files." << std::endl;
      }

      decompress(infile, outfile);

      break;
    }
    default:{
      std::cout << "Valid Usage:\n";
      std::cout << "To Compress: ./compress.exe -c <Your_input_file> <Your_output_file>\n";
      std::cout << "To Decompress: ./compress.exe -d <Your_input_file> <Your_output_file>" << std::endl;
      return 1;
    }

  }
  return 0;
}
