#ifndef WINKEYSENDER_H
#define WINKEYSENDER_H
#include <windows.h>
class WinKeySender
{
public:
	WinKeySender(void);
	~WinKeySender(void);
	static bool sendNAVCodeDecimal(unsigned short charcode, int kcode, int flags );
};
#endif //WINKEYSENDER_H