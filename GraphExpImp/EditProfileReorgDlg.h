#if !defined(AFX_EDITPROFILEREORGDLG_H__F62B4C82_20AE_4EBD_81CD_B807E4F7AFAC__INCLUDED_)
#define AFX_EDITPROFILEREORGDLG_H__F62B4C82_20AE_4EBD_81CD_B807E4F7AFAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditProfileReorgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EditProfileReorgDlg dialog

class EditProfileReorgDlg : public CDialog
{
// Construction
public:
	EditProfileReorgDlg(CWnd* pParent = NULL);   // standard constructor
	CString IniFile;
	CString PathSection;
	int NumberSection;
	int GroupSection;
	int TypeSourceData;

// Dialog Data
	//{{AFX_DATA(EditProfileReorgDlg)
	enum { IDD = IDD_EDIT_PROFILE_REORG_DIALOG };
	CEdit	m_Name_profile;
	CComboBox	m_Name_section;
	CString	m_Name_profile_str;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditProfileReorgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EditProfileReorgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeNameProfile();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITPROFILEREORGDLG_H__F62B4C82_20AE_4EBD_81CD_B807E4F7AFAC__INCLUDED_)
