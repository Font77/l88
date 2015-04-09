//#include "StdAfx.h"
#include "Code7.h"
#include "WinKeySender.h"
Code7::Code7(void)
{
}

Code7::~Code7(void)
{
}

bool Code7::sendEnglishCode(int mkc16)
{
   char engchar = 0; int keyflags = 0;
   bool is7KCFilled = false;
   int lbyte = mkc16 & 0xFF ;
   int hbyte = (mkc16 & 0xFF00) >> 8 ;
	switch (lbyte)
	{
		case 129: case 144: engchar = 'A'; break;//A,a
		case 192: engchar = 'I'; break;//I
		case 136: case 188: engchar ='U'; break;//U,u
		case 130: case 134: engchar ='E'; break;//e,E
		case 160: engchar = 'O'; break;//O
		case 10: engchar = 'N' ; break;//NN
		case 193: engchar = 'Q'; break;//Q
		case 143: engchar = 'K'; break;//K
		case 65: engchar = 'X'; break;//X
		//case 65: engchar = 88; break;//X
		case 164: case 36: engchar = 'G'; break;//G,Gh
		case 224: case 96: engchar = 'C'; break;//Ch,Chh
		case 48: engchar = 'Z'; break;//Z,Jh
		case 176: engchar = 'J'; break;//J,Jh
		case 132: case 4: case 142: case 14: case 145: case 17: engchar = 'T'; break;//T
		case 152: case 24: case 5: case 133: engchar = 'D'; break;//d,dh,D,Dh
		case 138: case 157: engchar = 'N'; break;//N,NN,n
		case 131: engchar = 'P'; break;//P
		case 135: engchar = 'F'; break;//F
		case 140: case 12: engchar = 'B'; break;//B,Bh
		case 161: engchar = 'M'; break;//M
		case 200: engchar = 'Y'; break;//Y
		case 146: case 18: case 159: engchar = 'R'; break;//R,RR,r
		case 162: case 174: engchar = 'L'; break;//L
		case 168: engchar = 'V'; break;//V
		case 40: engchar = 'W'; break;//W
		case 196: case 68: engchar = 'S'; break;//S,Sh
		case 137: engchar = 'H'; break;//H
	}
   if(engchar)
   {    
	  if(0xF7 == hbyte) WinKeySender::sendNAVCodeDecimal(VK_CAPITAL,0,0);
	  is7KCFilled = WinKeySender::sendNAVCodeDecimal(engchar,0,0);
	  if(0xF7 == hbyte) WinKeySender::sendNAVCodeDecimal(VK_CAPITAL,0,0);
   }
   return is7KCFilled;
}

bool Code7::sendSymbolCode(int mkc16)
{
   int lbyte = mkc16 & 0xFF ;
   int hbyte = (mkc16 & 0xFF00) >> 8 ;
   char tempWSCode = 0;
   bool is7KCFilled = false;
	tempWSCode = getSymbolCode(lbyte);
   if(0 == tempWSCode)
   {
      if (0 == lbyte && 0xEF != hbyte)
      {
         //tempcharCode = Code7::sendSymbolCode(hbyte);
		  tempWSCode = getSymbolCode(hbyte);
      }    
   }
	if(tempWSCode) { is7KCFilled = WinKeySender::sendNAVCodeDecimal(0,tempWSCode,0); }
  //return tempWSCode;
  return is7KCFilled;
}

int Code7::getU8SymbolCode(int mkc16)
{
	int _tempCode = 0;
	switch (mkc16)
	{
		case 95:	_tempCode = 247 ; break;//Mathematic divide symbol
		case 214:	_tempCode = 0x2261 ; break;//== symbol
		case 226:	_tempCode = 0x2229 ; break;//&& symbol
		case 72:	_tempCode = 0x221A ; break;//&& symbol
		case 86:	_tempCode = 0x2260 ; break;//\!= symbol
		case 198:	_tempCode = 0x2264 ; break;//less than or equal to symbol
		case 210:	_tempCode = 0x2265 ; break;//greater than or equal to symbol
		case 188:	_tempCode = 0x2228 ; break;//down v symbol
		case 61:	_tempCode = 0x2191 ; break;//upper arrow
		case 15:	_tempCode = 0x2192 ; break;//right arrow
		case 60:	_tempCode = 0x2193 ; break;//Down arrow
		case 92:	_tempCode = 0x21D2 ; break;//Down arrow
		case 89:	_tempCode = 0x2190 ; break;//Left arrow
		case 107:	_tempCode = 0x2193 ; break;//Down arrow
		case 148:	_tempCode = 0x25B3 ; break;//Triangle
		case 195:	_tempCode = 0x2218 ; break;//AngleDegree
		case 67:	_tempCode = 0x221E ; break;//Infinity
	}
	return _tempCode;
}

