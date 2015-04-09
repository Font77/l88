#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "L7Dialog.h"
#include "LCD16.h"
#include "WinKeySender.h"
#include "MKC16.h"
//#include "Code7.h"
// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("L7 Win32");

#define ID_123 1
#define ID_Aa 2
#define ID_SIFT 3
#define ID_CTRL 4

HINSTANCE hInst;
//HWND hWnd;
L7Dialog L7dialog;
HFONT hFont;
// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wcex;
	 wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T(""), NULL);
        return 1;
    }
    hInst = hInstance; // Store instance handle in our global variable
    hFont = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial Unicode MS");
    HWND hWnd = CreateWindowEx(
       WS_EX_TOPMOST
       | WS_EX_NOACTIVATE
       | WS_EX_APPWINDOW 
       //|WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE
       ,
        szWindowClass, szTitle,
        
          WS_SYSMENU | WS_POPUP | WS_THICKFRAME
         //|  WS_BORDER
         | WS_CAPTION
         | WS_VISIBLE,
		10,10,
        //CW_USEDEFAULT, CW_USEDEFAULT,
		280,64,
		//L7dialog.rectkeys[1].right+20, L7dialog.rectkeys[1].bottom+40,
        NULL,NULL,hInstance, NULL);
    if (!hWnd)//if (!hWnd)
    {
        MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Win32 Guided Tour"), NULL);
        return 1;
    }
    ShowWindow(hWnd, nCmdShow);//ShowWindow(hWnd, nCmdShow); UpdateWindow(hWnd);
    //UpdateWindow(hWnd);
    MSG msg;// Main message loop:
    while (GetMessage(&msg, NULL, 0, 0)) { TranslateMessage(&msg); DispatchMessage(&msg); }
	return (int) msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
static HWND hwndCombo;
const TCHAR *items[] =
{
   TEXT("Eng"), TEXT("हिनदी"),TEXT("বাংলা"),TEXT("ਪੰਜਾਬੀ"),
   TEXT("ગુજરાતી"), TEXT("ଓଡ଼ିଆ"),TEXT("தமிழ்"), TEXT("తెలుగు"), 
   TEXT("ಕನ್ನಡ"), TEXT("മലയാളം")
};
  LRESULT sel = 0;
    switch (message)
    {
      case WM_CREATE:

          CreateWindow(L"button", L"12",
                     WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                     40, 2, 40, 25,        
                     hWnd, (HMENU) ID_123, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
          CreateWindow(L"button", L"Aa",
                     WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                     80, 2, 40, 25,        
                     hWnd, (HMENU) ID_Aa, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
          CreateWindow(L"button", L"Sft",
                     WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                     120, 2, 40, 25,        
                     hWnd, (HMENU) ID_SIFT, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
          CreateWindow(L"button", L"Ctr",
                     WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                     160, 2, 40, 25,        
                     hWnd, (HMENU) ID_CTRL, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
         hwndCombo = CreateWindow(TEXT("combobox"), NULL, 
                  WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
                  200, 2, 70, 540, hWnd, NULL, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
         for (int i = 0; i < 10; i++ ) {
                SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM) items[i]);
            }
          //CheckDlgButton(hWnd, 1, BST_CHECKED);
      break;
      case WM_COMMAND:
      {
	      if (HIWORD(wParam) == BN_CLICKED) 
         {
	          switch (LOWORD(wParam))
             {
               case ID_Aa:
                  L7dialog.mkc16I._flag123AaSftCtrl |= 2;
                  if (IsDlgButtonChecked(hWnd, ID_Aa))
                  {
                     CheckDlgButton(hWnd, ID_Aa, BST_UNCHECKED);
                     L7dialog.mkc16I._flag123AaSftCtrl ^= 2;
                  }
                  else
                  {
                     CheckDlgButton(hWnd, ID_Aa, BST_CHECKED);
                  }
                  WinKeySender::sendNAVCodeDecimal(VK_CAPITAL,0,0);
                break;
		          case ID_123:
                  L7dialog.mkc16I._flag123AaSftCtrl |= 1;
                  if (IsDlgButtonChecked(hWnd, ID_123))
                  {
                     CheckDlgButton(hWnd, ID_123, BST_UNCHECKED);
                     L7dialog.mkc16I._flag123AaSftCtrl ^= 1;
                  }
                  else
                  {
                     CheckDlgButton(hWnd, ID_123, BST_CHECKED);
                  }
                  WinKeySender::sendNAVCodeDecimal(VK_NUMLOCK,0,0);
                break;
		          case ID_SIFT:
                  L7dialog.mkc16I._flag123AaSftCtrl |= 4;
                  keybd_event(VK_SHIFT,0,0,0);
                  if (IsDlgButtonChecked(hWnd, ID_SIFT))
                  {
                     CheckDlgButton(hWnd, ID_SIFT, BST_UNCHECKED);
                     L7dialog.mkc16I._flag123AaSftCtrl ^= 4;
                     keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                  }
                  else
                  {
                     CheckDlgButton(hWnd, ID_SIFT, BST_CHECKED);
                  }
                break;
		          case ID_CTRL:
                  L7dialog.mkc16I._flag123AaSftCtrl |= 8;
                  keybd_event(VK_CONTROL,0,0,0);
                  if (IsDlgButtonChecked(hWnd, ID_CTRL))
                  {
                     CheckDlgButton(hWnd, ID_CTRL, BST_UNCHECKED);
                     L7dialog.mkc16I._flag123AaSftCtrl ^= 8;
                     keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
                  }
                  else
                  {
                     CheckDlgButton(hWnd, ID_CTRL, BST_CHECKED);
                  }
                break;
             }
	          //InvalidateRect(hwnd, NULL, TRUE);
	      }
         if(HIWORD(wParam) == CBN_SELCHANGE)
         {
            //int selection;
            L7dialog.mkc16I._curLang = SendMessage (hwndCombo,CB_GETCURSEL,NULL,NULL);
            //CB_SETCURSEL

         }
         break;
      }
      case WM_PAINT: L7dialog.Draw2LEDs(hWnd); break;
      case WM_MOUSEMOVE: SetActiveWindow(hWnd); break;
      case WM_NCLBUTTONDOWN:
         if(20 == LOWORD(wParam)) { SendMessage(hWnd, WM_CLOSE, 0, 0); return true; }
         else SetForegroundWindow(hWnd);
      break;
      case WM_DESTROY:
         PostQuitMessage(0);
      break;
      case WM_LBUTTONDOWN:
         L7dialog.OnLButtonDown(hWnd, lParam);
      break;
      case WM_QUIT:
         PostQuitMessage(0);
      break;
      case WM_SETFONT:
         //SendMessage(hwndCombo, WM_SETFONT, (WPARAM)hFont, TRUE);
         SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, TRUE);
         break;
      default: return DefWindowProc(hWnd, message, wParam, lParam); break;
    }
    return 0;
}
