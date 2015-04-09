//#include "StdAfx.h"
#include "Keys16.h"

Keys16::Keys16(void)
{
   //BitBlt( hDC, 2, 32, from DrawKeyBoard
   LONG left12 = 2; LONG top12 = 32;
   LONG w035 = 45; LONG h0357 = 28;
   LONG w12467 = 30; LONG h1246 = 42;
   LONG gapkeys = 2; LONG gap1246 = 4;

   rectkeys[12].left = left12 ;
   rectkeys[12].right = rectkeys[12].left + w12467 ;
   rectkeys[12].top = top12 ;
   rectkeys[12].bottom = rectkeys[12].top + h1246 ;	

   rectkeys[14].left = rectkeys[12].left ;
   rectkeys[14].right = rectkeys[12].right ;
   rectkeys[14].top = rectkeys[12].bottom + gap1246 ;
   rectkeys[14].bottom = rectkeys[14].top + h1246 ;

   rectkeys[11].left = rectkeys[12].right + gapkeys ;
   rectkeys[11].right = rectkeys[11].left +  w035 ;
   rectkeys[11].top = rectkeys[12].top ;
   rectkeys[11].bottom = rectkeys[11].top + h0357 ;

   rectkeys[13].left = rectkeys[11].left ;
   rectkeys[13].right = rectkeys[11].right ;
   rectkeys[13].top = rectkeys[11].bottom + gapkeys ;
   rectkeys[13].bottom = rectkeys[13].top + h0357 ;

   rectkeys[8].left = rectkeys[11].left ;
   rectkeys[8].right = rectkeys[11].right ;
   rectkeys[8].top = rectkeys[13].bottom + gapkeys ;
   rectkeys[8].bottom = rectkeys[8].top + h0357 ;

   rectkeys[10].left = rectkeys[11].right + gapkeys ;
   rectkeys[10].right = rectkeys[10].left + w12467 ;
   rectkeys[10].top = top12 ;
   rectkeys[10].bottom = rectkeys[12].bottom ;	

   rectkeys[9].left = rectkeys[10].left ;
   rectkeys[9].right = rectkeys[10].right ;
   rectkeys[9].top = rectkeys[14].top ;
   rectkeys[9].bottom = rectkeys[14].bottom ;

   rectkeys[15].left = rectkeys[10].right + gapkeys ;
   rectkeys[15].right = rectkeys[15].left + w12467 ;
   rectkeys[15].top = top12 ;
   rectkeys[15].bottom = rectkeys[12].bottom ;	

   rectkeys[7].left = rectkeys[15].left ;
   rectkeys[7].right = rectkeys[15].right ;
   rectkeys[7].top = rectkeys[14].top ;
   rectkeys[7].bottom = rectkeys[14].bottom ;

   rectkeys[4].left = rectkeys[15].right + gapkeys ;
   rectkeys[4].right = rectkeys[4].left + w12467 ;
   rectkeys[4].top = top12 ;
   rectkeys[4].bottom = rectkeys[12].bottom ;	

   rectkeys[6].left = rectkeys[4].left ;
   rectkeys[6].right = rectkeys[4].right ;
   rectkeys[6].top = rectkeys[14].top ;
   rectkeys[6].bottom = rectkeys[14].bottom ;

   rectkeys[3].left = rectkeys[6].right + gapkeys ;
   rectkeys[3].right = rectkeys[3].left +  w035 ;
   rectkeys[3].top = rectkeys[11].top ;
   rectkeys[3].bottom = rectkeys[11].bottom ;

   rectkeys[5].left = rectkeys[3].left ;
   rectkeys[5].right = rectkeys[3].right ;
   rectkeys[5].top = rectkeys[13].top ;
   rectkeys[5].bottom = rectkeys[13].bottom ;

   rectkeys[0].left = rectkeys[3].left ;
   rectkeys[0].right = rectkeys[3].right ;
   rectkeys[0].top = rectkeys[8].top ;
   rectkeys[0].bottom = rectkeys[8].bottom ;

   rectkeys[2].left = rectkeys[0].right + gapkeys ;
   rectkeys[2].right = rectkeys[2].left + w12467 ;
   rectkeys[2].top = top12 ;
   rectkeys[2].bottom = rectkeys[12].bottom ;	

   rectkeys[1].left = rectkeys[2].left ;
   rectkeys[1].right = rectkeys[2].right ;
   rectkeys[1].top = rectkeys[14].top ;
   rectkeys[1].bottom = rectkeys[14].bottom ;

}

Keys16::~Keys16(void)
{
}
