#if !defined(AFX_ORDALLREAD_H__7959FC44_2A5E_40D9_83A1_A1A78FA44454__INCLUDED_)
#define AFX_ORDALLREAD_H__7959FC44_2A5E_40D9_83A1_A1A78FA44454__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OrdAllRead.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OrdAllRead recordset

class OrdAllRead : public CRecordset
{
public:
	OrdAllRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(OrdAllRead)
	CString StrConnection;
	CString TableName;
	bool HasRegiServ;

	// Field/Param Data
	//{{AFX_FIELD(OrdAllRead, CRecordset)
	BYTE	m_RegiServ;
	long	m_NUMORD;
	long	m_CODORD;
	BYTE	m_NREGSERV;
	long	m_YY;
	BYTE	m_NREGADM;
	long	m_NUMADRAM;
	CTime	m_DATREC;
	BYTE	m_STATEORD;
	CTime	m_DATENDF;
	//}}AFX_FIELD


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OrdAllRead)
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

#endif // !defined(AFX_ORDALLREAD_H__7959FC44_2A5E_40D9_83A1_A1A78FA44454__INCLUDED_)
