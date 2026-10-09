//Linux (and any other FLTK platform) front end.
#include "gui.h"
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Native_File_Chooser.H>

namespace {
  Fl_Input* inInput;
  Fl_Input* outInput;
  Fl_Box* status;

  void browse(Fl_Input* target, bool save){
    Fl_Native_File_Chooser chooser;
    chooser.type(save ? Fl_Native_File_Chooser::BROWSE_SAVE_FILE
                      : Fl_Native_File_Chooser::BROWSE_FILE);
    if(chooser.show() == 0){
      target->value(chooser.filename());
    }
  }

  void browseIn(Fl_Widget*, void*){ browse(inInput, false); }
  void browseOut(Fl_Widget*, void*){ browse(outInput, true); }

  void run(bool doCompress){
    std::string err;
    if(runOperation(doCompress, inInput->value(), outInput->value(), err)){
      status->labelcolor(FL_DARK_GREEN);
      status->label(doCompress ? "Compression finished." : "Decompression finished.");
    }
    else{
      status->labelcolor(FL_RED);
      static std::string msg;
      msg = err;
      status->label(msg.c_str());
    }
    status->redraw();
  }

  void onCompress(Fl_Widget*, void*){ run(true); }
  void onDecompress(Fl_Widget*, void*){ run(false); }
}

int runGui(){
  Fl_Double_Window* win = new Fl_Double_Window(520, 180, "Huffman Compression Tool");
  inInput = new Fl_Input(100, 15, 310, 25, "Input file:");
  (new Fl_Button(420, 15, 85, 25, "Browse..."))->callback(browseIn);
  outInput = new Fl_Input(100, 55, 310, 25, "Output file:");
  (new Fl_Button(420, 55, 85, 25, "Browse..."))->callback(browseOut);
  (new Fl_Button(100, 100, 150, 30, "Compress"))->callback(onCompress);
  (new Fl_Button(260, 100, 150, 30, "Decompress"))->callback(onDecompress);
  status = new Fl_Box(15, 145, 490, 25, "");
  status->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
  win->end();
  win->show();
  return Fl::run();
}
