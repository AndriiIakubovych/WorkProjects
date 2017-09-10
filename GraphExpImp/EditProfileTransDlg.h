#if !defined(AFX_EDITPROFILETRANSDLG_H__80F36D09_F1EE_48EB_8118_CAF40D1BEC41__INCLUDED_)
#define AFX_EDITPROFILETRANSDLG_H__80F36D09_F1EE_48EB_8118_CAF40D1BEC41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditProfileTransDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EditProfileTransDlg dialog

class EditProfileTransDlg : public CDialog
{
// Construction
public:
	EditProfileTransDlg(CWnd* pParent = NULL);   // standard constructor
	CString IniFile;
	CString PathSection;
	int NumberSection;
	int GroupSection;
	int TypeSourceData;

// Dialog Data
	//{{AFX_DATA(EditProfileTransDlg)
	enum { IDD = IDD_EDIT_PROFILE_TRANS_DIALOG };
	CEdit	m_Size_y;
	CEdit	m_Size_x;
	CEdit	m_Turn;
	CEdit	m_Shift_y;
	CEdit	m_Shift_x;
	CEdit	m_Factor_y;
	CEdit	m_Factor_x;
	CEdit	m_Name_profile;
	CComboBox	m_Name_section;
	CString	m_Name_profile_str;
	CString	m_Factor_x_str;
	CString	m_Factor_y_str;
	CString	m_Shift_x_str;
	CString	m_Shift_y_str;
	CString	m_Turn_str;
	CString	m_Size_x_str;
	CString	m_Size_y_str;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditProfileTransDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EditProfileTransDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeNameProfile();
	afx_msg void OnChangeFactorX();
	afx_msg void OnChangeFactorY();
	afx_msg void OnChangeShiftX();
	afx_msg void OnChangeShiftY();
	afx_msg void OnChangeTurn();
	afx_msg void OnChangeSizeX();
	afx_msg void OnChangeSizeY();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITPROFILETRANSDLG_H__80F36D09_F1EE_48EB_8118_CAF40D1BEC41__INCLUDED_)
