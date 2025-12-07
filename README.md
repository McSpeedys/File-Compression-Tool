#Huffman Compression Tool
A C++ implementation of Huffman coding for lossless file compression and decompression.

#Overview
This project implements the Huffman coding algorithm. 
It analyzes character frequencies in a file, builds an optimal binary tree, and encodes the data using variable-length codes where more frequent characters use shorter codes.

#Features
-Lossless Compression: Reconstructs original files without any loss in data.
-Binary Output: Packs bits into bytes for actual compression.
-Automatic Tree Reconstruction: Stores frequency table in header for decompression
-Single Character Handling: Correctly handles edge cases like files with only one unique character

#Building
The executable in the repo was built on Arch linux, build on your own to make sure it works on your machine.

Prerequisites:
-C++ compiler with C++11 support or later
-Make

Compilation:



