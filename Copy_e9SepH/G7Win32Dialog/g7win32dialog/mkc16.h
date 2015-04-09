#ifndef MKC16_H
#define MKC16_H

class MKC16
{
public:
   MKC16(void);
   ~MKC16(void);
   int _flag123AaSftCtrl;
	int _curLang;
	bool isPrevSpaceMatraVovel;   
   bool handleMKC16(int mkc16);
};
#endif //MKC16_H