bool Code7::sendU8IndicCode(int mkc16,int curLang,bool& isPrevSpaceMatraVovel)
{
   bool is7KCFilled = false;
   int _tempCode = 0;
   _tempCode = getU8IndicCode(mkc16,curLang,isPrevSpaceMatraVovel);
   if(_tempCode)
   {
      is7KCFilled = WinKeySender::sendNAVCodeDecimal(0,_tempCode,0);
   }
   return is7KCFilled;
}

bool Code7::sendDecimalCode(int mkc16)
{
   char tempVKCode = 0;
   bool is7KCFilled = false;
   switch (mkc16)
   {
      case 0xFF00:case 0xEF00:tempVKCode = '0' ;break;
      case 0xFF81:case 0xEF81:tempVKCode = '1' ;break;
      case 0xFF82:case 0xEF82:tempVKCode = '2' ;break;
      case 0xFF84:case 0xEF84:tempVKCode = '3' ;break;
      case 0xFF88:case 0xEF88:tempVKCode = '4' ;break;
      case 0xFF90:case 0xEF90:tempVKCode = '5' ;break;
      case 0xFFA0:case 0xEFA0:tempVKCode = '6' ;break;      
      case 0xFFC0:case 0xEFC0:tempVKCode = '7' ; break;
      case 0xFD80:case 0xED80:tempVKCode = '9' ;break;
      case 0xFE80:case 0xEE80:tempVKCode = '8' ;break;      
   }
   if(tempVKCode) { is7KCFilled = WinKeySender::sendNAVCodeDecimal(tempVKCode,0,0); }
   return is7KCFilled;
}

bool Code7::getNavCode(int mkc16,int _flag123AaSftCtrl,bool& isPrevSpaceMatraVovel)
{
   unsigned short tempVKCode = 0;
   bool is7KCFilled = false ;
   int keyflags = 0;
   switch(mkc16)
   {
      case 0xFD00: tempVKCode = VK_APPS ; break; // Enter
      case 0x7B80: tempVKCode = VK_ESCAPE ; keyflags |= 4; break; //Alt Escape
      case 0x3F80: tempVKCode = VK_ESCAPE ;	break; // Esc
      case 0xFB02: tempVKCode = VK_RETURN ; keyflags |= 4; break; //Alt Enter
      case 0xFF02: tempVKCode = VK_RETURN ; isPrevSpaceMatraVovel = true; 	break; // Enter
      case 0xFB00: tempVKCode = VK_SPACE ; keyflags |= 4; break; //Alt Space
      case 0xFF00: tempVKCode = VK_SPACE ; isPrevSpaceMatraVovel = true; break; // Enter      
      case 0xFB84: tempVKCode = VK_TAB; keyflags |= 4; break; //isAlt = true;// Alt9=AltF
      case 0x7F80: tempVKCode = VK_BACK ;	break; //backspace
      case 0xBF80: tempVKCode = VK_DELETE ;	break; //delete
      case 0xBF84: tempVKCode = VK_TAB ; isPrevSpaceMatraVovel = true; 	break; //mov+tab
      case 0xDF80: tempVKCode = VK_LEFT ; break; //left
      case 0x9F80: tempVKCode = VK_HOME ; break; //HOME
      case 0xF780: tempVKCode = VK_RIGHT ;	break; //right
      case 0xB780: tempVKCode = VK_END ; break; //END      
      case 0xEF80: tempVKCode = VK_UP ; break; //UP
      case 0xAF80: tempVKCode = VK_PRIOR ; break; //PageUP
      case 0xFB80: tempVKCode = VK_DOWN ; break; //DOWN
      case 0xBB80: tempVKCode = VK_NEXT ; break; //PageDOWN
      case 0xFF03: tempVKCode = VK_ADD ; break; //Plus
      case 0xDF00: tempVKCode = VK_SUBTRACT ; break; //Minus
      case 0xFD80: if( !(1 & _flag123AaSftCtrl) ) tempVKCode = VK_SNAPSHOT ; break; //PrintScreen
      case 0xFC80: tempVKCode = VK_SNAPSHOT ; break; //PrintScreen
      case 0xF980: tempVKCode = VK_SNAPSHOT ; keyflags |= 4; break; //Alt PrintScreen

      
      case 0x7F81: tempVKCode = 0x70 ; break; //Fn1
      case 0x7F82: tempVKCode = 0x71 ; break; //Fn2
      case 0x7F84: tempVKCode = 0x72 ; break; //Fn3
      case 0x7F88: tempVKCode = 0x73 ; break; //Fn4
      case 0x7B88: tempVKCode = 0x73; keyflags |= 4; break; //isAlt = true;// Alt4=Alt-F4
      case 0x7F90: tempVKCode = 0x74 ; break; //Fn5
      case 0x7FA0: tempVKCode = 0x75 ; break; //Fn6
      case 0x7FC0: tempVKCode = 0x76 ; break; //Fn7
      case 0x7E80: tempVKCode = 0x77 ; break; //Fn8
      case 0x7D80: tempVKCode = 0x78 ; break; //Fn9
      case 0x7F01: tempVKCode = 0x79 ; break; //Fn10
      case 0x7F83: tempVKCode = 0x7B ; break; //Fn12

      case 0xFF88: if(8 & _flag123AaSftCtrl) tempVKCode = 'Z'; break;
      case 0xFF90: if(8 & _flag123AaSftCtrl) tempVKCode = 'X'; break;      
      case 0xFFC0: if(8 & _flag123AaSftCtrl) tempVKCode = 'C'; break;
      case 0xFF82: if(8 & _flag123AaSftCtrl) tempVKCode = 'V'; break;
      
      case 0xFE80: if( !(1 & _flag123AaSftCtrl) )tempVKCode = VK_LWIN ; break; //Winkey
      case 0xFE00: tempVKCode = VK_LWIN ; break; //Winkey
      case 0xFE81: case 0xFE98: tempVKCode = 'D' ; keyflags |= 8; break; //isWin = true;WinD
      case 0xFE82: tempVKCode = 'E' ; keyflags |= 8; break; //isWin = true;WinE
      case 0xFE84: case 0xFE87: tempVKCode = 'F' ; keyflags |= 8; break; //isWin = true;WinF
      case 0xFE88: case 0xFEA2: tempVKCode = 'L' ; keyflags |= 8; break; //isWin = true;WinL
      case 0xFE90: case 0xFEA1: tempVKCode = 'M' ; keyflags |= 8; break; //isWin = true;WinM
      case 0xFEA0: case 0xFE92: tempVKCode = 'R' ; keyflags |= 8; break; //isWin = true;WinR
   }
   if(tempVKCode )
   {
      is7KCFilled = WinKeySender::sendNAVCodeDecimal(tempVKCode,0,keyflags);
   }
   return is7KCFilled;
}

