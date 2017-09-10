#if !defined(AFX_EDITPROFILEEXPDLG_H__0374074D_7039_4327_AA93_F19037082042__INCLUDED_)
#define AFX_EDITPROFILEEXPDLG_H__0374074D_7039_4327_AA93_F19037082042__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditProfileExpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EditProfileExpDlg dialog

class EditProfileExpDlg : public CDialog
{
// Construction
public:
	EditProfileExpDlg(CWnd* pParent = NULL);   // standard constructor
	CString IniFile;
	CString GraphAreaName;
	CString PathSection;
	BOOL GraphAreaEnable;
	int PERSON;
	int NumberSection;
	int GroupSection;
	int TypeSourceData;
	int GraphArea;

// Dialog Data
	//{{AFX_DATA(EditProfileExpDlg)
	enum { IDD = IDD_EDIT_PROFILE_EXP_DIALOG };
	CComboBox	m_Graph_area_name;
	CButton	m_Graph_area;
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
	CString	m_Factor_y_str;
	CString	m_Shift_x_str;
	CString	m_Shift_y_str;
	CString	m_Turn_str;
	BOOL	m_Graph_area_bool;
	int		m_Metre_int;
	CString	m_Choosen_folder_str;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditProfileExpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EditProfileExpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeNameProfile();
	afx_msg void OnSelchangeSection();
	afx_msg void OnOpenSelectFolder();
	afx_msg void OnGraphArea();
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

#endif // !defined(AFX_EDITPROFILEEXPDLG_H__0374074D_7039_4327_AA93_F19037082042__INCLUDED_)
