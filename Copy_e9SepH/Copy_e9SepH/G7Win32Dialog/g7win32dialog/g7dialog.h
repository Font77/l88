#ifndef G7DIALLOG_H
#define G7DIALLOG_H
#include <windows.h>
#include "Lcd16.h"
#include "Keys16.h"
#include "WinKeySender.h"
#include "MKC16.h"
class G7Dialog
{
public:
	G7Dialog(void);
	~G7Dialog(void);
	MKC16 mkc16I;
private:
	int _16bitsMkcVal;//0x8080 ;
	int _prevPressedIndex;
	int _vhichSevenKey;
	int _prevId;
	bool is7KCFilled;
	Lcd16* lcd;
   Keys16 keypad7;

public:
	//int DescribeKeyState();
	void Draw2LEDs(HWND hWnd);
	void processKeyDaunCommon(HWND hWnd,int buttonIndex);
	void syncCheckBoxes(void);
	void OnLButtonDown(HWND hWnd, LPARAM lParam);
   void DrawKeyboard(HWND hWnd,HINSTANCE _hInst);//(HDC hDC);//
   //BOOL LoadBitmapFromBMPFile( LPTSTR szFileName, HBITMAP *phBitmap,HPALETTE *phPalette );
};
#endif //G7DIALLOG_H