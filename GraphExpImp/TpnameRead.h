#if !defined(AFX_TPNAMEREAD_H__A00303CF_D2FC_48CF_89A1_6AFCC7E29B3B__INCLUDED_)
#define AFX_TPNAMEREAD_H__A00303CF_D2FC_48CF_89A1_6AFCC7E29B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TpnameRead.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// TpnameRead recordset

class TpnameRead : public CRecordset
{
public:
	TpnameRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TpnameRead)
	CString StrConnection;

// Field/Param Data
	//{{AFX_FIELD(TpnameRead, CRecordset)
	BYTE	m_VIDOBJ;
	BYTE	m_TYPNAM;
	BYTE	m_USEORDER;
	CString	m_NAMNAM;
	long	m_ICOLTEXT;
	BYTE	m_NUMFONT;
	BYTE	m_TYPSYS;
	BYTE	m_NUMEXPR;
	BYTE	m_STYLENAME;
	BYTE	m_NUMTPNAM;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TpnameRead)
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

#endif // !defined(AFX_TPNAMEREAD_H__A00303CF_D2FC_48CF_89A1_6AFCC7E29B3B__INCLUDED_)
