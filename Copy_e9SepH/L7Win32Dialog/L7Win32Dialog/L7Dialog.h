#pragma once
#include <windows.h>
#include "LCD16.h"
#include "Keypad7.h"
#include "WinKeySender.h"
#include "MKC16.h"
class L7Dialog
{
public:
	L7Dialog(void);
	~L7Dialog(void);
	MKC16 mkc16I;
private:
	int _16bitsMkcVal;//0x8080 ;
	int _prevPressedIndex;
	int _vhichSevenKey;
	int _prevId;
	bool is7KCFilled;
	LCD16* lcd;

public:
	//int DescribeKeyState();
	void Draw2LEDs(HWND hWnd);
	void processKeyDaunCommon(HWND hWnd,int buttonIndex);
	void syncCheckBoxes(void);
	void OnLButtonDown(HWND hWnd, LPARAM lParam);
};
