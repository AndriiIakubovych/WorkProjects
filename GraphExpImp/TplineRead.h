#if !defined(AFX_TPLINEREAD_H__0451E46F_819B_4137_9EE1_88674DF15429__INCLUDED_)
#define AFX_TPLINEREAD_H__0451E46F_819B_4137_9EE1_88674DF15429__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TplineRead.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// TplineRead recordset

class TplineRead : public CRecordset
{
public:
	TplineRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TplineRead)
	CString StrConnection;

// Field/Param Data
	//{{AFX_FIELD(TplineRead, CRecordset)
	BYTE	m_VIDOBJ;
	BYTE	m_TYPBLINE;
	BYTE	m_USEORDER;
	CString	m_NAMTP;
	BYTE	m_TYPLINE;
	long	m_ICOLBOUM;
	BYTE	m_WIDTH;
	BYTE	m_CLOSE;
	BYTE	m_TYPSYS;
	long	m_ICOLOUR;
	long	m_ICOLDASH;
	BYTE	m_STYLDASH;
	BYTE	m_MODEADR;
	float	m_SIZEVAL;
	int		m_NUMFIG;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TplineRead)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TPLINEREAD_H__0451E46F_819B_4137_9EE1_88674DF15429__INCLUDED_)
