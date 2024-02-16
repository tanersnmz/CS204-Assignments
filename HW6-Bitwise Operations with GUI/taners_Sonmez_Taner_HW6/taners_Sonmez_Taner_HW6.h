
// taners_Sonmez_Taner_HW6.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Ctaners_Sonmez_Taner_HW6App:
// See taners_Sonmez_Taner_HW6.cpp for the implementation of this class
//

class Ctaners_Sonmez_Taner_HW6App : public CWinApp
{
public:
	Ctaners_Sonmez_Taner_HW6App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Ctaners_Sonmez_Taner_HW6App theApp;