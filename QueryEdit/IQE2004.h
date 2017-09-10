// IQE2004.h : main header file for the IQE2004 application
//

#if !defined(AFX_IQE2004_H__37860A24_D662_11D8_88EF_00024453B8E0__INCLUDED_)
#define AFX_IQE2004_H__37860A24_D662_11D8_88EF_00024453B8E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "QueryEditRes\resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIQE2004App:
// See IQE2004.cpp for the implementation of this class
//

class CIQE2004App : public CWinApp
{
public:
	CIQE2004App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIQE2004App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIQE2004App)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IQE2004_H__37860A24_D662_11D8_88EF_00024453B8E0__INCLUDED_)
