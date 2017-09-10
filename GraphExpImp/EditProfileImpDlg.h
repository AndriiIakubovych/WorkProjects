#if !defined(AFX_EDITPROFILEIMPDLG_H__334C8BCC_E9A0_496F_BD58_12BFDC2490DC__INCLUDED_)
#define AFX_EDITPROFILEIMPDLG_H__334C8BCC_E9A0_496F_BD58_12BFDC2490DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditProfileImpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EditProfileImpDlg dialog

class EditProfileImpDlg : public CDialog
{
// Construction
public:
	EditProfileImpDlg(CWnd* pParent = NULL);   // standard constructor
	CString IniFile;
	CString PathSection;
	int NumberSection;
	int GroupSection;
	int TypeSourceData;

// Dialog Data
	//{{AFX_DATA(EditProfileImpDlg)
	enum { IDD = IDD_EDIT_PROFILE_IMP_DIALOG };
	CEdit	m_Turn;
	CEdit	m_Shift_y;
	CEdit	m_Shift_x;
	CEdit	m_Factor_y;
	CEdit	m_Factor_x;
	CEdit	m_Choosen_folder;
	CEdit	m_Name_profile;
	CComboBox	m_Name_section;
	CString	m_Name_profile_str;
	CString	m_Factor_x_str;
	CString	m_Choosen_folder_str;
	CString	m_Factor_y_str;
	CString	m_Shift_x_str;
	CString	m_Shift_y_str;
	CString	m_Turn_str;
	int		m_Usual_int;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditProfileImpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EditProfileImpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeNameProfile();
	afx_msg void OnOpenSelectFolder();
	afx_msg void OnChangeFactorX();
	afx_msg void OnChangeFactorY();
	afx_msg void OnChangeShiftX();
	afx_msg void OnChangeShiftY();
	afx_msg void OnChangeTurn();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITPROFILEIMPDLG_H__334C8BCC_E9A0_496F_BD58_12BFDC2490DC__INCLUDED_)
