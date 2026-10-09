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
-Native GUI: Simple graphical interface for Linux (FLTK) and Windows (Win32), the command line still works as before
-Reliable Round Trips: The Huffman tree is built in a deterministic order and padding bits are ignored when decompressing, so decompressing gives back the original file

# Building
The executable in the repo was built on Arch linux, build on your own to make sure it works on your machine.
It is recommended to rebuild it since the committed executable does not include the GUI.

## Prerequisites:
### -C++ compiler with C++11 support or later
### -Make
### -FLTK development files on Linux (e.g. `sudo apt install libfltk1.3-dev` or `sudo pacman -S fltk`)
### -Nothing extra on Windows (the GUI uses the Win32 API); build with MSYS2/MinGW `make`, or cross compile from Linux with `make windows` (needs mingw-w64)
### -Git (Optional)

### Compilation:
1. Clone the repo:
`git clone https://github.com/McSpeedys/File-Compression-Tool.git`
2. Access the directory:
`cd File-Compression-Tool`
3. "Make" the program (on Windows with MSYS2/MinGW this builds the Win32 GUI version, on Linux the FLTK one):
`make`
4. Optional, cross compile a standalone Windows executable from Linux (needs mingw-w64), this creates `compress-win.exe`:
`make windows`
5. If you want to delete the program:
`make clean`

# Usage 
# Graphical interface.
Run the program with no arguments (or double click it) to open the GUI: pick an input file, an output file and press Compress or Decompress.
`./compress.exe`

# Command line.
# Compress a file.
`./compress.exe -c input-file.txt output-file.txt`

# Decompress a file.
`./compress.exe -d input-file.txt output-file.txt`

# Miscellaneous
In the case you experience a bug or just want to contribute somehow feel free to submit a pull request or branch off.

# Known Limitations
Files compressed with versions before the decompression fix may not decompress correctly, compress them again with the current version.
The compressor always adds a newline at the end of the last line of the input file.
Due to the nature of the implementation of Huffman's algorithm in this project it is recommended you compress files that are
not too small. Works even better with files that have a lot of repeating characters. 
