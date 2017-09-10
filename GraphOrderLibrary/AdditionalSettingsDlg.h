#if !defined(AFX_ADDITIONALSETTINGSDLG_H__47B3654A_8BEF_4B94_9F3E_3236E481666D__INCLUDED_)
#define AFX_ADDITIONALSETTINGSDLG_H__47B3654A_8BEF_4B94_9F3E_3236E481666D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdditionalSettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdditionalSettingsDlg dialog

class CAdditionalSettingsDlg : public CDialog
{
	// Construction
public:
	CAdditionalSettingsDlg(CWnd* pParent = NULL);   // standard constructor
	CString IniFile;
	CTime DateBeginPeriod;
	CBitmap Reduce;
	CTime TimeBeginPeriod;
	CTime DateEndPeriod;
	CString DurationPeriod;
	CString ValueStep;

	// Dialog Data
	//{{AFX_DATA(CAdditionalSettingsDlg)
	enum { IDD = IDD_ADDITIONAL_SETTINGS_DIALOG };
	CButton	m_Increase_date;
	CButton	m_Reduce_date;
	CEdit	m_Duration_period;
	CEdit	m_Value_step;
	CDateTimeCtrl	m_Time_begin_period;
	CDateTimeCtrl	m_Date_begin_period;
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdditionalSettingsDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAdditionalSettingsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnReduceDate();
	afx_msg void OnIncreaseDate();
	afx_msg void OnDatetimechangeSelectDateBeginPeriod(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeSelectTimeBeginPeriod(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeInputDurationPeriod();
	afx_msg void OnChangeInputStep();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDITIONALSETTINGSDLG_H__47B3654A_8BEF_4B94_9F3E_3236E481666D__INCLUDED_)
