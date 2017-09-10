// AboutProgramDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "AboutProgramDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AboutProgramDlg dialog


AboutProgramDlg::AboutProgramDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AboutProgramDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(AboutProgramDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void AboutProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AboutProgramDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AboutProgramDlg, CDialog)
	//{{AFX_MSG_MAP(AboutProgramDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AboutProgramDlg message handlers
