#pragma once

class LCD16
{
public:
	LCD16(int a_ledTop, int a_led4left, int a_led12left, int a_w);
private:
	int led035w; int led035h;
	int led1246w; int led1246h;
	int led4left; int ledTop;
	int led12left; 
	int dplength; int dpgap;
	~LCD16(void);
public:
	RECT rectLED[18];
	RECT rectLED1,rectLED2;
	void fill2LEDs(int val);
};
