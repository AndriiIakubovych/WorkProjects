// OrderSay.h : main header file for the ORDERSAY application
//

#if !defined(AFX_ORDERSAY_H__CFE0A5BB_6F29_4AFA_B368_FF634618BE90__INCLUDED_)
#define AFX_ORDERSAY_H__CFE0A5BB_6F29_4AFA_B368_FF634618BE90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COrderSayApp:
// See OrderSay.cpp for the implementation of this class
//

class COrderSayApp : public CWinApp
{
public:
	CMultiDocTemplate* pDocTemplate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrderSayApp)
	public:
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(COrderSayApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORDERSAY_H__CFE0A5BB_6F29_4AFA_B368_FF634618BE90__INCLUDED_)
