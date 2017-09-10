#if !defined(AFX_TPLEVREAD_H__D2DD1B32_B6F7_41DD_90AE_7E9EEDF9E853__INCLUDED_)
#define AFX_TPLEVREAD_H__D2DD1B32_B6F7_41DD_90AE_7E9EEDF9E853__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TplevRead.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// TplevRead recordset

class TplevRead : public CRecordset
{
public:
	TplevRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TplevRead)
	CString StrConnection;

// Field/Param Data
	//{{AFX_FIELD(TplevRead, CRecordset)
	BYTE	m_vidobj;
	int		m_type;
	BYTE	m_USEORDER;
	int		m_dlevel;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TplevRead)
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

#endif // !defined(AFX_TPLEVREAD_H__D2DD1B32_B6F7_41DD_90AE_7E9EEDF9E853__INCLUDED_)
