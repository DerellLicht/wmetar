//****************************************************************************
//  Copyright (c) 2013  Daniel D Miller
//  sendbfr.cpp - creates a child window for misc data entry.
//  The purpose of this window will be to accept data from a text file,
//  or pasted from clipboard, and send each line to the odu.
//
//  Produced and Directed by:  Dan Miller
//****************************************************************************
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include "resource.h"
#include "common.h"
#include "commonw.h"
#include "winmsgs.h"
#include "wmetar.h"
#include "wthread.h"

extern HINSTANCE g_hinst ;

//****************************************************************************
static TCHAR szEditName[] = _T("SendBuffer") ;

static HWND hwndEdit = NULL ;
static CThread const * SendBufThread = NULL;

static LRESULT CALLBACK SendFileProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
//****************************************************************************
//  this should be done only once, at program startup
//****************************************************************************
LRESULT register_edit_window(void)
{
   // WNDCLASS wndclass = {0} ;
   WNDCLASS wndclass ;
   memset((char *) &wndclass, 0, sizeof(WNDCLASS)) ;

   wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
   wndclass.lpfnWndProc   = SendFileProc ;
   wndclass.cbClsExtra    = 0 ;
   wndclass.cbWndExtra    = 0 ;
   wndclass.hInstance     = g_hinst ;
   wndclass.hIcon         = LoadIcon (g_hinst, MAKEINTRESOURCE(IDI_APPICON));
   wndclass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1) ;
   wndclass.lpszMenuName  = MAKEINTRESOURCE(IDM_POPPAD2) ;
   wndclass.lpszClassName = szEditName ;

   if (!RegisterClass(&wndclass)) {
      LRESULT result = (LRESULT) GetLastError() ;
      syslog("RegisterClass: %s", get_system_message(result)) ;
      return result ;
   }
   return 0;
}

//******************************************************************
//  read lines from cmd_fname and stuff all resulting data
//  into the edit window.
//******************************************************************
static int read_command_file(char *cmd_fname)
{
   char inpbfr[MAX_METAR_LEN+1] ;
   if (dbg_flags & DBG_VERBOSE)
      syslog("command file: %s\n", cmd_fname) ;
   // HWND hwndEdit = GetDlgItem(hDlgWnd, IDC_EDIT_CE) ;
   FILE *fd = fopen(cmd_fname, "rt") ;
   if (fd == 0)
      return (int) GetLastError() ;

   unsigned lcount = 0 ;
   while (fgets(inpbfr, MAX_METAR_LEN, fd) != 0) {
      lcount++ ;
      //  convert whatever newlines are found, into CR/LF
      int found = 0 ;
      char *hd = inpbfr ;
      while (*hd != 0) {
         if (*hd == CR  ||  *hd == LF) {
            *hd++ = CR ;
            *hd++ = LF ;
            *hd = 0 ;
            found = 1 ;
            break;
         }
         hd++ ;
      }
      if (!found) {
         syslog("line %u: no EOL found, discarding data\n", lcount) ;
         continue;
      }

      //  stuff text into edit buffer
      int ndx = GetWindowTextLengthA(hwndEdit);
      SendMessageA(hwndEdit, EM_SETSEL, (WPARAM) ndx, (LPARAM) ndx) ;
      SendMessageA(hwndEdit, EM_REPLACESEL, 0, (LPARAM) ((LPSTR) inpbfr));
   }
   fclose(fd) ;
   // if (dbg_flags & DBG_VERBOSE)
   //    termout("read %u lines", lcount) ;
   return 0;
}

//******************************************************************
static void send_commands(void)
{
   //****************************************************
   //  extract command list from editor window
   //****************************************************
   int ndx = GetWindowTextLengthA (hwndEdit);
   char *bfr = (char *) GlobalAlloc(GMEM_FIXED, ndx+1) ;
   if (bfr == NULL) {
      syslog("GlobalAlloc: %s\n", get_system_message()) ;
      return ;
   }
   unsigned blen = GetWindowTextA (hwndEdit, bfr, ndx+1);
   // bfr[ndx+1] = 0 ;
   bfr[blen] = 0 ;
   process_metar_string(bfr) ;
   // syslog("read %u of %u bytes\n", blen, ndx) ;
   // hex_dump((u8 *) bfr, ndx) ;

   GlobalFree(bfr) ;
}

