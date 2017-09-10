#if !defined(AFX_NREGIONREAD_H__8885B3E3_6B12_4010_88CF_DFC5BD44F793__INCLUDED_)
#define AFX_NREGIONREAD_H__8885B3E3_6B12_4010_88CF_DFC5BD44F793__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NregionRead.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// NregionRead recordset

class NregionRead : public CRecordset
{
public:
	NregionRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(NregionRead)
	CString IniFile;

// Field/Param Data
	//{{AFX_FIELD(NregionRead, CRecordset)
	int		m_NUMREG;
	BYTE	m_GRUPREG;
	CString	m_NAMREG;
	CString	m_PATH;
	BYTE	m_TYPBASE;
	int		m_PARENT;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NregionRead)
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

#endif // !defined(AFX_NREGIONREAD_H__8885B3E3_6B12_4010_88CF_DFC5BD44F793__INCLUDED_)
