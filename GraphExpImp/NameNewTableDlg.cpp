// NameNewTableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "NameNewTableDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NameNewTableDlg dialog


NameNewTableDlg::NameNewTableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(NameNewTableDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(NameNewTableDlg)
	m_Name_table_str = _T("");
	//}}AFX_DATA_INIT
}


void NameNewTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(NameNewTableDlg)
	DDX_Control(pDX, IDC_NAME_TABLE, m_Name_table);
	DDX_Text(pDX, IDC_NAME_TABLE, m_Name_table_str);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(NameNewTableDlg, CDialog)
	//{{AFX_MSG_MAP(NameNewTableDlg)
	ON_EN_CHANGE(IDC_NAME_TABLE, OnChangeNameTable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NameNewTableDlg message handlers

void NameNewTableDlg::OnChangeNameTable() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString NameTable;
	CWnd* pWnd = GetDlgItem(IDOK);
	m_Name_table.GetWindowText(NameTable);
	if (NameTable.IsEmpty() || !NameTable.Find(" ", 0))
		pWnd->EnableWindow(false);
	else
		pWnd->EnableWindow(true);
}
