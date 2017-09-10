#if !defined(AFX_ADMREAD_H__9168B985_7040_4AD5_8810_50D9EF5D3ADC__INCLUDED_)
#define AFX_ADMREAD_H__9168B985_7040_4AD5_8810_50D9EF5D3ADC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdmRead.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AdmRead recordset

class AdmRead : public CRecordset
{
public:
	AdmRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(AdmRead)
	CString StrConnection;

// Field/Param Data
	//{{AFX_FIELD(AdmRead, CRecordset)
	int		m_NREGADM;
	CString	m_NAMADM;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AdmRead)
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

#endif // !defined(AFX_ADMREAD_H__9168B985_7040_4AD5_8810_50D9EF5D3ADC__INCLUDED_)
