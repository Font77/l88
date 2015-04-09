#pragma once
#define VK_ADD            0x6B
#define VK_SUBTRACT       0x6D

#define VK_SPACE          0x20
#define VK_DELETE         0x2E
#define VK_BACK           0x08

#define VK_LEFT           0x25
#define VK_HOME           0x24
#define VK_RIGHT          0x27
#define VK_END            0x23
#define VK_UP             0x26
#define VK_PRIOR          0x21
#define VK_DOWN           0x28
#define VK_NEXT           0x22

#define VK_SNAPSHOT       0x2C

#define VK_RETURN         0x0D
#define VK_TAB            0x09
#define VK_ESCAPE         0x1B

#define VK_LWIN           0x5B
#define VK_APPS           0x5D

#define VK_CAPITAL        0x14
#define VK_NUMLOCK        0x90

#define VK_SHIFT          0x10
#define VK_CONTROL        0x11

#define BST_UNCHECKED      0x0000
#define BST_CHECKED        0x0001


class Code7
{
public:
	Code7(void);
	~Code7(void);
	static bool sendEnglishCode(int mkc16);
	static bool sendSymbolCode(int mkc16);
	static int getU8SymbolCode(int mkc16);
	static bool sendU8IndicCode(int mkc16,int curLang,bool& isPrevSpaceMatraVovel);
	static bool sendDecimalCode(int mkc16);
	static bool getNavCode(int mkc16,int _flag123AaSftCtrl,bool& isPrevSpaceMatraVovel);
	static char getSymbolCode(int mkc16);
	static bool sendU8SymbolCode(int mkc16);
   static int getU8IndicCode(int mkc16,int curLang,bool& isPrevSpaceMatraVovel);
};
