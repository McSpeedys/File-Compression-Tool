//Windows front end using only the Win32 API (no extra libraries needed).
#include "gui.h"
#include <windows.h>
#include <commdlg.h>

namespace {
  enum { ID_IN = 1, ID_OUT, ID_BROWSE_IN, ID_BROWSE_OUT, ID_COMPRESS, ID_DECOMPRESS, ID_STATUS };

  std::string getText(HWND h){
    char buf[MAX_PATH * 4];
    GetWindowTextA(h, buf, sizeof(buf));
    return buf;
  }

  void browse(HWND parent, int editId, bool save){
    char path[MAX_PATH * 4] = "";
    OPENFILENAMEA ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = parent;
    ofn.lpstrFile = path;
    ofn.nMaxFile = sizeof(path);
    ofn.lpstrFilter = "All Files\0*.*\0";
    ofn.Flags = OFN_NOCHANGEDIR | (save ? OFN_OVERWRITEPROMPT : OFN_FILEMUSTEXIST);
    if(save ? GetSaveFileNameA(&ofn) : GetOpenFileNameA(&ofn)){
      SetWindowTextA(GetDlgItem(parent, editId), path);
    }
  }

  void run(HWND hwnd, bool doCompress){
    std::string err;
    if(runOperation(doCompress, getText(GetDlgItem(hwnd, ID_IN)),
                    getText(GetDlgItem(hwnd, ID_OUT)), err)){
      SetWindowTextA(GetDlgItem(hwnd, ID_STATUS),
                     doCompress ? "Compression finished." : "Decompression finished.");
    }
    else{
      SetWindowTextA(GetDlgItem(hwnd, ID_STATUS), err.c_str());
    }
  }

  LRESULT CALLBACK proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
    switch(msg){
      case WM_CREATE: {
        HFONT font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
        struct Item { const char* cls; const char* text; DWORD style; int x, y, w, h, id; };
        const Item items[] = {
          {"STATIC", "Input file:",  0, 15, 20, 80, 20, 0},
          {"EDIT",   "", WS_BORDER | ES_AUTOHSCROLL, 100, 17, 300, 24, ID_IN},
          {"BUTTON", "Browse...", BS_PUSHBUTTON, 410, 16, 85, 26, ID_BROWSE_IN},
          {"STATIC", "Output file:", 0, 15, 60, 80, 20, 0},
          {"EDIT",   "", WS_BORDER | ES_AUTOHSCROLL, 100, 57, 300, 24, ID_OUT},
          {"BUTTON", "Browse...", BS_PUSHBUTTON, 410, 56, 85, 26, ID_BROWSE_OUT},
          {"BUTTON", "Compress", BS_PUSHBUTTON, 100, 100, 150, 30, ID_COMPRESS},
          {"BUTTON", "Decompress", BS_PUSHBUTTON, 260, 100, 150, 30, ID_DECOMPRESS},
          {"STATIC", "", 0, 15, 145, 480, 20, ID_STATUS},
        };
        for(const Item& it: items){
          HWND h = CreateWindowExA(0, it.cls, it.text, WS_CHILD | WS_VISIBLE | it.style,
                                   it.x, it.y, it.w, it.h, hwnd, (HMENU)(INT_PTR)it.id,
                                   GetModuleHandle(NULL), NULL);
          SendMessage(h, WM_SETFONT, (WPARAM)font, TRUE);
        }
        return 0;
      }
      case WM_COMMAND:
        switch(LOWORD(wp)){
          case ID_BROWSE_IN:  browse(hwnd, ID_IN, false); break;
          case ID_BROWSE_OUT: browse(hwnd, ID_OUT, true); break;
          case ID_COMPRESS:   run(hwnd, true); break;
          case ID_DECOMPRESS: run(hwnd, false); break;
        }
        return 0;
      case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hwnd, msg, wp, lp);
  }
}

int runGui(){
  //Hide the console window when launched by double clicking.
  FreeConsole();

  HINSTANCE inst = GetModuleHandle(NULL);
  WNDCLASSA wc = {};
  wc.lpfnWndProc = proc;
  wc.hInstance = inst;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
  wc.lpszClassName = "HuffmanGui";
  RegisterClassA(&wc);

  HWND hwnd = CreateWindowExA(0, wc.lpszClassName, "Huffman Compression Tool",
                              WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                              CW_USEDEFAULT, CW_USEDEFAULT, 530, 220,
                              NULL, NULL, inst, NULL);
  ShowWindow(hwnd, SW_SHOW);

  MSG m;
  while(GetMessage(&m, NULL, 0, 0) > 0){
    if(!IsDialogMessage(hwnd, &m)){
      TranslateMessage(&m);
      DispatchMessage(&m);
    }
  }
  return 0;
}
