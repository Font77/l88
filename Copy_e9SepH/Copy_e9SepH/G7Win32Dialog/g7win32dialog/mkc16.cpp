#include "MKC16.h"
#include "Code7.h"
MKC16::MKC16(void)
{
   _flag123AaSftCtrl = 0;
   _curLang = 0;
   isPrevSpaceMatraVovel = true;
}

MKC16::~MKC16(void)
{
}

bool MKC16::handleMKC16(int mkc16)
{
   bool is7KCFilled = false;
   int hbyte = (mkc16 & 0xFF00) >> 8;
   int lbyte = (mkc16 & 0x00FF);   
   if (!is7KCFilled)
   {
      if
      (
            (
               (_flag123AaSftCtrl & 1)
               &&
               ( 0xFC == (0xFC & hbyte) )// A,B,C,D,E,F are not pressed , ignore 4,6
            )
            ||
            (
               (!(_flag123AaSftCtrl & 1))
               &&
               ( 0xEC == (0xFC & hbyte) ) // A,B,D,E,F are not pressed and C is pressed ignore 4,6
            )
       )
       {
		 is7KCFilled = Code7::sendDecimalCode(mkc16);
       }
   }

   if (!is7KCFilled)
   {
	   is7KCFilled = Code7::getNavCode(mkc16,_flag123AaSftCtrl,isPrevSpaceMatraVovel);
   }
   
   if
   (
      (!is7KCFilled)
      &&
      (
         0xF700 == (mkc16 & 0xF700)
      )
   )
   {
      if
      (
         //(!_curLang)
         ( (!_curLang) || (_flag123AaSftCtrl & 8) )
      )
      {
		 is7KCFilled = Code7::sendEnglishCode(mkc16);
		 if(is7KCFilled) { isPrevSpaceMatraVovel = true; }
      }
   }

   if
   (
      !(is7KCFilled)
      &&
      (
         (0xFF00 == (mkc16 & 0xFF00)) || (0 == (mkc16 & 0x00FF))
      )
   )
   {
	   is7KCFilled = Code7::sendSymbolCode(mkc16);
	   if(is7KCFilled) { isPrevSpaceMatraVovel = true; }
   }
   if
   (
      !(is7KCFilled)
      &&
      (
         (0xFF00 == (mkc16 & 0xFF00)) || (0 == (mkc16 & 0x00FF))
      )
   )
   {
	   is7KCFilled = Code7::sendU8SymbolCode(mkc16);
	   if(is7KCFilled) { isPrevSpaceMatraVovel = true; }
   }
   if
   (
      !(is7KCFilled)
      &&
      (
         (0xFF00 == (mkc16 & 0xFF00))
      )
      &&
      (_curLang)
   )
   {
      is7KCFilled = Code7::sendU8IndicCode(mkc16,_curLang,isPrevSpaceMatraVovel);
   }
   return 0;
}