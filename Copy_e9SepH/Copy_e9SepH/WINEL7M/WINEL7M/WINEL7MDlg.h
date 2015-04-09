// WINEL7Dlg.h : header file
//
#pragma once
#include "lcd16.h"
#include "KEYS16.h"
//#include "SystemTray.h"
#include "MKC16.h"
#define TAB 0x02
#define CAPSLOCK 0x03
#define SHIFT 0x04
#define CTRL 0x05
#define BSPACE 0x06
#define ENTER 0x07
#define ALT 0x08
#define WINDOW 0x9
#define LEFT 0x0A
#define RIGHT 0x0B
#define UP 0x0C
#define DOWN 0x0D
#define ESC 0x0E
#define PUP 0x0F
#define PDN 0x10
#define HOME 0x11
#define END 0x12
#define INS 0x13
#define DEL 0x14
#define WWW 0x15
struct KEYDEF { char cNormal; char cShifted; };
// CWINEL7MDlg dialog
class CWINEL7MDlg : public CDialog
{
// Construction
public:
	CWINEL7MDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WINEL7_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
private:
	int _16bitsMkcVal;//0x8080 ;
	int _prevPressedIndex;
	int _vhichSevenKey;
	int _prevId;
	bool is7KCFilled;
	LCD16* lcd;
	KEYS16 keypad7;
	MKC16 mkc16I;	
public:
	//void ReleaseFocus();
   //CSystemTray cSystray;
	int DescribeKeyState();
	void Draw2LEDs();
	void processKeyDaunCommon(int buttonIndex);
	bool handle7KCValue(int arg7KCValue);
	void syncCheckBoxes(void);
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
   afx_msg void OnBnClickedCheck4();
};
