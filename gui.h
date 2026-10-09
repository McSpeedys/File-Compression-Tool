//Protection.
#ifndef GUI_H
#define GUI_H

#include <string>

//Launches the native graphical interface. Returns the process exit code.
int runGui();

//Runs the same compress/decompress operations as the command line,
//opening the files in exactly the same modes. Returns true on success,
//otherwise puts a message in "error".
bool runOperation(bool doCompress, const std::string& in, const std::string& out, std::string& error);

#endif
