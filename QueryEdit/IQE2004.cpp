// IQE2004.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "i:\ciwin5\bibuni6\General.h"

#include "IQE2004.h"
#include "IQE2004Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CIQE2004App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CIQE2004App::CIQE2004App()
{
}

CIQE2004App theApp;

BOOL CIQE2004App::InitInstance()
{
	AfxEnableControlContainer();

    if(!LoadResDll("QueryEdit"))
        return false;

	CIQE2004Dlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CIQE2004App::OnAppAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg adlg;
	adlg.DoModal();
}
