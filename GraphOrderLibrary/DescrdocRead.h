#if !defined(AFX_DESCRDOCREAD_H__638CEE43_B689_48DE_9C11_FFC7781EAC94__INCLUDED_)
#define AFX_DESCRDOCREAD_H__638CEE43_B689_48DE_9C11_FFC7781EAC94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DescrdocRead.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DescrdocRead recordset

class DescrdocRead : public CRecordset
{
public:
	DescrdocRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(DescrdocRead)
	CString StrConnection;

// Field/Param Data
	//{{AFX_FIELD(DescrdocRead, CRecordset)
	int		m_CODDOC;
	CString	m_NAMEDOC;
	CString	m_QUERYDATA;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DescrdocRead)
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

#endif // !defined(AFX_DESCRDOCREAD_H__638CEE43_B689_48DE_9C11_FFC7781EAC94__INCLUDED_)
