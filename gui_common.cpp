#include "gui.h"
#include "compressor.h"
#include <fstream>

//Mirrors the file handling done in main.cpp for -c and -d.
bool runOperation(bool doCompress, const std::string& in, const std::string& out, std::string& error){
  std::ifstream infile;
  std::ofstream outfile;

  if(doCompress){
    infile.open(in);
    //Open as binary so we can write binary bits into it.
    outfile.open(out, std::ios::binary);
  }
  else{
    //Open as binary so we can read off of it in bits.
    infile.open(in, std::ios::binary);
    outfile.open(out);
  }

  //Checking if the files given exist.
  if(!(infile.is_open() && outfile.is_open())){
    error = "Please input valid and existing files.";
    return false;
  }

  if(doCompress){
    compress(infile, outfile);
  }
  else{
    decompress(infile, outfile);
  }
  return true;
}
