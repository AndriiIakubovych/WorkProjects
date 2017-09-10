#if !defined(AFX_CODTECHREAD_H__F13862B1_460D_4631_8FE3_4F197BB20E04__INCLUDED_)
#define AFX_CODTECHREAD_H__F13862B1_460D_4631_8FE3_4F197BB20E04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodTechRead.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CodTechRead recordset

class CodTechRead : public CRecordset
{
public:
	CodTechRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CodTechRead)
	CString StrConnection;

	// Field/Param Data
	//{{AFX_FIELD(CodTechRead, CRecordset)
	int		m_CODCLAS;
	BYTE	m_CODSCLAS;
	CString	m_NAME;
	//}}AFX_FIELD


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CodTechRead)
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

#endif // !defined(AFX_CODTECHREAD_H__F13862B1_460D_4631_8FE3_4F197BB20E04__INCLUDED_)
