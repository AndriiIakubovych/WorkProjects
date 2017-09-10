#if !defined(AFX_ADDPROFILEDLG_H__19F4CAA2_AAFC_464F_B456_0AB0B72ED7F4__INCLUDED_)
#define AFX_ADDPROFILEDLG_H__19F4CAA2_AAFC_464F_B456_0AB0B72ED7F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddProfileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AddProfileDlg dialog

class AddProfileDlg : public CDialog
{
// Construction
public:
	AddProfileDlg(CWnd* pParent = NULL);   // standard constructor
	CString IniFile;
	CString PathSection;
	BOOL GraphAreaEnable;
	int TypeProfile;
	int PERSON;
	int NumberSection;
	int GroupSection;
	int GraphAreaId;
	int TypeSourceData;

// Dialog Data
	//{{AFX_DATA(AddProfileDlg)
	enum { IDD = IDD_ADD_PROFILE_DIALOG };
	CEdit	m_Size_y;
	CEdit	m_Size_x;
	CButton	m_Usual;
	CButton	m_Metre;
	CComboBox	m_Graph_area_name;
	CButton	m_Graph_area;
	CEdit	m_Turn;
	CEdit	m_Shift_y;
	CEdit	m_Shift_x;
	CEdit	m_Choosen_folder;
	CEdit	m_Factor_y;
	CEdit	m_Factor_x;
	CComboBox	m_Name_section;
	CEdit	m_Name_profile;
	CComboBox	m_Type_profile;
	CString	m_Name_profile_str;
	CString	m_Factor_x_str;
	CString	m_Factor_y_str;
	CString	m_Choosen_folder_str;
	CString	m_Shift_x_str;
	CString	m_Shift_y_str;
	CString	m_Turn_str;
	int		m_Type_profile_int;
	BOOL	m_Graph_area_bool;
	int		m_Usual_int;
	int		m_Metre_int;
	CString	m_Size_x_str;
	CString	m_Size_y_str;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AddProfileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AddProfileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTypeProfile();
	afx_msg void OnSelchangeSection();
	afx_msg void OnOpenSelectFolder();
	afx_msg void OnGraphArea();
	afx_msg void OnChangeNameProfile();
	afx_msg void OnChangeFolder();
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

#endif // !defined(AFX_ADDPROFILEDLG_H__19F4CAA2_AAFC_464F_B456_0AB0B72ED7F4__INCLUDED_)
