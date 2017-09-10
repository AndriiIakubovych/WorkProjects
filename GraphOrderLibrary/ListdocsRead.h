#if !defined(AFX_LISTDOCSREAD_H__14FC73B7_E9DF_4E3B_885D_A8159E93B395__INCLUDED_)
#define AFX_LISTDOCSREAD_H__14FC73B7_E9DF_4E3B_885D_A8159E93B395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListdocsRead.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ListdocsRead recordset

class ListdocsRead : public CRecordset
{
public:
	ListdocsRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(ListdocsRead)
	CString StrConnection;

// Field/Param Data
	//{{AFX_FIELD(ListdocsRead, CRecordset)
	int		m_LISTDOC;
	BYTE	m_NUMDOC;
	int		m_CODDOC;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ListdocsRead)
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

#endif // !defined(AFX_LISTDOCSREAD_H__14FC73B7_E9DF_4E3B_885D_A8159E93B395__INCLUDED_)
