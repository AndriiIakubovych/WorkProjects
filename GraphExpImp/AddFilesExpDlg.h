#if !defined(AFX_ADDFILESEXPDLG_H__720A8DCD_4797_41A6_B090_8CD0183C3962__INCLUDED_)
#define AFX_ADDFILESEXPDLG_H__720A8DCD_4797_41A6_B090_8CD0183C3962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddFilesExpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AddFilesExpDlg dialog

class AddFilesExpDlg : public CDialog
{
// Construction
public:
	AddFilesExpDlg(CWnd* pParent = NULL);   // standard constructor
	CString IniFile;
	CString StrConnection;
	CString* NameFile;
	int* TypeGraphObject;
	int* TypeGraphObj;
	int IdProfile;
	int GROUPREG;
	int CountSelectedElements;

// Dialog Data
	//{{AFX_DATA(AddFilesExpDlg)
	enum { IDD = IDD_ADD_FILES_EXP_DIALOG };
	CButton	m_Complement_areas_centers_knots;
	CListCtrl	m_List;
	BOOL	m_Complement_areas_centers_knots_bool;
	CString	m_Query_exp_str;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AddFilesExpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AddFilesExpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDFILESEXPDLG_H__720A8DCD_4797_41A6_B090_8CD0183C3962__INCLUDED_)
