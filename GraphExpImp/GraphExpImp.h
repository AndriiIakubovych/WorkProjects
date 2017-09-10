// GraphExpImp.h : main header file for the GRAPHEXPIMP application
//

#if !defined(AFX_GRAPHEXPIMP_H__DD0FE76E_D0B0_422C_A75A_E2DF568487A7__INCLUDED_)
#define AFX_GRAPHEXPIMP_H__DD0FE76E_D0B0_422C_A75A_E2DF568487A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "GraphExpImpRes\resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGraphExpImpApp:
// See GraphExpImp.cpp for the implementation of this class
//

class CGraphExpImpApp : public CWinApp
{
public:
	CGraphExpImpApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphExpImpApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGraphExpImpApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHEXPIMP_H__DD0FE76E_D0B0_422C_A75A_E2DF568487A7__INCLUDED_)
