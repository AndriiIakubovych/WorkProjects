#if !defined(AFX_SERVICEREAD_H__F3964B9F_A75C_4EF4_8E46_13E328B33B5B__INCLUDED_)
#define AFX_SERVICEREAD_H__F3964B9F_A75C_4EF4_8E46_13E328B33B5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServiceRead.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ServiceRead recordset

class ServiceRead : public CRecordset
{
public:
	ServiceRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(ServiceRead)
	CString StrConnection;

// Field/Param Data
	//{{AFX_FIELD(ServiceRead, CRecordset)
	BYTE	m_NREGSERV;
	CString	m_NAMSERV;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ServiceRead)
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

#endif // !defined(AFX_SERVICEREAD_H__F3964B9F_A75C_4EF4_8E46_13E328B33B5B__INCLUDED_)
