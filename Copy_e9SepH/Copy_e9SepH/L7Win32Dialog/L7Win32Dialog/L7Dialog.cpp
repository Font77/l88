#include "L7Dialog.h"
#include "Code7.h"
#include "WinKeySender.h"
L7Dialog::L7Dialog(void)
{
   mkc16I._flag123AaSftCtrl = 0;
   _16bitsMkcVal = 0xff80;//65408;//0x8080 ;
   _prevPressedIndex = 20;
   _vhichSevenKey = 0;
   _prevId=20;
   is7KCFilled = false;
   mkc16I._curLang = 0;
   mkc16I.isPrevSpaceMatraVovel = true;
   lcd = new LCD16(2,20,2,2);
}

L7Dialog::~L7Dialog(void)
{
}
void L7Dialog::processKeyDaunCommon(HWND hWnd,int buttonIndex)
{
   if(16==buttonIndex) buttonIndex = 7;
   if(17==buttonIndex) buttonIndex = 15;
   int _bitCheckerSetter = 1<<buttonIndex;
   _16bitsMkcVal ^= _bitCheckerSetter ;
   Draw2LEDs(hWnd);
}
void L7Dialog::OnLButtonDown(HWND hWnd, LPARAM lParam)//(int keyindex)
{
   POINT p; p.x =  LOWORD(lParam); p.y =  HIWORD(lParam);
   for(int i=0; i<18 ; i++)
   {
      if( PtInRect(&(lcd->rectLED[i]),p ))
      {
         if(i==_prevId)
         {
            mkc16I.handleMKC16(_16bitsMkcVal);
            _prevId = 20;	
            _16bitsMkcVal = 65408;//0x8080 ;
            Draw2LEDs(hWnd);
            InvalidateRect(hWnd,&(lcd->rectLED2),true);
            InvalidateRect(hWnd,&(lcd->rectLED1),true);
         }
         else
         {
            _prevId = i;processKeyDaunCommon(hWnd,i);
            if((i<8) || (16==i)) InvalidateRect(hWnd,&(lcd->rectLED2),true);
            else InvalidateRect(hWnd,&(lcd->rectLED1),true);
         }
         break ;
      }
   }
}
void L7Dialog::Draw2LEDs(HWND hWnd)
{
   PAINTSTRUCT ps; HDC hdc; hdc = BeginPaint(hWnd, &ps);
   HBRUSH brushBlack , brushRed , brushGreen , brushWhite;
   brushBlack=CreateSolidBrush(RGB(0,0,0));
   brushRed=CreateSolidBrush(RGB(255,0,0));
   brushGreen=CreateSolidBrush(RGB(0,255,0));
   brushWhite=CreateSolidBrush(RGB(255,255,255));
   for(int i=0;i<8;i++)
   {
      if(_16bitsMkcVal & (1<<i))
         FrameRect(hdc, &(lcd->rectLED[i]), brushWhite );
      else
         FillRect(hdc, &(lcd->rectLED[i]), brushBlack );
   }
   if(_16bitsMkcVal & 128)
      FrameRect(hdc, &(lcd->rectLED[16]), brushWhite );
   else
      FillRect(hdc, &(lcd->rectLED[16]), brushBlack );
      
      
   for(int i=8;i<16;i++)
   {
      if(_16bitsMkcVal & (1<<i))
         FrameRect(hdc,  &(lcd->rectLED[i]), brushGreen );
      else
         FillRect(hdc, &(lcd->rectLED[i]), brushRed );
   }
   if(_16bitsMkcVal & 32768)
      FrameRect(hdc, &(lcd->rectLED[17]), brushGreen );
   else
      FillRect(hdc, &(lcd->rectLED[17]), brushRed );
   DeleteObject(brushBlack);DeleteObject(brushRed);DeleteObject(brushGreen);
}
