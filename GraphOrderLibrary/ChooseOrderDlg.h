#pragma once
#include "afxwin.h"
#include "stdafx.h"

using namespace std;

// CChooseOrderDlg dialog

class CChooseOrderDlg : public CDialog
{
	DECLARE_DYNAMIC(CChooseOrderDlg)
	vector <int> FindOrder;
	vector <CString> FindOrderStr;
	int NumberOrder;

public:
	CChooseOrderDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CChooseOrderDlg();

// Dialog Data
	enum { IDD = IDD_CHOOSE_ORDER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	CComboBox m_Order_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CListBox m_Order_list;
};
