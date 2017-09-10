#if !defined(AFX_DESCRREAD_H__72CDD886_E989_4AC8_B25C_E78D5C910EDD__INCLUDED_)
#define AFX_DESCRREAD_H__72CDD886_E989_4AC8_B25C_E78D5C910EDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DescrRead.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DescrRead recordset

class DescrRead : public CRecordset
{
public:
	DescrRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(DescrRead)
	CString StrConnection;

// Field/Param Data
	//{{AFX_FIELD(DescrRead, CRecordset)
	int		m_CODDOC;
	BYTE	m_NUMCOL;
	CString	m_NAMSQLCOL;
	CString	m_NAMECOL;
	BYTE	m_WIDTHCOL;
	BYTE	m_TYPDATA;
	CString	m_FORMAT;
	BYTE	m_TYPCENTR;
	BOOL	m_SEE;
	BOOL	m_NOSEEAGR;
	BYTE	m_TOBJECT;
	int		m_TYPPAR;
	BYTE	m_TYPEAGR;
	BYTE	m_FIELDTYPE;
	int		m_CLASSID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DescrRead)
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

#endif // !defined(AFX_DESCRREAD_H__72CDD886_E989_4AC8_B25C_E78D5C910EDD__INCLUDED_)
