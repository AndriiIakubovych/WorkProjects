#if !defined(AFX_ABOUTPROGRAMDLG_H__5C97CEDE_56F0_405B_83F3_A8D304FE9352__INCLUDED_)
#define AFX_ABOUTPROGRAMDLG_H__5C97CEDE_56F0_405B_83F3_A8D304FE9352__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutProgramDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AboutProgramDlg dialog

class AboutProgramDlg : public CDialog
{
// Construction
public:
	AboutProgramDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AboutProgramDlg)
	enum { IDD = IDD_ABOUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AboutProgramDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AboutProgramDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTPROGRAMDLG_H__5C97CEDE_56F0_405B_83F3_A8D304FE9352__INCLUDED_)
