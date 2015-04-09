// WINEL7.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWINEL7App:
// See WINEL7.cpp for the implementation of this class
//

class CWINEL7App : public CWinApp
{
public:
	CWINEL7App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CWINEL7App theApp;