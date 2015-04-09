#pragma once

class WinKeySender
{
public:
	WinKeySender(void);
	~WinKeySender(void);
	static bool sendNAVCodeDecimal(WORD charcode, int kcode, int flags );
};
