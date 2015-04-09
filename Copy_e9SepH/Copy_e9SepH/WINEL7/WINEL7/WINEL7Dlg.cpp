// WINEL7Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "WINEL7.h"
#include "WINEL7Dlg.h"
#include "Code7.h"
#include "WinKeySender.h"
#define	WM_ICON_NOTIFY WM_USER + 10
#define TIMER_ID 101
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWINEL7Dlg dialog
CWINEL7Dlg::CWINEL7Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWINEL7Dlg::IDD, pParent)
{
   m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
   mkc16I._flag123AaSftCtrl = 0;
   _16bitsMkcVal = 0xff80;//65408;//0x8080 ;
   _prevPressedIndex = 20;
   _vhichSevenKey = 0;
   _prevId=20;
   is7KCFilled = false;
   mkc16I._curLang = 0;
   mkc16I.isPrevSpaceMatraVovel = true;
   lcd = new LCD16(4,124,2,3);
}

void CWINEL7Dlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWINEL7Dlg, CDialog)
   ON_WM_PAINT()
   ON_WM_QUERYDRAGICON()
   //}}AFX_MSG_MAP
   ON_CBN_SELCHANGE(IDC_COMBO1, &CWINEL7Dlg::OnCbnSelchangeCombo1)
   ON_BN_CLICKED(IDC_CHECK1, &CWINEL7Dlg::OnBnClickedCheck1)
   ON_BN_CLICKED(IDC_CHECK2, &CWINEL7Dlg::OnBnClickedCheck2)
   ON_BN_CLICKED(IDC_CHECK3, &CWINEL7Dlg::OnBnClickedCheck3)
   ON_WM_NCLBUTTONDOWN()
   ON_WM_MOUSEMOVE()
   ON_WM_LBUTTONDOWN()
   ON_WM_KEYDOWN()
   ON_WM_KEYDOWN()
   ON_WM_LBUTTONDBLCLK()
   ON_BN_CLICKED(IDC_CHECK4, &CWINEL7Dlg::OnBnClickedCheck4)
END_MESSAGE_MAP()

// CWINEL7Dlg message handlers
BOOL CWINEL7Dlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   // Set the icon for this dialog.  The framework does this automatically
   //  when the application's main window is not a dialog
   SetIcon(m_hIcon, TRUE);			// Set big icon
   SetIcon(m_hIcon, FALSE);		// Set small icon

   // TODO: Add extra initialization here
   syncCheckBoxes();
   //syncNUM123();
   const TCHAR *items[] = 
   { L"Eng", L"हिनदी", L"বাংলা", L"ਪੰਜਾਬੀ", L"ગુજરાતી", L"ଓଡ଼ିଆ", L"தமிழ்", L"తెలుగు", L"ಕನ್ನಡ", L"മലയാളം" }	;
   CComboBox* p_cbox = (CComboBox*)GetDlgItem(IDC_COMBO1);
   for(int i=0 ; i<10; i++) { p_cbox->AddString(items[i]); }
   p_cbox->SetCurSel(0);
   return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWINEL7Dlg::OnPaint()
{
   if (IsIconic())
   {
      CPaintDC dc(this); // device context for painting
      SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

      // Center icon in client rectangle
      int cxIcon = GetSystemMetrics(SM_CXICON);
      int cyIcon = GetSystemMetrics(SM_CYICON);
      CRect rect;
      GetClientRect(&rect);
      int x = (rect.Width() - cxIcon + 1) / 2;
      int y = (rect.Height() - cyIcon + 1) / 2;

      // Draw the icon
      dc.DrawIcon(x, y, m_hIcon);
   }
   else
   {
      CDialog::OnPaint();
      //DrawKeyboard();
      //lcd->fill2LEDs(_16bitsMkcVal);
      Draw2LEDs();
   }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWINEL7Dlg::OnQueryDragIcon()
{
   return static_cast<HCURSOR>(m_hIcon);
}
void CWINEL7Dlg::Draw2LEDs()
{
   CClientDC dc(this);
   CBrush brushBlack(RGB(0, 0, 0)); CBrush brushRed(RGB(255, 0, 0));
   CBrush brushWhite(RGB(255, 255, 255)); CBrush brushGreen(RGB(0, 128, 0));
   ////
   for(int i=0;i<8;i++)
   {
      if(_16bitsMkcVal & (1<<i)) dc.FrameRect( &(lcd->rectLED[i]), &brushWhite );
      else dc.FillRect( &(lcd->rectLED[i]), &brushBlack );
   }
   if(_16bitsMkcVal & 128) dc.FrameRect( &(lcd->rectLED[16]), &brushWhite );
   else dc.FillRect( &(lcd->rectLED[16]), &brushBlack );
      
      
   for(int i=8;i<16;i++)
   {
      if(_16bitsMkcVal & (1<<i)) dc.FrameRect( &(lcd->rectLED[i]), &brushGreen );
      else dc.FillRect( &(lcd->rectLED[i]), &brushRed );
   }
   if(_16bitsMkcVal & 32768) dc.FrameRect( &(lcd->rectLED[17]), &brushGreen );
   else dc.FillRect( &(lcd->rectLED[17]), &brushRed );
   /////
   brushBlack.DeleteObject(); brushRed.DeleteObject();
   brushGreen.DeleteObject(); brushWhite.DeleteObject();
}
int CWINEL7Dlg::DescribeKeyState() 
{
   int state = 0; 	short ks;
   ks = GetKeyState(VK_CAPITAL); 	if(ks & 0x000F) state += 0x01;
   ks = GetKeyState(VK_SHIFT); 	if(ks & 0xF000) state += 0x02;
   ks = GetKeyState(VK_CONTROL); 	if(ks & 0xF000) state += 0x04;
   return state;
}
void CWINEL7Dlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
// TODO: Add your message handler code here and/or call default
   SetForegroundWindow();
   CDialog::OnNcLButtonDown(nHitTest, point);
}