char Code7::getSymbolCode(int mkc16)
{
	char _tempCode = 0;
	switch (mkc16)
	{
		case 215:	_tempCode = '\t' ; break;//tab
		case 1:		_tempCode = '&' ; break;//&	
		case 16:	_tempCode = '@' ; break;//@	
		case 9:		_tempCode = '#' ; break;//#
		case 28:	_tempCode = '$' ; break;//$
		case 223:	_tempCode = '-' ; break;//hyphen
		case 156:	_tempCode = '.' ; break;//ABRR/FULSTOP
		case 147:	_tempCode = '?' ; break;//QUESTION MARK
		case 199:	_tempCode = '~' ; break;//TILDE
		case 166:	_tempCode = '[' ; break;//[
		case 38:	_tempCode = '(' ; break;//(
		case 6:		_tempCode = '{' ; break;//(
		case 240:	_tempCode = ']' ; break;//]
		case 112:	_tempCode = ')' ; break;//)
		case 80:	_tempCode = '}' ; break;//}
		case 254:case 247:	_tempCode = '_' ; break;//_
		case 222:	_tempCode = '=' ; break;//=
		case 127:	_tempCode = ':' ; break;//:
		case 235:	_tempCode = 34 ; break;//"
		case 124:	_tempCode = ';' ; break;//;
		case 252:	_tempCode = ',' ; break;//,
		case 220:	_tempCode = '>' ; break;//>
		case 158:	_tempCode = '<' ; break;//<
		case 227:	_tempCode = '^' ; break;//^
		case 180:	_tempCode = '~' ; break;//~
		case 243:	_tempCode = '`' ; break;//` backquoteascii=96
		case 231:	_tempCode = 39 ; break;//'92=backslashascii , 47=forfawrdslashascii , 39=singlequoteascii
		case 27:	_tempCode = '%' ; break;//%
		case 205:	_tempCode = 92 ; break;
		case 155:	_tempCode = '/' ; break;////
		case 3:		_tempCode = '+' ; break;//+
		case 33:	_tempCode = '*' ; break;//*
		case 169:	_tempCode = '|' ; break;//|
		case 126:	_tempCode = '!' ; break;//\!
	}
	return _tempCode;
}

