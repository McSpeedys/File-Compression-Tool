# Huffman Compression Tool
A C++ implementation of Huffman coding for lossless file compression and decompression.

# Overview
This project implements the Huffman coding algorithm. 
It analyzes character frequencies in a file, builds an optimal binary tree, and encodes the data using variable-length codes where more frequent characters use shorter codes.

# Features
-Lossless Compression: Reconstructs original files without any loss in data.
-Binary Output: Packs bits into bytes for actual compression.
-Automatic Tree Reconstruction: Stores frequency table in header for decompression
-Single Character Handling: Correctly handles edge cases like files with only one unique character

# Building
The executable in the repo was built on Arch linux, build on your own to make sure it works on your machine.

## Prerequisites:
# -C++ compiler with C++11 support or later
# -Make
# -Git (Optional)

### Compilation:
1. Clone the repo:
`git clone https://github.com/McSpeedys/File-Compression-Tool.git`
2. Access the directory:
`cd File-Compression-Tool`
3. "Make" the program:
`make`
4. If you want to delete the program:
`make clean`

# Usage 
# Compress a file.
`./compressor input-file.txt output-file.txt`

# Decompress a file.
`./compressor -d input-file.txt output-file.txt`

# Miscellaneous
In the case you experience a bug or just want to contribute somehow feel free to submit a pull request or branch off.

# Known Limitations
Due to the nature of the implementation of Huffman's algorithm in this project it is recommended you compress files that are
not too small. Works even better with files that have a lot of repeating characters. 
