#if !defined(AFX_EDITFILESEXPDLG_H__45D33CEB_31F7_4843_9672_73EBCC18787A__INCLUDED_)
#define AFX_EDITFILESEXPDLG_H__45D33CEB_31F7_4843_9672_73EBCC18787A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditFilesExpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EditFilesExpDlg dialog

class EditFilesExpDlg : public CDialog
{
// Construction
public:
	EditFilesExpDlg(CWnd* pParent = NULL);   // standard constructor
	CString IniFile;
	CString StrConnection;
	CString NameFile_str;
	int IdProfile;
	int TypeGraphObject_int;
	int TypeGraphObj_int;
	int GROUPREG;

// Dialog Data
	//{{AFX_DATA(EditFilesExpDlg)
	enum { IDD = IDD_EDIT_FILES_EXP_DIALOG };
	CListCtrl	m_List;
	CButton	m_Complement_areas_centers_knots;
	BOOL	m_Complement_areas_centers_knots_bool;
	CString	m_Query_exp_str;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditFilesExpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EditFilesExpDlg)
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

#endif // !defined(AFX_EDITFILESEXPDLG_H__45D33CEB_31F7_4843_9672_73EBCC18787A__INCLUDED_)
