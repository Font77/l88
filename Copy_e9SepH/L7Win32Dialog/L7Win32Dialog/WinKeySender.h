#pragma once
#include <windows.h>
class WinKeySender
{
public:
	WinKeySender(void);
	~WinKeySender(void);
	static bool sendNAVCodeDecimal(unsigned short charcode, int kcode, int flags );
};