bool Code7::sendU8SymbolCode(int mkc16)
{
   int tempUTFLCode = 0;
   bool is7KCFilled = false;
   int lbyte = mkc16 & 0xFF ;
   int hbyte = (mkc16 & 0xFF00) >> 8 ;
   tempUTFLCode = getU8SymbolCode(lbyte);
   if(!tempUTFLCode)
   {
      if (0 == lbyte && 0xEF != hbyte)
      {
         tempUTFLCode = getU8SymbolCode(hbyte);
      }    
   }
   if(tempUTFLCode)
   {    
      is7KCFilled = WinKeySender::sendNAVCodeDecimal(0,tempUTFLCode,0);
   }
   return is7KCFilled;
}

int Code7::getU8IndicCode(int mkc16,int curLang,bool& isPrevSpaceMatraVovel)
{
   //bool is7KCFilled = false;
   int lbyte = mkc16 & 0x00FF ;
   int _tempCode = 0;
   switch (lbyte)
   {
      case 129:_tempCode = 5;break;//VOWELS BELOW
      case 144:_tempCode = isPrevSpaceMatraVovel ? 6:0x3E;break;//a
      case 64:_tempCode = isPrevSpaceMatraVovel ? 8:0x40;break;//I
      case 192:_tempCode = isPrevSpaceMatraVovel ? 7:0x3F;break;//I
      case 188: case 136:_tempCode = isPrevSpaceMatraVovel ? 9:0x42;break;//u,U
      case 130:case 134:_tempCode = isPrevSpaceMatraVovel ? 0x10:0x47;break;//e,E
      case 160:_tempCode = isPrevSpaceMatraVovel ? 0x13:0x4B;break;//O
      case 32:_tempCode = isPrevSpaceMatraVovel ? 0x14:0x4C;break;//O
   }
  if(_tempCode) {isPrevSpaceMatraVovel = true;}

  if(6==curLang && (!_tempCode))
  {
    switch (lbyte)
    {
      case 65: case 164: case 36: _tempCode = 0x15;break;//q,K
      case 96:_tempCode = 0x1A;break;//C,Ch
      case 48:_tempCode = 0x1C;break;//Jh
      case 4: case 14: case 152: case 24:_tempCode = 0x1F;break;//dh
      case 17: case 133: case 5:_tempCode = 0x24;break;//DDh
      case 135: case 140: case 12:_tempCode = 0x2A;break;//bh
    }
    if(_tempCode) {isPrevSpaceMatraVovel = false;}
  }
  if(!_tempCode)
  {
    switch (lbyte)
    {
      case 193: case 143: _tempCode = 0x15;break;//q,K
      case 65:_tempCode = 0x16;break;//Kh
      case 164:_tempCode = 0x17;break;//G
      case 36:_tempCode = 0x18 ;break;//Gh
      case 10:_tempCode = 2 ; break;//NN
      case 224: case 158:_tempCode = 0x1A;break;//C,c
      case 96:_tempCode = 0x1B;break;//Ch
      case 176:_tempCode = 0x1C;break;//J
      case 48:_tempCode = 0x1D;break;//Jh
      case 132: case 142: _tempCode = 0x1F;break;//6(t),t
      case 4: case 14: _tempCode = 0x20;break;//6(th),th
      case 152:_tempCode = 0x21;break;//d
      case 24:_tempCode = 0x22;break;//dh
      case 145:_tempCode = 0x24;break;//TT
      case 17:_tempCode = 0x25;break;//TTh
      case 133:_tempCode = 0x26;break;//DD
      case 5:_tempCode = 0x27;break;//DDh
      case 138: case 157: _tempCode = 0x28;break;//N,n
      case 131:_tempCode = 0x2A;break;//P
      case 135:_tempCode = 0x2B;break;//F
      case 140:_tempCode = 0x2C;break;//b
      case 12:_tempCode = 0x2D;break;//bh
      case 161:_tempCode = 0x2E;break;//M
      case 200:_tempCode = 0x2F;break;//Y
      case 146: case 159: _tempCode = 0x30;break;//R,r
      case 18:_tempCode = 0x5C;break;//RR
      case 162: case 174: _tempCode = 0x32;break;//Lbent,L
      case 168: case 40: _tempCode = 0x35;break;//V,W
      case 196:_tempCode = 0x38;break;//S
      case 68:_tempCode = 0x36;break;//Sh
      case 137:_tempCode = 0x39;break;//H
    }
    if(_tempCode) {isPrevSpaceMatraVovel = false;}
  }
  if(_tempCode)
  {
    _tempCode += (0x900+(curLang-1) * (128));
  }
  return _tempCode;
}
