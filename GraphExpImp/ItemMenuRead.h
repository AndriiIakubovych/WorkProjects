#if !defined(AFX_ITEMMENUREAD_H__F6AD0DDD_FDF6_4544_825E_AA62EF4BD487__INCLUDED_)
#define AFX_ITEMMENUREAD_H__F6AD0DDD_FDF6_4544_825E_AA62EF4BD487__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ItemMenuRead.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ItemMenuRead recordset

class ItemMenuRead : public CRecordset
{
public:
	ItemMenuRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(ItemMenuRead)
	CString IniFile;

// Field/Param Data
	//{{AFX_FIELD(ItemMenuRead, CRecordset)
	int		m_CODMENU;
	int		m_CODITEM;
	int		m_NUMITEM;
	CString	m_NAMEITEM;
	int		m_CODCOMM;
	int		m_CODICON;
	CString	m_HELPITEM;
	BYTE	m_ACCESS;
	BYTE	m_WRJOURN;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ItemMenuRead)
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

#endif // !defined(AFX_ITEMMENUREAD_H__F6AD0DDD_FDF6_4544_825E_AA62EF4BD487__INCLUDED_)
