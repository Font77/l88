#include "LCD16.h"
LCD16::~LCD16(void)
{
}
LCD16::LCD16(int a_ledTop, int a_led4left, int a_led12left, int a_w)
{
	ledTop = a_ledTop;
	led4left = a_led4left; led12left = a_led12left;
	led1246w = led035h = a_w;
	led035w = led1246h = 5*a_w;
	dplength = 3*a_w; dpgap = a_w;
//int led035w = 14; int led035h = 2;
//int led1246w = 2; int led1246h = 14;
//int led4left = 236; int ledTop = 4;
//int led12left = 2; 
//int dplength = 6; int dpgap = 4;
	//2nd LED					
	rectLED[12].left = led12left; rectLED[12].right = rectLED[12].left + led1246w;
	rectLED[11].top = ledTop; rectLED[11].bottom = rectLED[11].top + led035h;
	rectLED[11].left = rectLED[12].right ; rectLED[11].right = rectLED[11].left + led035w;
	rectLED[12].top = rectLED[11].bottom ; rectLED[12].bottom = rectLED[12].top + led1246h;
	
	rectLED[13].top = rectLED[12].bottom ; rectLED[13].bottom = rectLED[13].top + led035h ;
	rectLED[13].left = rectLED[11].left ; rectLED[13].right = rectLED[11].right ;
	rectLED[14].top = rectLED[13].bottom ; rectLED[14].bottom = rectLED[14].top + led1246h;
	rectLED[14].left = rectLED[12].left; rectLED[14].right = rectLED[12].right ;

	rectLED[10].left = rectLED[11].right ; rectLED[10].right = rectLED[10].left + led1246w;
	rectLED[10].top = rectLED[12].top ; rectLED[10].bottom = rectLED[12].bottom ;
	rectLED[9].left = rectLED[10].left ; rectLED[9].right = rectLED[10].right ;
	rectLED[9].top = rectLED[14].top ; rectLED[9].bottom = rectLED[14].bottom ;

	rectLED[8].top = rectLED[9].bottom ; rectLED[8].bottom = rectLED[8].top + led035h ;
	rectLED[8].left = rectLED[11].left; rectLED[8].right = rectLED[11].right ;

	//2dp
	rectLED[15].top = rectLED[11].bottom + dpgap ; rectLED[15].bottom = rectLED[15].top + dplength;
	rectLED[15].left = rectLED[13].left + dpgap ; rectLED[15].right = rectLED[15].left + dplength ;
	rectLED[17].top = rectLED[13].bottom + dpgap ; rectLED[17].bottom = rectLED[17].top + dplength;
	rectLED[17].left=rectLED[15].left ; rectLED[17].right=rectLED[15].right;

	
	//1st LED //int led4left = 264; int led3Top = 36;
	rectLED[4].left = led4left; rectLED[4].right = rectLED[4].left + led1246w;
	rectLED[3].top = ledTop; rectLED[3].bottom = rectLED[3].top + led035h;
	rectLED[3].left = rectLED[4].right ; rectLED[3].right = rectLED[3].left + led035w;
	rectLED[4].top = rectLED[3].bottom ; rectLED[4].bottom = rectLED[4].top + led1246h;
	
	rectLED[5].top = rectLED[4].bottom ; rectLED[5].bottom = rectLED[5].top + led035h ;
	rectLED[5].left = rectLED[3].left ; rectLED[5].right = rectLED[3].right ;
	rectLED[6].top = rectLED[5].bottom ; rectLED[6].bottom = rectLED[6].top + led1246h;
	rectLED[6].left = rectLED[4].left; rectLED[6].right = rectLED[4].right ;

	rectLED[2].left = rectLED[3].right ; rectLED[2].right = rectLED[2].left + led1246w;
	rectLED[2].top = rectLED[4].top ; rectLED[2].bottom = rectLED[4].bottom ;
	rectLED[1].left = rectLED[2].left ; rectLED[1].right = rectLED[2].right ;
	rectLED[1].top = rectLED[6].top ; rectLED[1].bottom = rectLED[6].bottom ;

	rectLED[0].top = rectLED[1].bottom ; rectLED[0].bottom = rectLED[0].top + led035h ;
	rectLED[0].left = rectLED[3].left; rectLED[0].right = rectLED[3].right ;

	//1dp
	rectLED[7].top = rectLED[3].bottom + dpgap ; rectLED[7].bottom = rectLED[7].top + dplength;
	rectLED[7].left = rectLED[5].left + dpgap ; rectLED[7].right = rectLED[7].left + dplength ;
	rectLED[16].top = rectLED[5].bottom + dpgap ; rectLED[16].bottom = rectLED[16].top + dplength;
	rectLED[16].left=rectLED[7].left ; rectLED[16].right=rectLED[7].right;

	rectLED1.top = rectLED[11].top-1;
	rectLED1.left = rectLED[12].left-1;
	rectLED1.bottom = rectLED[8].bottom+2;
	rectLED1.right = rectLED[9].right+1;

	rectLED2.top = rectLED[3].top-1;
	rectLED2.left = rectLED[4].left-1;
	rectLED2.bottom = rectLED[0].bottom+2;
	rectLED2.right = rectLED[1].right+1;
}
void LCD16::fill2LEDs(int val)
{
	for(int i=0;i<18;i++) { rectLED[i].bottom=rectLED[i].top; }
	if( !(val & 1) ) { rectLED[0].bottom += led035h ; }
	if( !(val & 2) ) { rectLED[1].bottom += led1246h ; }
	if( !(val & 4) ) { rectLED[2].bottom += led1246h ; }
	if( !(val & 8) ) { rectLED[3].bottom += led035h ; }
	if( !(val & 16) ) { rectLED[4].bottom += led1246h ; }
	if( !(val & 32) ) { rectLED[5].bottom += led035h ; }
	if( !(val & 64) ) { rectLED[6].bottom += led1246h ; }
	if( !(val & 128) ) { rectLED[7].bottom += dplength ; rectLED[16].bottom += dplength ;}

	if( !(val & 256) ) { rectLED[8].bottom += led035h ; }
	if( !(val & 512) ) { rectLED[9].bottom += led1246h ; }
	if( !(val & 1024) ) { rectLED[10].bottom += led1246h ; }
	if( !(val & 2048) ) { rectLED[11].bottom += led035h ; }
	if( !(val & 4096) ) { rectLED[12].bottom += led1246h ; }
	if( !(val & 8192) ) { rectLED[13].bottom += led035h ; }
	if( !(val & 16384) ) { rectLED[14].bottom += led1246h ; }
	if( !(val & 32768) ) { rectLED[15].bottom += dplength ; rectLED[17].bottom += dplength ;}
}
