#if !defined(AFX_EDITFILESIMPDLG_H__03713661_511A_4711_9804_E60598D73998__INCLUDED_)
#define AFX_EDITFILESIMPDLG_H__03713661_511A_4711_9804_E60598D73998__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditFilesImpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EditFilesImpDlg dialog

class EditFilesImpDlg : public CDialog
{
// Construction
public:
	EditFilesImpDlg(CWnd* pParent = NULL);   // standard constructor
	CString IniFile;
	CString StrConnection;
	CString Folder;
	int IdProfile;
	int AcceptingTypeLines;
	int LevelLines;
	int AcceptingTypeText;
	int LevelText;
	int TransformDenotations;
	int TypeTransformedDenotations;
	int LevelDenotations;
	int NumberFieldCharakteristics;
	int AcceptingTypeCharakteristics;
	int LevelCharakteristics;
	BOOL ImportLinesEnable;
	BOOL ImportTextEnable;
	BOOL ImportDenotationsEnable;
	BOOL ImportCharakteristicsEnable;
	BOOL DeleteGraphObjectEnable;

// Dialog Data
	//{{AFX_DATA(EditFilesImpDlg)
	enum { IDD = IDD_EDIT_FILES_IMP_DIALOG };
	CButton	m_Import_charakteristics;
	CButton	m_Circles;
	CEdit	m_Height_charakteristics;
	CComboBox	m_Name_field_charakteristics;
	CEdit	m_Size_denotations;
	CButton	m_Windows;
	CComboBox	m_Accepting_type_charakteristics;
	CComboBox	m_Type_transformed_denotations;
	CComboBox	m_Accepting_type_text;
	CComboBox	m_Accepting_type_lines;
	CEdit	m_File_name;
	CString	m_File_name_str;
	int		m_Windows_int;
	CString	m_Size_denotations_str;
	int		m_Circles_int;
	BOOL	m_Break_lines_segments_bool;
	BOOL	m_Skip_superfluous_points_bool;
	int		m_Name_field_charakteristics_int;
	BOOL	m_Import_charakteristics_bool;
	CString	m_Height_charakteristics_str;
	CButton	m_Delete_graph_object;
	BOOL	m_Delete_graph_object_bool;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditFilesImpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EditFilesImpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCircles();
	afx_msg void OnPrimitives();
	afx_msg void OnImpCharakteristics();
	afx_msg void OnOpenSelectFile();
	afx_msg void OnChangeFileName();
	afx_msg void OnChangeSizeDenotations();
	afx_msg void OnChangeSizeCharacteristics();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITFILESIMPDLG_H__03713661_511A_4711_9804_E60598D73998__INCLUDED_)
