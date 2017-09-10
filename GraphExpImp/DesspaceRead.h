#if !defined(AFX_DESSPACEREAD_H__7A5162A7_667D_4F7B_8EFF_F04748A5D8B7__INCLUDED_)
#define AFX_DESSPACEREAD_H__7A5162A7_667D_4F7B_8EFF_F04748A5D8B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DesspaceRead.h : header file
//

#include <afxdb.h>

/////////////////////////////////////////////////////////////////////////////
// DesspaceRead recordset

class DesspaceRead : public CRecordset
{
public:
	DesspaceRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(DesspaceRead)
	CString StrConnection;

// Field/Param Data
	//{{AFX_FIELD(DesspaceRead, CRecordset)
	int		m_PERSON;
	int		m_NUMSPACE;
	CString	m_NAMESPACE;
	BYTE	m_TYPSPACE;
	//BYTE	m_CRIT;
	int		m_NUMPOINT;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DesspaceRead)
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

#endif // !defined(AFX_DESSPACEREAD_H__7A5162A7_667D_4F7B_8EFF_F04748A5D8B7__INCLUDED_)
