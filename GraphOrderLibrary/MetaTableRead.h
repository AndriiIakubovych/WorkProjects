#if !defined(AFX_METATABLEREAD_H__F862E34E_DE34_4E7C_AC3C_B2E0437A94BA__INCLUDED_)
#define AFX_METATABLEREAD_H__F862E34E_DE34_4E7C_AC3C_B2E0437A94BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MetaTableRead.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MetaTableRead recordset

class MetaTableRead : public CRecordset
{
public:
	MetaTableRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(MetaTableRead)
	CString IniFile;

	// Field/Param Data
	//{{AFX_FIELD(MetaTableRead, CRecordset)
	int		m_NUMREG;
	int		m_Table_ID;
	CString	m_TableName;
	CString	m_TableDescr;
	BOOL	m_IsTable;
	BYTE	m_TableType;
	BYTE	m_BaseType;
	BOOL	m_IsBlock;
	CString	m_Condition;
	BYTE	m_ModeName;
	//}}AFX_FIELD


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MetaTableRead)
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

#endif // !defined(AFX_METATABLEREAD_H__F862E34E_DE34_4E7C_AC3C_B2E0437A94BA__INCLUDED_)
