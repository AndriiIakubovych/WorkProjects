#if !defined(AFX_ADDSAMPLEPROFILEDLG_H__B9AD397E_F434_49AC_8B82_B29DC7E3269A__INCLUDED_)
#define AFX_ADDSAMPLEPROFILEDLG_H__B9AD397E_F434_49AC_8B82_B29DC7E3269A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddSampleProfileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AddSampleProfileDlg dialog

class AddSampleProfileDlg : public CDialog
{
// Construction
public:
	AddSampleProfileDlg(CWnd* pParent = NULL);   // standard constructor
	CString IniFile;
	int TypeProfile;

// Dialog Data
	//{{AFX_DATA(AddSampleProfileDlg)
	enum { IDD = IDD_ADD_SAMPLE_PROFILE_DIALOG };
	CEdit	m_Name_profile;
	CComboBox	m_Type_profile;
	CString	m_Name_profile_str;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AddSampleProfileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AddSampleProfileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeNameProfile();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDSAMPLEPROFILEDLG_H__B9AD397E_F434_49AC_8B82_B29DC7E3269A__INCLUDED_)
