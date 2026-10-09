CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

# Windows uses the Win32 API; everything else uses FLTK.
# Cross compile for Windows from Linux with: make windows
ifeq ($(OS),Windows_NT)
  GUI = gui_win32
  EXTRA_LIBS = -lcomdlg32 -lgdi32 -static -static-libgcc -static-libstdc++
else
  GUI = gui_fltk
  GUI_CFLAGS = $(shell fltk-config --cxxflags)
  EXTRA_LIBS = $(shell fltk-config --ldflags)
endif

OBJS = main.o compressor.o gui_common.o $(GUI).o

compress.exe: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o compress.exe $(EXTRA_LIBS)

# Cross compile a standalone Windows executable (needs mingw-w64).
windows:
	x86_64-w64-mingw32-g++ -Wall -O2 main.cpp compressor.cpp gui_common.cpp gui_win32.cpp \
	  -o compress-win.exe -lcomdlg32 -lgdi32 -static -static-libgcc -static-libstdc++

main.o: main.cpp compressor.h gui.h
	$(CC) $(CFLAGS) main.cpp

compressor.o: compressor.cpp compressor.h
	$(CC) $(CFLAGS) compressor.cpp

gui_common.o: gui_common.cpp gui.h compressor.h
	$(CC) $(CFLAGS) gui_common.cpp

gui_fltk.o: gui_fltk.cpp gui.h
	$(CC) $(CFLAGS) $(GUI_CFLAGS) gui_fltk.cpp

gui_win32.o: gui_win32.cpp gui.h
	$(CC) $(CFLAGS) gui_win32.cpp

clean:
	rm -f *.o compress.exe compress-win.exe
