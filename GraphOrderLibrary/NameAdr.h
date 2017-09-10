#if !defined(AFX_NAMEADR_H__B50B7581_C14C_11D5_8399_00C0F020120D__INCLUDED_)
#define AFX_NAMEADR_H__B50B7581_C14C_11D5_8399_00C0F020120D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NameAdr.h : header file

#pragma comment(lib, "OutGraf.lib")
#include "I:\CiWin5\bibuni6\grafstr.h"

/////////////////////////////////////////////////////////////////////////////
// NameAdr recordnet

class NameAdr : public CRecordNet
{
public:
	NameAdr(CDatabNet* pDatabase = NULL, CString NAME = "");

// Field/Param Data
	//{{AFX_FIELD(NameAdr, CRecordnet)
	long	m_NUMAREA;
	CString	m_distr;
	CString	m_street;
	CString	m_ADDRESS;
	//}}AFX_FIELD
	BOOL isDISTR;
	CString strSql;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NameAdr)
	public:
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG

#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAMEADR_H__B50B7581_C14C_11D5_8399_00C0F020120D__INCLUDED_)
