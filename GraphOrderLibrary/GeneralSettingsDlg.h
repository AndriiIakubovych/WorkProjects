#if !defined(AFX_GENERALSETTINGSDLG_H__08310685_EACE_4906_A6CF_5F6F5511CDF5__INCLUDED_)
#define AFX_GENERALSETTINGSDLG_H__08310685_EACE_4906_A6CF_5F6F5511CDF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GeneralSettingsDlg.h : header file
//

#include "SelectStateOrder.h"

/////////////////////////////////////////////////////////////////////////////
// CGeneralSettingsDlg dialog

class CGeneralSettingsDlg : public CDialog
{
	// Construction
public:
	CGeneralSettingsDlg(CWnd* pParent = NULL);   // standard constructor
	CString IniFile;
	CString StrConnectionAdm;
	CString StrConnectionService;
	int ViewGrid;
	int ViewLegend;
	CString WidthColumn;
	COLORREF Color;
	vector <int> Red;
	vector <int> Green;
	vector <int> Blue;
	bool IncreaseSort;
	bool DecreaseSort;
	bool NumberOrderSort;
	bool AdmRegionNumberSort;
	bool DateReceiptOrderSort;
	bool OperationalServiceSort;
	bool AdmRegNumFilter;
	bool OperatServFilter;
	CString AdmRegionNumber;
	CString OperationalService;
	bool ChangeInscriptionFont;
	bool ChangeNameFont;
	LOGFONT lfh;
	LOGFONT lfv;
	LOGFONT lfn;
	COLORREF fci;
	COLORREF fcn;

	// Dialog Data
	//{{AFX_DATA(CGeneralSettingsDlg)
	enum { IDD = IDD_GENERAL_SETTINGS_DIALOG };
	CComboBox	m_Operational_service;
	CComboBox	m_Adm_region_name;
	CButton	m_Operational_service_filter;
	CButton	m_Adm_region_name_filter;
	CEdit	m_Width_column;
	CButton	m_View_legend;
	CButton	m_View_grid;
	CSelectStateOrder	m_Select_state_order;
	CButton	m_Increase_sort;
	CButton	m_Decrease_sort;
	CButton	m_Number_order_sort;
	CButton	m_Adm_region_number_sort;
	CButton	m_Date_receipt_order_sort;
	CButton	m_Operational_service_sort;
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeneralSettingsDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGeneralSettingsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeColorState();
	afx_msg void OnViewGrid();
	afx_msg void OnViewLegend();
	afx_msg void OnChangeInputWidthColumn();
	afx_msg void OnAdmRegionNameFilter();
	afx_msg void OnOperationalServiceFilter();
	virtual void OnOK();
	afx_msg void OnChangeSelectAdmRegionFilter();
	afx_msg void OnChangeSelectOperationalFilter();
	virtual void OnInscriptionFont();
	virtual void OnNameFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERALSETTINGSDLG_H__08310685_EACE_4906_A6CF_5F6F5511CDF5__INCLUDED_)
