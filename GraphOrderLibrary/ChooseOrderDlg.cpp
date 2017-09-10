// ChooseOrderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphOrder.h"
#include "ChooseOrderDlg.h"
#include "afxdialogex.h"


// CChooseOrderDlg dialog

IMPLEMENT_DYNAMIC(CChooseOrderDlg, CDialog)

CChooseOrderDlg::CChooseOrderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseOrderDlg::IDD, pParent)
{

}

CChooseOrderDlg::~CChooseOrderDlg()
{
}

void CChooseOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_ORDER_LIST, m_Order_list);
	DDX_Control(pDX, IDC_ORDER_LIST, m_Order_list);
}

BEGIN_MESSAGE_MAP(CChooseOrderDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CChooseOrderDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CChooseOrderDlg message handlers

BOOL CChooseOrderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	char buffer[MAX_PATH];
	for (int i = 0; i < FindOrder.size(); i++)
	{
		m_Order_list.AddString(FindOrderStr[i]);
	}
	m_Order_list.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CChooseOrderDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//m_Order_list.GetText(m_Order_list.GetCurSel(), NumberOrder);
	NumberOrder = FindOrder[m_Order_list.GetCurSel()];
	CDialog::OnOK();
}