//****************************************************************************
static LRESULT CALLBACK SendFileProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   // int iSelect, iEnable ;
   int result ;
   char command_filename[MAX_PATH] = "commands.txt" ;

   //***************************************************
   //  debug: log all windows messages
   //***************************************************
   // this_object->winmessages = true ;
   if (dbg_flags & DBG_WINMSGS) {
      switch (message) {
      //  list messages to be ignored
      case WM_NCHITTEST:
      case WM_SETCURSOR:
      case WM_MOUSEMOVE:
      case WM_NCMOUSEMOVE:
      case WM_COMMAND:
         break;
      default:
         syslog("ED: [%s]\n", lookup_winmsg_name(message)) ;
         break;
      }
   }

   //********************************************************************
   //  Windows message handler for this dialog
   //********************************************************************
   switch (message) {
   case WM_CREATE:
      {
//       TCHAR msgstr[81] ;
//       wsprintf(msgstr, _T("ODU Command Editor [M%u: %s]"), this_object->index,
//          ascii2unicode(get_sernum(this_object))) ;
//       // 00000:  4F 00 44 00 55 00 20 00 43 00 6F 00 6D 00 6D 00  | O.D.U. .C.o.m.m. |
//       // 00010:  61 00 6E 00 64 00 20 00 45 00 64 00 69 00 74 00  | a.n.d. .E.d.i.t. |
//       // 00020:  6F 00 72 00 20 00 5B 00 4D 00 32 00 3A 00 20 00  | o.r. .[.M.2.:. . |
//       // 00030:  30 00 32 00 32 00 32 00 34 00 36 00 5D 00 00 00  | 0.2.2.2.4.6.]... |
//       // hex_dump((u8 *) msgstr, 64) ;
//       SetWindowText(hwnd, msgstr) ;

      // SetWindowText(hwnd, _T("Test")) ;

      //  create the internal edit window
      hwndEdit = CreateWindow(_T("edit"), NULL,
                          WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |
                          WS_BORDER | ES_LEFT | ES_MULTILINE |
                          ES_AUTOHSCROLL | ES_AUTOVSCROLL,
                          0, 0, 0, 0, hwnd, (HMENU) IDC_EDITWIN,
                          ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;
      }
      return 0 ;

   case WM_SIZE:
      MoveWindow(hwndEdit, 0, 0, LOWORD (lParam), HIWORD (lParam), true) ;
      return 0 ;

   case WM_SETFOCUS:
      SetFocus(hwndEdit) ;
      return 0 ;

   case WM_COMMAND:
      switch(LOWORD(wParam)) {
      case IDC_BDECODE:
         send_commands() ;
         DestroyWindow(hwnd);
         return 0 ;

      //  not currently implemented
      case IDC_LOADFILE: //  read lines from file
         if (select_text_file(hwnd, command_filename)) {
            result = read_command_file(command_filename);
            if (result != 0) {
               syslog("%s: %s", command_filename, get_system_message(result)) ;
            }
         } else {
            syslog("select_text_file: %s", get_system_message()) ;
         }
         return 0 ;
      }  //lint !e744
      break ;

   case WM_CLOSE:
      DestroyWindow (hwnd) ;
      return 0 ;

   case WM_DESTROY:
      // syslog("EditWin: WM_DESTROY\n") ;
      // this_object->editwin_open = 0 ;
      SendBufThread = NULL ;
      PostQuitMessage(0) ;
      return 0 ;
   }  //lint !e744
   return DefWindowProc(hwnd, message, wParam, lParam) ;
}

//****************************************************************************
static DWORD WINAPI fEditThread(LPVOID iValue)
{
   HWND hwnd = CreateWindow(szEditName, szEditName,
        WS_OVERLAPPEDWINDOW,
        GetSystemMetrics (SM_CXSCREEN) / 4,
        GetSystemMetrics (SM_CYSCREEN) / 4,
        800, 600,
        // GetSystemMetrics (SM_CXSCREEN) / 2,
        // GetSystemMetrics (SM_CYSCREEN) / 2,
        NULL, NULL, g_hinst, iValue) ;

   if (hwnd == NULL) {
      syslog("CreateWindow: %s\n", get_system_message()) ;
      return 0;
   }
   ShowWindow(hwnd, SW_SHOW) ;
   UpdateWindow(hwnd) ;
   // hAccel = LoadAccelerators (hInstance, szEditName) ;

   MSG      msg ;
//  interesting...  If I enable USE_GETMESSAGE_HWND, and use hwnd in GetMessage(),
//  then PostQuitMessage() does not terminate the message loop!!
//  Actually, this problem only occurs if the message handler is a Window.
//  Dialogs terminate just fine in this case.
// #ifdef  USE_GETMESSAGE_HWND
//    while (GetMessageA (&msg, hwnd, 0, 0)) {
// #else
   while (GetMessage(&msg, NULL, 0, 0)) {
// #endif
      TranslateMessage (&msg) ;
      DispatchMessage (&msg) ;
   }
   // syslog("EditWin: thread exiting\n") ;
   return msg.wParam ;
}

//****************************************************************************
void open_edit_window(void)
{
   if (SendBufThread == NULL) 
      SendBufThread = new CThread(fEditThread, (LPVOID) NULL, NULL) ;
}

