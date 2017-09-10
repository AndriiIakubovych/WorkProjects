#if !defined(AFX_NAMENEWTABLEDLG_H__758FC413_3143_4480_8BF1_841FDB6A5181__INCLUDED_)
#define AFX_NAMENEWTABLEDLG_H__758FC413_3143_4480_8BF1_841FDB6A5181__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NameNewTableDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// NameNewTableDlg dialog

class NameNewTableDlg : public CDialog
{
// Construction
public:
	NameNewTableDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(NameNewTableDlg)
	enum { IDD = IDD_NAME_NEW_TABLE };
	CEdit	m_Name_table;
	CString	m_Name_table_str;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NameNewTableDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(NameNewTableDlg)
	afx_msg void OnChangeNameTable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAMENEWTABLEDLG_H__758FC413_3143_4480_8BF1_841FDB6A5181__INCLUDED_)
