#include "StdAfx.h"
#include "WinKeySender.h"

WinKeySender::WinKeySender(void)
{
}

WinKeySender::~WinKeySender(void)
{
}

bool WinKeySender::sendNAVCodeDecimal(WORD a_VKCode, int a_WScanCode, int keyflags )
{
   bool is7KCFilled = false;
   WORD vKCode = a_VKCode;
   int wScanCode = a_WScanCode;
   INPUT input[4];
   if((!is7KCFilled) && vKCode )
   {
      input[0].type = INPUT_KEYBOARD; input[1].type = INPUT_KEYBOARD;
      input[2].type = INPUT_KEYBOARD; input[3].type = INPUT_KEYBOARD;
      if((!is7KCFilled) && (keyflags & 1)) //Ctrl key
      {
         input[0].ki.wVk = VK_CONTROL; input[0].ki.wScan = 0;input[0].ki.dwFlags = 0;			
         input[1].ki.wVk = vKCode; input[1].ki.wScan = 0;input[1].ki.dwFlags = 0;			
         input[2].ki.wVk = vKCode; input[2].ki.wScan = 0;input[2].ki.dwFlags = KEYEVENTF_KEYUP;			
         input[3].ki.wVk = VK_CONTROL; input[3].ki.wScan = 0;input[3].ki.dwFlags = KEYEVENTF_KEYUP;
         SendInput(4, input, sizeof(INPUT)); is7KCFilled = true;
      }
      //if((!is7KCFilled) && (keyflags & 2)) //Shift key
      //{
      //   input[0].ki.wVk = VK_SHIFT; input[0].ki.wScan = 0;input[0].ki.dwFlags = 0;			
      //   input[1].ki.wVk = vKCode; input[1].ki.wScan = 0;input[1].ki.dwFlags = 0;			
      //   input[2].ki.wVk = vKCode; input[2].ki.wScan = 0;input[2].ki.dwFlags = KEYEVENTF_KEYUP;			
      //   input[3].ki.wVk = VK_SHIFT; input[3].ki.wScan = 0;input[3].ki.dwFlags = KEYEVENTF_KEYUP;
      //   SendInput(4, input, sizeof(INPUT)); is7KCFilled = true;
      //}
      if((!is7KCFilled) && (keyflags & 4)) //Alt key
      {
         input[0].ki.wVk = VK_MENU; input[0].ki.wScan = 0;input[0].ki.dwFlags = 0;			
         input[1].ki.wVk = vKCode; input[1].ki.wScan = 0;input[1].ki.dwFlags = 0;			
         input[2].ki.wVk = vKCode; input[2].ki.wScan = 0;input[2].ki.dwFlags = KEYEVENTF_KEYUP;
         input[3].ki.wVk = VK_MENU; input[3].ki.wScan = 0;input[3].ki.dwFlags = KEYEVENTF_KEYUP;
         SendInput(4, input, sizeof(INPUT)); is7KCFilled = true;
      }
      if((!is7KCFilled) && (keyflags & 8)) //Alt key
      {
         input[0].ki.wVk = VK_LWIN; input[0].ki.wScan = 0;input[0].ki.dwFlags = 0;			
         input[1].ki.wVk = vKCode; input[1].ki.wScan = 0;input[1].ki.dwFlags = 0;			
         input[2].ki.wVk = vKCode; input[2].ki.wScan = 0;input[2].ki.dwFlags = KEYEVENTF_KEYUP;
         input[3].ki.wVk = VK_LWIN; input[3].ki.wScan = 0;input[3].ki.dwFlags = KEYEVENTF_KEYUP;
         SendInput(4, input, sizeof(INPUT)); is7KCFilled = true;
      }      
      if((!is7KCFilled))
      {
         input[0].ki.wVk = vKCode; input[0].ki.wScan = 0;input[0].ki.dwFlags = 0;			
         input[1].ki.wVk = vKCode; input[1].ki.wScan = 0;input[1].ki.dwFlags = KEYEVENTF_KEYUP;
         SendInput(2, input, sizeof(INPUT)); is7KCFilled = true;
      }//VK_DOWN ,[0-9],Enter,Tab,[a-z,A-Z]
   }
   if((!is7KCFilled) && wScanCode ) //'\t' ,अ,≡,symbols(",@,+,...),spacebar,fullstop
   {
      KEYBDINPUT kb={0}; kb.wScan = wScanCode;
      INPUT Input1={0};INPUT Input2={0};
      Input1.type = INPUT_KEYBOARD;Input2.type = INPUT_KEYBOARD;							
      kb.dwFlags = KEYEVENTF_UNICODE; Input1.ki = kb; ::SendInput(1,&Input1,sizeof(Input1));
      kb.dwFlags = KEYEVENTF_UNICODE|KEYEVENTF_KEYUP; Input2.ki = kb; ::SendInput(1,&Input2,sizeof(Input2));
      is7KCFilled = true;
   }
   return is7KCFilled;
}
