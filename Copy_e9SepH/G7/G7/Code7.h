#pragma once

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