void CWINEL7Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
// TODO: Add your message handler code here and/or call default
   SetActiveWindow();
   CDialog::OnMouseMove(nFlags, point);
}

// //It handles first click by toggling led line
void CWINEL7Dlg::processKeyDaunCommon(int buttonIndex)
{
   if(16==buttonIndex) buttonIndex = 7;
   if(17==buttonIndex) buttonIndex = 15;
   int _bitCheckerSetter = 1<<buttonIndex;
   _16bitsMkcVal ^= _bitCheckerSetter ;
   Draw2LEDs();
   if(buttonIndex<8) this->InvalidateRect(&(lcd->rectLED2),true);
   else this->InvalidateRect(&(lcd->rectLED1),true);
}

void CWINEL7Dlg::syncCheckBoxes(void)
{
   //int state = 0;
   short ks;
   ks = GetKeyState(VK_CAPITAL);
   if(ks & 0x000F)
   {
      mkc16I._flag123AaSftCtrl |=2;
      CButton* chkBxP = (CButton*)GetDlgItem(IDC_CHECK2);
      chkBxP->SetCheck(BST_CHECKED);
   }
   else
   {
      mkc16I._flag123AaSftCtrl |=2; mkc16I._flag123AaSftCtrl ^= 2;
      CButton* chkBxP = (CButton*)GetDlgItem(IDC_CHECK2);
      chkBxP->SetCheck(BST_UNCHECKED);
   }
   ks = GetKeyState(VK_NUMLOCK);
   if(ks & 0x000F)
   {
      mkc16I._flag123AaSftCtrl |=1;
      CButton* chkBxP = (CButton*)GetDlgItem(IDC_CHECK1);
      chkBxP->SetCheck(BST_CHECKED);
   }
   else
   {
      mkc16I._flag123AaSftCtrl |=1; mkc16I._flag123AaSftCtrl ^= 1;
      CButton* chkBxP = (CButton*)GetDlgItem(IDC_CHECK1);
      chkBxP->SetCheck(BST_UNCHECKED);
   }
   ks = GetKeyState(VK_SHIFT);
   if(ks & 0x8000)
   {
      mkc16I._flag123AaSftCtrl |=4;
      CButton* chkBxP = (CButton*)GetDlgItem(IDC_CHECK3);
      chkBxP->SetCheck(BST_CHECKED);
   }
   else
   {
      mkc16I._flag123AaSftCtrl |=4; mkc16I._flag123AaSftCtrl ^= 4;
      CButton* chkBxP = (CButton*)GetDlgItem(IDC_CHECK3);
      chkBxP->SetCheck(BST_UNCHECKED);
   }
   ks = GetKeyState(VK_CONTROL);
   if(ks & 0x8000)
   {
      mkc16I._flag123AaSftCtrl |=8;
      CButton* chkBxP = (CButton*)GetDlgItem(IDC_CHECK4);
      chkBxP->SetCheck(BST_CHECKED);
   }
   else
   {
      mkc16I._flag123AaSftCtrl |=8; mkc16I._flag123AaSftCtrl ^= 8;
      CButton* chkBxP = (CButton*)GetDlgItem(IDC_CHECK4);
      chkBxP->SetCheck(BST_UNCHECKED);
   }   
}
void CWINEL7Dlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   syncCheckBoxes();
   //CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CWINEL7Dlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
   // TODO: Add your message handler code here and/or call default
   mkc16I.handleMKC16(_16bitsMkcVal);
   _prevId = 20;	
   _16bitsMkcVal = 65408;//0x8080 ;
   Draw2LEDs();
   InvalidateRect(&(lcd->rectLED2),true);
   InvalidateRect(&(lcd->rectLED1),true);
   //CDialogEx::OnLButtonDblClk(nFlags, point);
}
void CWINEL7Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
   // TODO: Add your message handler code here and/or call default
   POINT p; p.x = point.x; p.y = point.y;
   for(int i=0; i<18 ; i++)
   {
      if( PtInRect(&(lcd->rectLED[i]),p ))
      {
         if(i==_prevId)
         {
            mkc16I.handleMKC16(_16bitsMkcVal);
            _prevId = 20;	
            _16bitsMkcVal = 65408;//0x8080 ;
            Draw2LEDs();
            InvalidateRect(&(lcd->rectLED2),true);
            InvalidateRect(&(lcd->rectLED1),true);
         }
         else { _prevId = i;processKeyDaunCommon(i); }
         break ;
      }
   }
   //CDialogEx::OnLButtonDown(nFlags, point);
}
void CWINEL7Dlg::OnCbnSelchangeCombo1()
{
   // TODO: Add your control notification handler code here
   CComboBox* cbx1P = (CComboBox*)GetDlgItem(IDC_COMBO1);
   mkc16I._curLang = cbx1P->GetCurSel();
   cbx1P->SetCurSel(mkc16I._curLang);
   CButton* chkBxP = (CButton*)GetDlgItem(IDC_CHECK1);
   chkBxP->SetFocus();
}
void CWINEL7Dlg::OnBnClickedCheck1()
{
   // TODO: Add your control notification handler code here
   mkc16I._flag123AaSftCtrl |= 1;
   CButton* chkBxP = (CButton*)GetDlgItem(IDC_CHECK1);
   if(!(chkBxP->GetCheck())) { mkc16I._flag123AaSftCtrl ^= 1; }
   WinKeySender::sendNAVCodeDecimal(VK_NUMLOCK,0,0);
}
void CWINEL7Dlg::OnBnClickedCheck2()
{
   // TODO: Add your control notification handler code here
   mkc16I._flag123AaSftCtrl |=2;
   CButton* chkBxP = (CButton*)GetDlgItem(IDC_CHECK2);
   if(!(chkBxP->GetCheck())) { mkc16I._flag123AaSftCtrl ^= 2; }
   WinKeySender::sendNAVCodeDecimal(VK_CAPITAL,0,0);
}
void CWINEL7Dlg::OnBnClickedCheck3()
{
   // TODO: Add your control notification handler code here
   mkc16I._flag123AaSftCtrl |=4;
   keybd_event(VK_SHIFT,0,0,0);
   CButton* chkBxP = (CButton*)GetDlgItem(IDC_CHECK3);
   if(!(chkBxP->GetCheck()))
   {
      mkc16I._flag123AaSftCtrl ^= 4;
      keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
   }
}
void CWINEL7Dlg::OnBnClickedCheck4()
{
   // TODO: Add your control notification handler code here
   mkc16I._flag123AaSftCtrl |=8;
   keybd_event(VK_CONTROL,0,0,0);
   CButton* chkBxP = (CButton*)GetDlgItem(IDC_CHECK4);
   if(!(chkBxP->GetCheck()))
   {
      mkc16I._flag123AaSftCtrl ^= 8;
      keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
   }
}

